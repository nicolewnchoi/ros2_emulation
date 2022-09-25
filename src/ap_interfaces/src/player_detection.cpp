#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <deque>
#include <thread>
#include <stdlib.h>

//print to file
#include <iostream>
#include <fstream>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "ap_interfaces/msg/score.hpp"
#include "ap_interfaces/msg/pos.hpp"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/video.hpp>

//#include "image_transport/image_transport.hpp"
//#include "sensor_msgs/image_encodings.hpp"

using namespace std;
using namespace std::chrono_literals;
using namespace cv;
using namespace std::chrono;


struct Pos_raw1
{

    int total;
    std::string timestamp;
    float x[32];
    float y[32];
    int player_id[32];
    std::string tag_id[32];
    float size[32];

};


Mat Init_background(){
    
    // int img_height = 750;
    // int img_width = 960;
    int img_height = 640;
    int img_width = 960;
    Mat background_raw = imread("D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/src/background960_640.jpg");

	return background_raw;

}

deque<Mat> background_subtraction(Mat frame_input , Mat background_input){

    Mat recording;
	Mat result;
	Mat result_hsv;
	Mat testmat;

    // 960*750
    // int img_height = 750;
    // int img_width = 960;
    // int cut_start_x = 171;
	// int cut_start_y = 143;
    //960*640
    int img_height = 640;
    int img_width = 960;
    int cut_start_x = 160;
	int cut_start_y = 192;

    int high_H = 360 / 2;
	int high_S = 235;
	int high_V = 255;

	Mat result_hsv_copy;
	Mat result_final;
	vector<Mat> channels;

    deque<Mat> Buffer;

    Mat current(frame_input, Rect(cut_start_x, cut_start_y, img_width, img_height));

    absdiff(current, background_input, result);

    cvtColor(result, result_hsv, COLOR_BGR2HSV);
    split(result_hsv, channels);

    if (!frame_input.empty())
    {

        //bitwise_and(mask, channels[2], channels[2]);
        merge(channels, result_hsv);
        inRange(result_hsv, Scalar(0, 0, 60), Scalar(high_H, high_S, high_V), result_final);
        Buffer.push_back(result_final);
    }

    return Buffer;
	

}

void perspectivetransform_vector(vector<Point2f>& center)
{
    float img_center_x = 643.56;
    float img_center_y = 536.71;
    // perspective_x = ; // percent
    // perspective_y = ;
    float focal_x = 1143;
    float focal_y = 1145;
    float transform_x = -3.02;
    float transform_y = 0.0;
    vector<Point2f> cam_coordinate(center.size());
    vector<Point2f> world_coordinate(center.size());

    
    for(int i = 0; i < center.size(); i++){
        //image coordinate to camera coordinate
        cam_coordinate[i].x = (center[i].x - img_center_x) / focal_x;
        cam_coordinate[i].y = (center[i].y - img_center_y) / focal_y;

        // camera coordinate to world coordinate
        world_coordinate[i].x = cam_coordinate[i].x - transform_x;
        world_coordinate[i].y =  cam_coordinate[i].y - transform_y;

        // igym version
        // center[i].x = (center[i].x - img_center_x * perspective_x / 100) / (1 - perspective_x / 100);
        // center[i].y = (center[i].y - img_center_y * perspective_y / 100) / (1 - perspective_y / 100);
    }
}




