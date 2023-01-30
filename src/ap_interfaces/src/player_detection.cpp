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

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include "CameraFLIR.h"

//#include "image_transport/image_transport.hpp"
//#include "sensor_msgs/image_encodings.hpp"

using namespace std;
using namespace std::chrono_literals;
using namespace cv;
using namespace std::chrono;
using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;


#include <mutex>          // std::mutex
std::mutex mtx;           // mutex for critical section
bool newDetections;



Mat Init_background(Mat first_frame){
    // read from file
    // int img_height = 750;
    // int img_width = 960;
    // Mat background_raw = imread("D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/src/background960_750.jpg");

    // roi960*750
    // int bg_height = 750;
    // int bg_width = 960;
    // int bg_cut_start_x = 160;
	// int bg_cut_start_y = 137;
    //960*640
    // int img_height = 640;
    // int img_width = 960;
    // int cut_start_x = 200;
	// int cut_start_y = 192;

    //table demo
    int img_height = 480;
    int img_width = 720;
    int cut_start_x = 300;
	int cut_start_y = 320;


    Mat background_raw(first_frame, Rect(cut_start_x, cut_start_y, img_width, img_height));
    //remove all green
    // vector<Mat> channels;
    // Mat background_removegreen;
    // split(background_raw, channels);
    // channels[1] = Mat::zeros(background_raw.rows, background_raw.cols, CV_8UC1);
    // merge(channels, background_removegreen);

    //convert_to_grey
    // Mat background_grey;
    // cvtColor(background_raw, background_grey, cv::COLOR_BGR2GRAY);

	return background_raw;

}

// int threshold_value = 120;
// void test_thres(){
//     namedWindow("thres", WINDOW_AUTOSIZE);
//     createTrackbar( "threshold_value", "thres", &threshold_value, 255);
// }
// int low_H = 36;
// int low_S = 50;
// int low_V = 70;
// int high_H = 89;
// int high_S = 255;
// int high_V = 255;
// void test_HSV(){
//     namedWindow("HSV", WINDOW_AUTOSIZE);
//     createTrackbar( "low_H", "HSV", &low_H, 255);
//     createTrackbar( "low_S", "HSV", &low_S, 255);
//     createTrackbar( "low_V", "HSV", &low_V, 255);
//     createTrackbar( "high_H", "HSV", &high_H, 255);
//     createTrackbar( "high_S", "HSV", &high_S, 255);
//     createTrackbar( "high_V", "HSV", &high_V, 255);
// }


