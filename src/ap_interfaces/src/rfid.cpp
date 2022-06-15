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

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "ap_interfaces/msg/score.hpp"
#include "ap_interfaces/msg/pos.hpp"

using namespace std::chrono_literals;


struct Pos1
{
    int total;
    int timestamp;
   /* int[18] x;
    int[18] y;
    int[18] player_id;
    std::string[18] tag_id;
    int[18] size;*/

};

void randompos(Pos1* pos1) {
    while (true) {
        pos1->total = rand() % 3;
        pos1->timestamp = rand() % 10;
        std::this_thread::sleep_for(std::chrono::seconds(1));
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
    Pos1 * pos1;
public:
    PublisherNode(Pos1* pos)
        : Node("RFIDPublisher"), count_(0),pos1(pos)
    {
        publisher_ = this->create_publisher<ap_interfaces::msg::pos>("pos_true", 10);
        auto timer_callback =
            [this]() -> void {
            auto message = ap_interfaces::msg::pos();
            message.total = pos1->total;
            message.timestamp = pos1->timestamp;

            // Extract current thread
            auto curr_thread = string_thread_id();

            // Prep display message
            RCLCPP_INFO(
                this->get_logger(), "\n<<THREAD %s>> Publishing '%s'",
                curr_thread.c_str(), message.data.c_str());
            this->publisher_->publish(message);
        };
        timer_ = this->create_wall_timer(500ms, timer_callback);
    }

private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<ap_interfaces::msg::pos>::SharedPtr publisher_;
    size_t count_;
};

class DualThreadedNode : public rclcpp::Node
{
    
public:
    DualThreadedNode()
        : Node("RFIDSubscribers")
    {
        /* These define the callback groups
         * They don't really do much on their own, but they have to exist in order to
         * assign callbacks to them. They're also what the executor looks for when trying to run multiple threads
         */
        callback_group_subscriber1_ = this->create_callback_group(
            rclcpp::CallbackGroupType::MutuallyExclusive);
        callback_group_subscriber2_ = this->create_callback_group(
            rclcpp::CallbackGroupType::MutuallyExclusive);

        // Each of these callback groups is basically a thread
        // Everything assigned to one of them gets bundled into the same thread
        auto sub1_opt = rclcpp::SubscriptionOptions();
        sub1_opt.callback_group = callback_group_subscriber1_;
        auto sub2_opt = rclcpp::SubscriptionOptions();
        sub2_opt.callback_group = callback_group_subscriber2_;

        subscription1_ = this->create_subscription<std_msgs::msg::String>(
            "pos_raw",
            rclcpp::QoS(10),
            // std::bind is sort of C++'s way of passing a function
            // If you're used to function-passing, skip these comments
            std::bind(
                &DualThreadedNode::subscriber1_cb,  // First parameter is a reference to the function
                this,                               // What the function should be bound to
                std::placeholders::_1),             // At this point we're not positive of all the
                                                    // parameters being passed
                                                    // So we just put a generic placeholder
                                                    // into the binder
                                                    // (since we know we need ONE parameter)
            sub1_opt);                  // This is where we set the callback group.
                                        // This subscription will run with callback group subscriber1

        subscription2_ = this->create_subscription<std_msgs::msg::String>(
            "control",
            rclcpp::QoS(10),
            std::bind(
                &DualThreadedNode::subscriber2_cb,
                this,
                std::placeholders::_1),
            sub2_opt);
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
    void subscriber1_cb(const std_msgs::msg::String::SharedPtr msg)
    {
        auto message_received_at = timing_string();

        // Extract current thread
        RCLCPP_INFO(
            this->get_logger(), "THREAD %s => Heard '%s' at %s",
            string_thread_id().c_str(), msg->data.c_str(), message_received_at.c_str());
    }

    /**
     * This function gets called when Subscriber2 is poked
     * Since it's running on a separate thread than Subscriber 1, it will run at (more-or-less) the same time!
     */
    void subscriber2_cb(const std_msgs::msg::String::SharedPtr msg)
    {
        auto message_received_at = timing_string();

        // Prep display message
        RCLCPP_INFO(
            this->get_logger(), "THREAD %s => Heard '%s' at %s",
            string_thread_id().c_str(), msg->data.c_str(), message_received_at.c_str());
    }

    rclcpp::CallbackGroup::SharedPtr callback_group_subscriber1_;
    rclcpp::CallbackGroup::SharedPtr callback_group_subscriber2_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription1_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription2_;
};

int main(int argc, char* argv[])
{
    Pos1 pos1;
    rclcpp::init(argc, argv);
    thread th2(randompos,&pos1);
    // You MUST use the MultiThreadedExecutor to use, well, multiple threads
    rclcpp::executors::MultiThreadedExecutor executor;
    auto rfid_pubnode = std::make_shared<PublisherNode>(&pos1);
    auto rfid_subnode = std::make_shared<DualThreadedNode>();  // This contains BOTH subscriber callbacks.
                                                          // They will still run on different threads
                                                          // One Node. Two callbacks. Two Threads
    executor.add_node(rfid_pubnode);
    executor.add_node(rfid_subnode);
    executor.spin();
    rclcpp::shutdown();
    return 0;
}