// detect algorithm
void detect_pos(Pos_raw1* pos_raw) {

    int first_flag = 1;

    ofstream myfile_detect;
    myfile_detect.open ("detect_duration.txt", ios::out);
    
    // read from file
    Mat frame, fgMask, fgMask_gray, final_view;
    Mat fgMask_erode, fgMask_dilate;
    Mat frame_diff;
    Mat input, input_erode, input_dilate;
    VideoCapture cap;

    cap.open("D:/umich_course/Airplay/video/multiplayer.avi");

    Mat Background = Init_background();
    //cout << "background size: " << Background.size() <<endl;
    deque<Mat> buffer;


    while(true){
        
        cap.read(frame);

        if(frame.empty()){
            pos_raw->total = -1;
            //pos1->timestamp = static_cast<double>(time.nano);
            (pos_raw->x)[0] = -1;
            (pos_raw->y)[0] = -1;
            (pos_raw->player_id)[0] = -1;
            (pos_raw->size)[0] = -1;

        }else{
            // start time
            auto timestart =  duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            //cout << "frame size: " << frame.size()<< endl;
            //resize(frame, frame, Size(input_width, input_height), INTER_LINEAR);
            //background subtraction
            buffer = background_subtraction(frame, Background);
            //check whether there are available frames in buffer
			if (!buffer.empty())
			{
				frame_diff = static_cast<int>(buffer.size());
				input = buffer.back().clone(); //choose the most recent frame as input
				buffer.clear();
			}
            // if (frame_diff != 0)
			// {


            // }

            // erode and dilate
            //GaussianBlur(input, input_erode, Size(3, 3), 0, 0);
            Mat elementErosion = getStructuringElement(MORPH_ELLIPSE, Size(2 * 5 + 1, 2 * 5 + 1));
            erode(input, input_erode, elementErosion);
            Mat elementDilate = getStructuringElement(MORPH_ELLIPSE,  Size(2 * 6 + 1, 2 * 6 + 1));
	        dilate(input, input_dilate, elementDilate);

            // threshold to binary
            // int threshold_value = 120;
            // int threshold_type = 0; //0 Binary
            // int const max_binary_value = 255;
            // threshold( frame, final_view, threshold_value, max_binary_value, threshold_type );

            // extract contours and find blob
            vector<vector<Point> > contours;
            vector<Vec4i> hierarchy;
            findContours(input_dilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
            size_t size_contours = contours.size();
            vector<vector<Point> > contours_poly( size_contours );
            vector<Point2f>centers_contours( size_contours );
            vector<float>radius_contours(size_contours);
            vector<Point2f>centers;
            vector<float>radius;
            
            // field rect
            // int left_side = 46;
            // int right_side = 936;
            // int up_side = 83;
            // int down_side = 684;
            //cout << contours.size() << endl;
            for( size_t k = 0; k < contours.size(); k++ ){
                if (contourArea(contours[k]) > 100){
                    approxPolyDP( contours[k], contours_poly[k], 3, true );
                    minEnclosingCircle( contours_poly[k], centers_contours[k], radius_contours[k] );
                    if (radius_contours[k] > 100 || radius_contours[k] < 20) {continue;}
                    // cout << "find contour" <<endl;
                    // cout << "detected centers:"<<centers[k] <<endl;
                    centers.push_back(centers_contours[k]);
                    radius.push_back(radius_contours[k]);
                    
                }
            }

            

            if (!centers.empty()){
                (pos_raw->total) = centers.size();
                for(int i = 0; i < centers.size(); i++){
                    circle( input_dilate, centers[i], (int)radius[i] + 10, (0,0,255), 8);
                    (pos_raw->x)[i] = (float)centers[i].x;
                    (pos_raw->y)[i] = (float)(640 - centers[i].y);
                    (pos_raw->size)[i] = (float)radius[i];
                    
                }
               
            }



            auto timeend =  duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            auto d_time = timeend - timestart;
            myfile_detect << d_time <<endl;

            imshow("input", input);
            //imshow("Background", Background);
            //imshow("erode", input_erode);
            imshow("Live", frame);
            imshow("reduce noise", input_dilate);
            //imshow("final_view", final_view);
            waitKey(1);

        }
        

    }
    myfile_detect.close();

}
/**
 * A small convenience function for converting a thread ID to a string
 **/
std::string string_thread_id()
{
    auto hashed = std::hash<std::thread::id>()(std::this_thread::get_id());
    return std::to_string(hashed);
}

/* For this example, we will be creating a publishing node like the one in minimal_publisher.
 * We will have a single subscriber node running 2 threads. Each thread loops at different speeds, and
 * just repeats what it sees from the publisher to the screen.
 */

class PublisherNode : public rclcpp::Node
{
    Pos_raw1 * pos_raw;
    ofstream & myfile;
public:
    PublisherNode(Pos_raw1 * pos, ofstream& file)
        : Node("PlayerDetectionPublisher"), count_(0), pos_raw(pos), flag(0), myfile(file)
    {

        publisher_ = this->create_publisher<ap_interfaces::msg::Pos>("pos_raw", 10);
        auto timer_callback =
            [this]() -> void {
            auto message = ap_interfaces::msg::Pos();

            // Extract current thread
            int temp_num = pos_raw->total;
            for(int i = 0; i < temp_num; i++){
                (message.x)[i] = (pos_raw->x)[i];
                (message.y)[i] = (pos_raw->y)[i];
                (message.size)[i] = (pos_raw->size)[i];
            }
            message.total = pos_raw->total;

            rclcpp::Time time = this->now();
            message.timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            unsigned long timenow_pub = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            if (flag != 0){
                duration_pub = timenow_pub - time_prev_pub;
                myfile << count_ << ": ";
                myfile << duration_pub <<endl;
                time_prev_pub = timenow_pub;

                // myfile << count_ << ": ";
                // myfile << (double)(time.nanoseconds() - time_prev.nanoseconds()) <<endl;
                // time_prev = time;
               
                count_++;

            }else{
                // time_prev = time;
                time_prev_pub = timenow_pub;
                count_++;
                flag++;
            }
        

            // Extract current thread
            auto curr_thread = string_thread_id();
            
            std::string output;
            // output += " ";
            // output += std::to_string(pos_raw->timestamp);
            output += " ";
            output += std::to_string(pos_raw->total);
            output += " ";
            output += std::to_string((pos_raw->x)[1]);
            output += " ";
            output += std::to_string((pos_raw->y)[1]);

            // Prep display message
            RCLCPP_INFO(
                this->get_logger(), "\n<<THREAD %s>> Publishing '%s'",
                curr_thread.c_str(), output.c_str());
            this->publisher_->publish(message);
        };
        timer_ = this->create_wall_timer(16.67ms, timer_callback);
    }

private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<ap_interfaces::msg::Pos>::SharedPtr publisher_;
    size_t count_;
    //rclcpp::Time time_prev;
    unsigned long duration_pub;
    unsigned long time_prev_pub;
    int flag;

};

class SingleThreadedNode : public rclcpp::Node
{
public:
    SingleThreadedNode()
        : Node("PlayerDetectionSubscriber")
    {
        /* These define the callback groups
         * They don't really do much on their own, but they have to exist in order to
         * assign callbacks to them. They're also what the executor looks for when trying to run multiple threads
         */
        callback_group_subscriber_ = this->create_callback_group(
            rclcpp::CallbackGroupType::MutuallyExclusive);

        // Each of these callback groups is basically a thread
        // Everything assigned to one of them gets bundled into the same thread
        auto sub_opt = rclcpp::SubscriptionOptions();
        sub_opt.callback_group = callback_group_subscriber_;

        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "control",
            rclcpp::QoS(10),
            // std::bind is sort of C++'s way of passing a function
            // If you're used to function-passing, skip these comments
            std::bind(
                &SingleThreadedNode::subscriber_cb,  // First parameter is a reference to the function
                this,                               // What the function should be bound to
                std::placeholders::_1),             // At this point we're not positive of all the
                                                    // parameters being passed
                                                    // So we just put a generic placeholder
                                                    // into the binder
                                                    // (since we know we need ONE parameter)
            sub_opt);                  // This is where we set the callback group.
                                        // This subscription will run with callback group subscriber1
    }

private:
    /**
     * Simple function for generating a timestamp
     * Used for somewhat ineffectually demonstrating that the multithreading doesn't cripple performace
     */
    std::string timing_string()
    {
        rclcpp::Time time = this->now();
        return std::to_string(time.nanoseconds());
    }

    /**
     * Every time the Publisher publishes something, all subscribers to the topic get poked
     * This function gets called when Subscriber1 is poked (due to the std::bind we used when defining it)
     */
    void subscriber_cb(const std_msgs::msg::String::SharedPtr msg)
    {
        auto message_received_at = timing_string();

        // Extract current thread
        RCLCPP_INFO(
            this->get_logger(), "THREAD %s => Heard '%s' at %s",
            string_thread_id().c_str(), msg->data.c_str(), message_received_at.c_str());
    }


    rclcpp::CallbackGroup::SharedPtr callback_group_subscriber_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char* argv[])
{
    Pos_raw1 pos_raw;
    ofstream myfile;
    
    myfile.open ("pub_diff.txt", ios::out);

    rclcpp::init(argc, argv);

    std::thread th_detect(detect_pos,&pos_raw);

    // You MUST use the MultiThreadedExecutor to use, well, multiple threads
    rclcpp::executors::MultiThreadedExecutor executor;
    auto player_detection_pubnode = std::make_shared<PublisherNode>(&pos_raw, myfile);
    auto player_detection_subnode = std::make_shared<SingleThreadedNode>();  // This contains BOTH subscriber callbacks.
                                                          // They will still run on different threads
                                                          // One Node. Two callbacks. Two Threads
    executor.add_node(player_detection_pubnode);
    executor.add_node(player_detection_subnode);
    executor.spin();
    th_detect.join();
    rclcpp::shutdown();
    // myfile_detect.close();
    myfile.close();
    return 0;
}