deque<Mat> background_subtraction(Mat frame_input, Mat background_input){

    Mat recording;
	Mat result;
	Mat result_hsv;
	Mat testmat;

    //table demo
    int img_height = 480;
    int img_width = 720;
    int cut_start_x = 300;
	int cut_start_y = 320;
    
    // green color
    int low_H = 39;
    int low_S = 58;
    int low_V = 81;
    int high_H = 114;
    int high_S = 255;
    int high_V = 255;
    

    

    // old version
    int low_H_all = 0;
	int low_S_all = 0;
	int low_V_all = 60;
    int high_H_all = 360 / 2;
	int high_S_all = 235;
	int high_V_all = 255;
	Mat result_hsv_copy;
	Mat result_final, result_all;
    Mat green_mask, colorMask;
    Mat only_green;
	vector<Mat> channels;

    deque<Mat> Buffer;

    Mat current(frame_input, Rect(cut_start_x, cut_start_y, img_width, img_height));
    
    // old version
    absdiff(current, background_input, result);

    cvtColor(result, result_hsv, COLOR_BGR2HSV);
    // split(result_hsv, channels);

    if (!frame_input.empty())
    {

        // merge(channels, result_hsv);
        inRange(result_hsv, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), green_mask);
        inRange(result_hsv, Scalar(low_H_all, low_S_all, low_V_all), Scalar(high_H_all, high_S_all, high_V_all), result_all);
        //preprocess
        // Mat elementErosion = getStructuringElement(MORPH_ELLIPSE, Size(2 * 3 + 1, 2 * 3 + 1));
        // erode(green_mask, green_mask, elementErosion);
        // Mat elementDilate = getStructuringElement(MORPH_ELLIPSE,  Size(2 * 6 + 1, 2 * 6 + 1));
        // dilate(green_mask, green_mask, elementDilate);

        bitwise_xor(green_mask, result_all, result_final);
        //absdiff(result_hsv, only_green, result_final);
        // // int threshold_value = 120;
        // int threshold_type = 0; //0 Binary
        // int const max_binary_value = 255;
        // threshold( result_final, result_final, threshold_value, max_binary_value, threshold_type );
        // imshow("result_all:",result_all);
        // imshow("green_mask:",green_mask);
        // imshow("result_final:",result_final);
        Buffer.push_back(result_final);
    }

    // HSV
    // absdiff(current, background_input, result);
    // cvtColor(result, result_hsv, COLOR_BGR2HSV);
    // inRange(result_hsv, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), green_mask);
    // bitwise_and(result_hsv, result_hsv, result_final, green_mask);
    // imshow("remove green:", result_final);
    // cvtColor(result_final, result_final, COLOR_HSV2BGR);
    // cvtColor(result_final, result_final, COLOR_BGR2GRAY);
    // // threshold to binary
    
    // Buffer.push_back(result_final);

    // another try
    // absdiff(current, background_input, result);

    // cvtColor(result, result_hsv, COLOR_BGR2HSV);
    // cvtColor(result, result_grey, COLOR_BGR2GRAY);
    // inRange(result_hsv, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), green_mask);
    // int morphosize = 1;
    // int opIterations = 1;
    // Mat MorphoElement = getStructuringElement( MORPH_RECT, Size( 2*morphosize + 1, 2*morphosize+1 ));
    // morphologyEx(green_mask, green_mask, MORPH_CLOSE, MorphoElement);
    // add(green_mask, result_grey, colorMask);
    // // split(result_hsv, channels);

        
    // // merge(channels, result_hsv);
    // // //cvtColor(result_hsv, result_final, cv::COLOR_BGR2GRAY);
    // // inRange(result_hsv, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), result_final);
    // // Buffer.push_back(result_hsv);
    // imshow("colorMask:", colorMask);
    // int threshold_value = 0;
    // int threshold_type = 0; //0 Binary
    // int const max_binary_value = 255;
    // threshold( colorMask, result_final, threshold_value, max_binary_value, threshold_type );
    // Buffer.push_back(result_final);

    return Buffer;
	

}

Mat AverageFrame(vector<Mat> frames){
    Mat temp;
    Mat temp1;
    Mat result;
    cout << frames[0].size() << endl;
    frames[0].convertTo(temp, CV_32FC3);
    Mat avgImg(frames[0].rows, frames[0].cols, CV_32FC3);
    avgImg = temp;
    //Mat captured_img;
    //cout<< "frames size:" << frames.size() << endl;
    if (frames.size() > 1){

        for(int i = 1 ; i < frames.size(); i++){
            // captured_img = frames[i];
            // accumulate(captured_img, avgImg);
            frames[i].convertTo(temp1, CV_32FC3);
            //accumulate(temp, avgImg);
            avgImg += temp1;
            cout<< i << endl;
        }

    }
    //avgImg = avgImg / float(frames.size());
    avgImg = avgImg / float(frames.size());
    avgImg.convertTo(result, CV_8UC3);

    //cout << "result size: " << avgImg.size() << endl;
    return result;

}


// DEBUG for mat's type
// string type2str(int type) {
//   string r;

//   uchar depth = type & CV_MAT_DEPTH_MASK;
//   uchar chans = 1 + (type >> CV_CN_SHIFT);

//   switch ( depth ) {
//     case CV_8U:  r = "8U"; break;
//     case CV_8S:  r = "8S"; break;
//     case CV_16U: r = "16U"; break;
//     case CV_16S: r = "16S"; break;
//     case CV_32S: r = "32S"; break;
//     case CV_32F: r = "32F"; break;
//     case CV_64F: r = "64F"; break;
//     default:     r = "User"; break;
//   }

//   r += "C";
//   r += (chans+'0');

//   return r;
// }

