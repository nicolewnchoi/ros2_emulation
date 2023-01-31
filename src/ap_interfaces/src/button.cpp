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
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "ap_interfaces/msg/score.hpp"
#include "ap_interfaces/msg/pos.hpp"
#include "ap_interfaces/msg/button.hpp"

#include "common/utils.hpp"
#include "simpleble/SimpleBLE.h"

using namespace std;
using namespace std::chrono_literals;

int kick_control(bool * p) {

    ofstream myfile;
    myfile.open("kick_duration.txt", ios::out);
    myfile.close();

    /*
    sf::RenderWindow window(sf::VideoMode(500, 500), "Please move the mouse here!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            *(p) = NULL;
            *(p + 1) = NULL;
            switch (event.type)
            {
                // window closed
            case sf::Event::Closed:
                window.close();
                break;

                // key pressed
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {   
                    *(p) = 1;
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {   
                    *(p+1) = 1;
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
                break;

                // we don't process other types of events
            default:
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));;
        }

        window.clear();
        window.display();
    }
    */

    auto adapter_optional = Utils::getAdapter();

    if (!adapter_optional.has_value()) {
        return EXIT_FAILURE;
    }

    auto adapter = adapter_optional.value();


    /*
    std::vector<SimpleBLE::Peripheral> peripherals;
    peripherals = adapter.get_paired_peripherals();
    for (size_t i = 0; i < peripherals.size(); i++) {
        std::cout << "[" << i << "] " << peripherals[i].identifier() << " [" << peripherals[i].address() << "]"
                  << std::endl;
    }
    */


    SimpleBLE::Peripheral d1, d2;

    std::vector<char[10]> devices;

    adapter.set_callback_on_scan_found([&](SimpleBLE::Peripheral peripheral) {
        //std::cout << peripheral.identifier() << std::endl;

        if (peripheral.address() == "c0:49:ef:bd:37:72") {
            d1 = peripheral;
            //adapter.scan_stop();
        }
        else if (peripheral.address() == "c0:49:ef:bd:3a:c2") {
            d2 = peripheral;
        }
        //std::cout << "Found device: " << peripheral.identifier() << " [" << peripheral.address() << "]" << std::endl;
        //peripherals.push_back(peripheral);
        });

    adapter.set_callback_on_scan_start([]() { std::cout << "Scan started." << std::endl; });
    adapter.set_callback_on_scan_stop([]() { std::cout << "Scan stopped." << std::endl; });
    // Scan for 5 seconds and return.
    //adapter.scan_start();

    adapter.scan_for(5000);

    /*
    std::cout << "The following devices were found:" << std::endl;
    for (size_t i = 0; i < peripherals.size(); i++) {
        std::cout << "[" << i << "] " << peripherals[i].identifier() << " [" << peripherals[i].address() << "]"
                  << std::endl;
    }


    auto selection = Utils::getUserInputInt("Please select a device to connect to", peripherals.size() - 1);

    if (!selection.has_value()) {
        return EXIT_FAILURE;
    }

    auto peripheral = peripherals[selection.value()];
    */

    std::cout << "Connecting to " << d1.identifier() << " [" << d1.address() << "]" << std::endl;
    d1.connect();


    std::cout << "Connecting to " << d2.identifier() << " [" << d2.address() << "]" << std::endl;
    d2.connect();

    std::cout << "Successfully connected, printing services and characteristics.." << std::endl;

    // Store all service and characteristic uuids in a vector.

    /*
    std::vector<std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID>> uuids;
    for (auto service : d1.services()) {
        for (auto characteristic : service.characteristics()) {
            uuids.push_back(std::make_pair(service.uuid(), characteristic.uuid()));
        }
    }

    std::cout << "The following services and characteristics were found:" << std::endl;
    for (size_t i = 0; i < uuids.size(); i++) {
        std::cout << "[" << i << "] " << uuids[i].first << " " << uuids[i].second << std::endl;
    }


    selection = Utils::getUserInputInt("Select a characteristic to read", uuids.size() - 1);

    if (!selection.has_value()) {
        return EXIT_FAILURE;
    }
    */

    while (true) {
        SimpleBLE::ByteArray rx_data_1 = d1.read("4fafc201-1fb5-459e-8fcc-c5c9c331914b",
            "beb5483e-36e1-4688-b7f5-ea07361b26a8");

        SimpleBLE::ByteArray rx_data_2 = d2.read("4fafc201-1fb5-459e-8fcc-c5c9c331914b",
            "beb5483e-36e1-4688-b7f5-ea07361b26a8");

        std::cout << "Controller 1: ";
        Utils::print_byte_array(rx_data_1);
        std::cout << "Controller 2: ";
        Utils::print_byte_array(rx_data_2);
        std::this_thread::sleep_for(10ms);
    }

    d1.disconnect();
    d2.disconnect();

    return EXIT_SUCCESS;
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
    bool* pp;
public:
    PublisherNode(bool * p)
        : Node("ButtonPublisher"), count_(0), pp(p)
    {
        publisher_ = this->create_publisher<ap_interfaces::msg::Button>("kick_size", 10);
        auto timer_callback =
            [this]() -> void {
            auto message = ap_interfaces::msg::Button();

            for (int i = 0; i < 2; i++) {
                message.kick[i] = *(pp + i);
            }
            // Extract current thread
            auto curr_thread = string_thread_id();

            std::string output;
            // output += " ";
            // output += std::to_string(pos_raw->timestamp);
            output += " ";
            for (int i = 0; i<2; i++) {
                output += std::to_string(*(pp + i));
            }

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
    rclcpp::Publisher<ap_interfaces::msg::Button>::SharedPtr publisher_;
    size_t count_;
};


class SingleThreadedNode : public rclcpp::Node
{
public:
    SingleThreadedNode()
        : Node("ButtonSubscriber")
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
    bool kick_data[32];
    bool* p;

    p = kick_data;

    rclcpp::init(argc, argv);

    std::thread th_kick(kick_control, p);

    // You MUST use the MultiThreadedExecutor to use, well, multiple threads
    rclcpp::executors::MultiThreadedExecutor executor;
    auto button_pubnode = std::make_shared<PublisherNode>(p);
    auto button_subnode = std::make_shared<SingleThreadedNode>();  // This contains BOTH subscriber callbacks.
                                                          // They will still run on different threads
                                                          // One Node. Two callbacks. Two Threads
    executor.add_node(button_pubnode);
    executor.add_node(button_subnode);
    executor.spin();
    th_kick.join();
    rclcpp::shutdown();
    return 0;
}