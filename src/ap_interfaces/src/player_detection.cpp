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

// judge whether the center_still is detected again or not; or whether detected_center is put inside 
int near_center(Point2f a, Point2f b, float thres) {

    Point2f diff = a - b;
    float result = sqrt(diff.x*diff.x + diff.y*diff.y);
    cout<<"center_diff: "<< result << endl;
    if (result <= thres) return 1;
    //cout<<"not near_center"<<endl;
    return 0;

}

void judge_centerstill(vector<Point2f>& still_centers, vector<Point2f>& detected_centers, vector<float>& still_radius) {
    if (still_centers.empty() || detected_centers.empty()){
        return;
    }
    auto k = still_radius.begin();

    for (auto i = still_centers.begin(); i != still_centers.end();) {
        for (auto j = detected_centers.begin(); j != detected_centers.end(); j++) {

            if (near_center(*i, *j, 500.0)) {
                //cout << "erase element" << endl;
                i = still_centers.erase(i);
                k = still_radius.erase(k);
                break;
            }
            if ((j + 1) == detected_centers.end()) {
                i++;
                k++;
            }
                
        }
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
    VideoCapture cap;
    Ptr<BackgroundSubtractor> pBackSub;

    cap.open("D:/umich_course/Airplay/video/still.avi");
    pBackSub = createBackgroundSubtractorKNN();

    // initialize para
    vector<Point2f> centers_still;
    vector<float> radius_still;
    vector<Point2f> centers_still_prev;
    vector<float> radius_still_prev;

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


            //update the background model
            pBackSub->apply(frame, fgMask);
            
            // erode and dilate
            Mat elementErosion = getStructuringElement(MORPH_ELLIPSE, Size(2 * 5 + 1, 2 * 5 + 1));
            erode(fgMask, fgMask_erode, elementErosion);
            Mat elementDilate = getStructuringElement(MORPH_ELLIPSE,	Size(2 * 6 + 1, 2 * 6 + 1));
	        dilate(fgMask_erode, fgMask_dilate, elementDilate);

            // threshold to binary
            int threshold_value = 120;
            int threshold_type = 0; //0 Binary
            int const max_binary_value = 255;
            threshold( fgMask_dilate, final_view, threshold_value, max_binary_value, threshold_type );

            // extract contours and find blob
            vector<vector<Point> > contours;
            vector<Vec4i> hierarchy;
            findContours(final_view, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
            vector<vector<Point> > contours_poly( contours.size() );
            vector<Point2f>centers( contours.size() );
            
            vector<float>radius( contours.size() );
            // field rect
            // int left_side = 46;
            // int right_side = 936;
            // int up_side = 83;
            // int down_side = 684;
            //cout << contours.size() << endl;
            for( size_t k = 0; k < contours.size(); k++ ){
                if (contourArea(contours[k]) > 2000){
                    approxPolyDP( contours[k], contours_poly[k], 3, true );
                    minEnclosingCircle( contours_poly[k], centers[k], radius[k] );
                    if (radius[k] > 100 ) {continue;}
                    cout << "find contour" <<endl;
                    cout << "detected centers:"<<centers[k] <<endl;
                    centers_still.push_back(centers[k]);
                    radius_still.push_back(radius[k]);

                }
            }
            cout << "center size: "<< centers.size() <<endl;

            if (first_flag){
                centers_still_prev = centers_still;
                radius_still_prev = radius_still;
                first_flag = 0;
            }
            // judge whether the player is still
            judge_centerstill(centers_still_prev, centers, radius_still_prev);
            // update prev centers with current centers
            radius_still_prev.insert(radius_still_prev.end(), radius_still.begin(), radius_still.end());
            centers_still_prev.insert(centers_still_prev.end(), centers_still.begin(), centers_still.end());
            

            cout << "center still prev size: " << centers_still_prev.size() << endl;

            if (!centers_still.empty()){
                circle( final_view, centers_still[0], (int)radius_still[0], (0,0,255), 20);
                (pos_raw->x)[0] = (int)centers_still[0].x;
                (pos_raw->y)[0] = (int)centers_still[0].y;
                (pos_raw->size)[0] = (int)radius_still[0];
            }else if(!centers_still_prev.empty()){
                circle( final_view, centers_still_prev[0], (int)radius_still_prev[0], (0,0,255), 20);
                (pos_raw->x)[0] = (int)centers_still_prev[0].x;
                (pos_raw->y)[0] = (int)centers_still_prev[0].y;
                (pos_raw->size)[0] = (int)radius_still_prev[0];
            }
            // clear valid centers and radius and prepare for the next frame
            centers_still.clear();
            radius_still.clear();
            auto timeend =  duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            auto d_time = timeend - timestart;
            myfile_detect << d_time <<endl;


            imshow("Live", frame);
            //imshow("reduce noise", fgMask_dilate);
            imshow("Mask", final_view);
            waitKey(1);

        }
        

    }
    myfile_detect.close();

    //default cam example
    // Mat frame;
    // VideoCapture cap;
    // int deviceID = 0;   // 0 = open default camera
    // int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // cap.open(deviceID, apiID);


    // while (true) {
        
    //     cap.read(frame);
    //     if(cap.isOpened()){
    //         if (frame.empty()) {
    //         } else {
    //             pos_raw->total = 1;
    //             //pos1->timestamp = static_cast<double>(time.nano);
    //             (pos_raw->x)[0] = 1;
    //             (pos_raw->y)[0] = 1;
    //             (pos_raw->player_id)[0] = 1;
    //             (pos_raw->size)[0] = 1;

    //             imshow("live", frame);
    //             waitKey(1);
    //         }

    //     }else{
    //     }
    // }
   
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