void detect_pos(ap_interfaces::msg::Pos* pos_raw) {

    int first_flag = 0;
    //xrf delay
    ofstream myfile_detect;
    myfile_detect.open ("detect_duration.txt", ios::out);

    Mat frame, frame_rgb, fgMask, fgMask_gray;
    Mat fgMask_erode, fgMask_dilate;
    Mat frame_diff;
    Mat input, input_erode, input_dilate, input_grey;
    vector<Mat> captured_frames;
    Mat avgframe;

    CameraFLIR theFLIRCamera;
    theFLIRCamera.Initialize();
    //cout<< "FLIR Initialize completed"<<endl;

    Mat Background(480, 720, CV_8UC3, Scalar());
    
    deque<Mat> buffer;

    //para in while loop
    vector<Point> contours_poly_temp;
    Point2f centers_contours_temp;
    float radius_contours_temp;
    vector<Point2f>centers;
    vector<float>radius;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //test_HSV();
    //test_thres();
    while(true){
        auto timestart =  duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        frame = theFLIRCamera.GrabFrame(0);
        //cvtColor(frame, frame_rgb, cv::COLOR_BGR2RGB);
        //cout << "grab frane!" << endl;
        if(frame.empty()){
            pos_raw->total = -1;
            //pos1->timestamp = static_cast<double>(time.nano);
            (pos_raw->x)[0] = -1;
            (pos_raw->y)[0] = -1;
            (pos_raw->player_id)[0] = -1;
            (pos_raw->size)[0] = -1;

        }else{
            // start time
            

            if (first_flag < 11){
                // cout<< "frame type: " << type2str(frame.type()) << endl;
                //cout<< "first_flag: "<<first_flag << endl;
                captured_frames.push_back(frame);
                // cout <<"captured_frames: "<< captured_frames.size() << endl;
                //cout << "start average frame" << endl;
                //cout << "frame size:" << frame.size() << endl;
                avgframe = AverageFrame(captured_frames);
                cout << "finish averaging frame " << endl;
                Background = Init_background(frame);
                
                // if (captured_frames.size() == 11){
                //     avgframe = AverageFrame(captured_frames);
                //     Background = Init_background(avgframe);

                // }
                // if (first_flag == 0){

                //     imwrite("first.jpg", Background);
                // }
                // if (first_flag == 1){

                //     imwrite("result1.jpg", Background);
                // }
                // if (first_flag == 2){

                //     imwrite("result2.jpg", Background);
                // }
                // if (first_flag == 3){

                //     imwrite("result3.jpg", Background);
                // }
                // if (first_flag == 4){

                //     imwrite("result4.jpg", Background);
                // }
                // if (first_flag == 5){

                //     imwrite("result5.jpg", Background);
                // }
                // if (first_flag == 6){

                //     imwrite("result6.jpg", Background);
                // }
                // if (first_flag == 7){

                //     imwrite("result7.jpg", Background);
                // }
                if (first_flag == 10){

                    imwrite("result10.jpg", Background);
                }
                //if (first_flag == 10){
                //    Mat temp;
                //    std::ostringstream name;
                //    int i;
                //    name << "captured_frames_";
                //    for(i = 0 ; i < captured_frames.size(); i++){
                //        name << i << ".jpg";
                //        // captured_img = frames[i];
                //        // accumulate(captured_img, avgImg);
                //        captured_frames[i].convertTo(temp, CV_32FC3);
                //        imwrite(name.str(), temp);                    
                //    }
                //}
                first_flag++;
                //cout << "background size: " << Background.size() <<endl;
            }

            buffer = background_subtraction(frame, Background);
            //cout << "get buffer " << endl;

            //check whether there are available frames in buffer
			if (!buffer.empty())
			{
				frame_diff = static_cast<int>(buffer.size());
				input = buffer.back().clone(); //choose the most recent frame as input
				buffer.clear();
			}

            // threshold to binary
            // int threshold_value = 120;
            // int threshold_type = 0; //0 Binary
            // int const max_binary_value = 255;
            // threshold( frame, final_view, threshold_value, max_binary_value, threshold_type );
            // erode and dilate
            //cvtColor(input, input_grey, cv::COLOR_BGR2GRAY);

            //GaussianBlur(input, input_erode, Size(3, 3), 0, 0);
            Mat elementErosion = getStructuringElement(MORPH_ELLIPSE, Size(2 * 3 + 1, 2 * 3 + 1));
            erode(input, input_erode, elementErosion);
            //cout <<"erode end"<<endl;
       
            Mat elementDilate = getStructuringElement(MORPH_ELLIPSE,  Size(2 * 6 + 1, 2 * 6 + 1));
	        dilate(input_erode, input_dilate, elementDilate);
            

            // extract contours and find blob
            contours.clear();
            hierarchy.clear();
            findContours(input_dilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
            size_t size_contours = contours.size();
            
            centers.clear();
            radius.clear();

            
            for( size_t k = 0; k < size_contours; k++ ){
                if (contourArea(contours[k]) > 100){
                    approxPolyDP( contours[k], contours_poly_temp, 3, true );
                    minEnclosingCircle( contours_poly_temp, centers_contours_temp, radius_contours_temp );
                    if (radius_contours_temp > 1000 || radius_contours_temp < 30) {continue;}
                    centers.push_back(centers_contours_temp);
                    radius.push_back(radius_contours_temp);
                }
            }

            
            if (!centers.empty()){
                (pos_raw->total) = centers.size();
                for(int i = 0; i < centers.size(); i++){
                    circle( input_dilate, centers[i], (int)radius[i] + 10, (0,0,255), 8);
                    (pos_raw->x)[i] = (float)centers[i].x;
                    (pos_raw->y)[i] = (float)(480 - centers[i].y);
                    (pos_raw->size)[i] = (float)radius[i];
                }
                mtx.lock();
                newDetections = true;
                mtx.unlock();
            }


            
            //xrf delay
            auto timeend =  duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            auto d_time = timeend - timestart;
            myfile_detect << d_time <<endl;

            //imshow("input", input);
            //imshow("Background", Background);
            //imshow("mask_display", Mask);
            //imshow("Live", frame);
            //moveWindow("Live", 10, 10);
            // // imshow("background",Background);
            //imshow("reduce noise", input_dilate);
            //imshow("final_view", final_view);
            //waitKey(1);


        }
        

    }
    //xrf delay
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
    ap_interfaces::msg::Pos * pos_raw;
    ofstream & myfile;
public:
    PublisherNode(ap_interfaces::msg::Pos * pos, ofstream& file)
        : Node("PlayerDetectionPublisher"), count_(0), pos_raw(pos), flag(0), myfile(file)
    {

        publisher_ = this->create_publisher<ap_interfaces::msg::Pos>("pos_raw", 10);
        auto timer_callback =
            [this]() -> void {
                
            mtx.lock();
            if(!newDetections){
                mtx.unlock();
                return;
            }
            ap_interfaces::msg::Pos pos_raw_msg = *pos_raw;
            newDetections = false;
            mtx.unlock();

            // Extract current thread
            rclcpp::Time time = this->now();

            //test time duration
            pos_raw_msg.timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

            //xrf delay
            unsigned long timenow_pub = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            if (flag != 0){
                duration_pub = timenow_pub - time_prev_pub;
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
            // output += std::to_string(pos_raw_msg.timestamp);
            output += " ";
            output += std::to_string(pos_raw_msg.total);
            output += " ";
            output += std::to_string((pos_raw_msg.x)[0]);
            output += " ";
            output += std::to_string((pos_raw_msg.y)[0]);

            // Prep display message
            RCLCPP_INFO(
                this->get_logger(), "\n<<THREAD %s>> Publishing '%s'",
                curr_thread.c_str(), output.c_str());
                
            //lets ad the time this message was published to the message so qwe can compare inside 
            // unity
            //https://stackoverflow.com/questions/31255486/how-do-i-convert-a-stdchronotime-point-to-long-and-back
            auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
            auto value = start.time_since_epoch();
            double duration = value.count();
            // cout.precision(20);
            // cout << duration << "\n";
            pos_raw_msg.ms = duration;    //set the system time the message is sent
            pos_raw_msg.id = count_;
            //

            this->publisher_->publish(pos_raw_msg);
            
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
    ap_interfaces::msg::Pos pos_raw;
    ofstream myfile;
    newDetections = false;
    
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