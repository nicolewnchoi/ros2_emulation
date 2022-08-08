// Copyright 2020 Open Source Robotics Foundation, Inc.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
    int x[1];
    int y[1];
    int player_id[1];
    std::string tag_id[1];
    int size[1];

};

Mat Init_mask(){
    int img_height = 750;
    int img_width = 960;
    int ball_radius = 15;
    int goalSize_p1 = 100;
    int goalSize_p2 = 100;
    int LINE_THICKNESS = 14;

    Mat mask_raw = Mat::zeros(Size(960, 750), CV_8UC1);
	mask_raw = Scalar(255);
	ellipse(mask_raw, Point(70, img_height / 2 - 4), Size(img_width / 13, (int)(1.0 * img_height * (goalSize_p1 - 1.5 * ball_radius) * 7 / 3000)), 0, -90, 90, Scalar(0), LINE_THICKNESS + 3, 12);
	ellipse(mask_raw, Point(img_width - 63, img_height / 2 + 1), Size(img_width / 13, (int)(1.0 * img_height * (goalSize_p2 - 1.5 * ball_radius) * 7 / 3000)), 0, 90, 270, Scalar(0), LINE_THICKNESS + 3, 12);
	
	// Rect rec(Point(301, 220), Point(320, 275));
	// Rect rec2(Point(353, 222), Point(380, 275));
	// Rect rec3(Point(0, 0), Point(670, 80));

	circle(mask_raw, Point(img_width / 2, img_height / 2), 80, Scalar(0), 12, 9, 0);
	// Mat temp = mask_raw(rec);
	// temp.setTo(0);
	// temp = mask_raw(rec2);
	// temp.setTo(0);
	// temp = mask_raw(rec3);
	// temp.setTo(0);

	// Rect rec5(Point(0, 430), Point(50, 500));
	// temp = mask_raw(rec5);
	// temp.setTo(0);
    return mask_raw;

}

Mat Init_background(){
    // int img_height = 500;
    // int img_width = 670;
    int img_height = 750;
    int img_width = 960;
	// goalSize_p1 = 100;
	// goalSize_p2 = 100;
	// PC_coefficient = 1000;
	// PC_coefficient1 = 1000;
	// PC_coefficient2 = 1000;
	// goal_appear_counter = 0;
	// goal_counter = 0;
	// reset_flag = 0;
	// circle_flag = true;

	// black = imread("black.png");
	// resize(black, black, Size(disp_width, disp_height), INTER_LINEAR);
	// flip(black, black, 1);
	// line(black, Point(LINE_OFFSET, LINE_OFFSET), Point(LINE_OFFSET, disp_height - LINE_OFFSET), Scalar(theSettings.R, theSettings.G, theSettings.B), LINE_THICKNESS, 8, 0);
	// line(black, Point(LINE_OFFSET, LINE_OFFSET), Point(disp_width - LINE_OFFSET, LINE_OFFSET), Scalar(theSettings.R, theSettings.G, theSettings.B), LINE_THICKNESS, 8, 0);
	// line(black, Point(disp_width - LINE_OFFSET, LINE_OFFSET), Point(disp_width - LINE_OFFSET, disp_height - LINE_OFFSET), Scalar(theSettings.R, theSettings.G, theSettings.B), LINE_THICKNESS, 8, 0);
	// line(black, Point(LINE_OFFSET, disp_height - LINE_OFFSET), Point(disp_width - LINE_OFFSET, disp_height - LINE_OFFSET), Scalar(theSettings.R, theSettings.G, theSettings.B), LINE_THICKNESS + 3, 8, 0);
	
    // line(black, Point(disp_width / 2, LINE_OFFSET), Point(disp_width / 2, disp_height - LINE_OFFSET), Scalar(theSettings.R, theSettings.G, theSettings.B), LINE_THICKNESS - 5, 8, 0);

	// blackraw = black.clone();

	//  //real-time
    // splitDisp(black, output1, output2);
    //Mat background_raw = imread("D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/src/background.png");
    Mat background_raw = imread("D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/src/background960_750.jpg");

	return background_raw;

	// black = imread("black.png");
	// resize(black, black, Size(150 * DIS_COEFICIENT, 90 * DIS_COEFICIENT), INTER_LINEAR);
	// scoreraw = black.clone();

}

deque<Mat> background_subtraction(Mat frame_input, Mat mask , Mat background_input){

    Mat recording;
	Mat result;
	Mat result_hsv;
	Mat testmat;

    int img_height = 750;
    int img_width = 960;
	// int cut_start_x = 320;
	// int cut_start_y = 110;
    int cut_start_x = 171;
	int cut_start_y = 143;
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
    result_hsv_copy = result_hsv.clone();
    split(result_hsv, channels);

    if (!frame_input.empty())
    {
        testmat = channels[1];

        //bitwise_and(mask, channels[2], channels[2]);
        merge(channels, result_hsv);
        inRange(result_hsv, Scalar(0, 0, 60), Scalar(high_H, high_S, high_V), result_final);
        Buffer.push_back(result_final);
    }

    return Buffer;
	

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

    cap.open("D:/umich_course/Airplay/video/still.avi");

    // initialize para
    // int input_height = 720;
    // int input_width = 1280;
    Mat Mask = Init_mask();
    //cout<< "mask size: " << Mask.size()<< endl;
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
            cout << "frame size: " << frame.size()<< endl;
            //resize(frame, frame, Size(input_width, input_height), INTER_LINEAR);
            //background subtraction
            buffer = background_subtraction(frame, Mask, Background);
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
            vector<vector<Point> > contours_poly( contours.size() );
            vector<Point2f>centers_contours( contours.size() );
            vector<float>radius_contours(contours.size());
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

            for(int i = 0; i < centers.size(); i++){
                circle( input_dilate, centers[i], (int)radius[i] + 10, (0,0,255), 8);
            }

            if (!centers.empty()){
                
                (pos_raw->x)[0] = (int)centers[0].x;
                (pos_raw->y)[0] = (int)centers[0].y;
                (pos_raw->size)[0] = (int)radius[0];
            }



            auto timeend =  duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            auto d_time = timeend - timestart;
            myfile_detect << d_time <<endl;

            imshow("input", input);
            //imshow("Background", Background);
            imshow("mask_display", Mask);
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
            
            //message.total = pos_raw->total;
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
            // currently use total for debug
            message.total = count_;
            (message.x)[0] = (pos_raw->x)[0];
            (message.y)[0] = (pos_raw->y)[0];

            // Extract current thread
            auto curr_thread = string_thread_id();
            
            std::string output;
            // output += " ";
            // output += std::to_string(pos_raw->timestamp);
            output += " ";
            output += std::to_string((message.x)[0]);
            output += " ";
            output += std::to_string((message.y)[0]);

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