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
#include <string>
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

#include "image_transport/image_transport.hpp"
#include "sensor_msgs/image_encodings.hpp"

using namespace std;
using namespace std::chrono_literals;
using namespace cv;


struct Pos_raw1
{
    int total;
    double timestamp;
    int x[1];
    int y[1];
    int player_id[1];
    std::string tag_id[1];
    int size[1];

};

void detect_pos(Pos_raw1* pos_raw) {
    //opencv example
    Mat frame;
    VideoCapture cap;
    int deviceID = 0;   // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // opencv example 
    cap.open(deviceID, apiID);


    while (true) {
        
        cap.read(frame);
        if(cap.isOpened()){
            if (frame.empty()) {
            } else {
                pos_raw->total = 1;
                //pos1->timestamp = static_cast<double>(time.nano);
                (pos_raw->x)[0] = 1;
                (pos_raw->y)[0] = 1;
                (pos_raw->player_id)[0] = 1;
                (pos_raw->size)[0] = 1;

                imshow("live", frame);
                waitKey(1);
            }

        }else{
        }
    }
   
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
    ofstream myfile;
public:
    PublisherNode(Pos_raw1 * pos, ofstream& file)
        : Node("PlayerDetectionPublisher"), count_(0), pos_raw(pos), flag(0), myfile(&file)
    {

        publisher_ = this->create_publisher<ap_interfaces::msg::Pos>("pos_raw", 10);
        auto timer_callback =
            [this]() -> void {
            auto message = ap_interfaces::msg::Pos();
            
            //message.data = "Raw Position! " + std::to_string(this->count_++);

            // Extract current thread
            message.total = pos_raw->total;
            rclcpp::Time time = this->now();
            message.timestamp = time.nanoseconds();
            //cout << (double)time_prev << endl;
            if (flag != 0){

                duration_arr.push_back((double)(time.nanoseconds() - time_prev.nanoseconds()));
                myfile << time.nanoseconds()<<endl;
                time_prev = time;
                sum = std::accumulate(std::begin(duration_arr), std::end(duration_arr), 0.0);
                mean_time =  sum / duration_arr.size(); 

            }else{
                time_prev = time;
                flag++;
            }
            
            (message.x)[0] = (pos_raw->x)[0];
            (message.y)[0] = (pos_raw->y)[0];

            // Extract current thread
            auto curr_thread = string_thread_id();
            
            std::string output = std::to_string(mean_time);
            // output += " ";
            // output += std::to_string(pos_raw->timestamp);
            // output += " ";
            // output += std::to_string((message.x)[0]);
            // output += " ";
            // output += std::to_string((message.y)[0]);

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
    rclcpp::Time time_prev;
    vector<double> duration_arr;
    double sum;
    double mean_time;
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
    myfile.open ("result.txt", ios::out);

    rclcpp::init(argc, argv);

    std::thread th_detect(detect_pos,&pos_raw);

    // You MUST use the MultiThreadedExecutor to use, well, multiple threads
    rclcpp::executors::MultiThreadedExecutor executor;
    auto player_detection_pubnode = std::make_shared<PublisherNode>(&pos_raw, &myfile);
    auto player_detection_subnode = std::make_shared<SingleThreadedNode>();  // This contains BOTH subscriber callbacks.
                                                          // They will still run on different threads
                                                          // One Node. Two callbacks. Two Threads
    executor.add_node(player_detection_pubnode);
    executor.add_node(player_detection_subnode);
    executor.spin();
    th_detect.join();
    rclcpp::shutdown();
    myfile.close();
    return 0;
}