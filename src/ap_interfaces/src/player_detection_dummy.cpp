#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <stdlib.h>
#include <utility>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "ap_interfaces/msg/score.hpp"
#include "ap_interfaces/msg/pos.hpp"

using namespace std;
using namespace std::chrono_literals;
using namespace std::chrono;

/* Publishing node like the one in minimal_publisher. */
class PublisherNode : public rclcpp::Node
{
    ap_interfaces::msg::Pos * pos_raw;
public:
    PublisherNode(ap_interfaces::msg::Pos * pos, double hz, list<std::pair<int,int>> &waypoints)
        : Node("PlayerDetectionPublisher"),  pos_raw(pos), hz_(hz), waypoints(waypoints), count_(0)
    {
        publisher_ = this->create_publisher<ap_interfaces::msg::Pos>("pos_raw", 10);
        timer_ = this->create_wall_timer(milliseconds(static_cast<long int>(1000/hz_)), std::bind(&PublisherNode::timer_callback,this));
    }

private:
    void timer_callback()
    {
        count_++;
        ap_interfaces::msg::Pos message = ap_interfaces::msg::Pos();
        
        int x = waypoints.front().first;
        int y = waypoints.front().second;
        (message.x)[0] = x;       //(pos_raw->x)[i];
        (message.y)[0] = y;       //(pos_raw->y)[i];
        (message.size)[0] = 30;    //(pos_raw->size)[i];
        message.id = count_;    //use the count as an id
        message.total = 1;          //pos_raw->total;

        // keep cycling the list by pushing and popping
        waypoints.emplace_back(std::make_pair(x,y));
        waypoints.pop_front();
        //yeah the waypoint list manipulation is rather crude, but just needs to work rn

        RCLCPP_INFO(this->get_logger(), "Dummy|Msg#:'%d' x:%d y:%d", count_, x, y);
        
        //lets ad the time this message was published to the message so qwe can compare inside 
        // unity
        //https://stackoverflow.com/questions/31255486/how-do-i-convert-a-stdchronotime-point-to-long-and-back
        auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
        auto value = start.time_since_epoch();
        double duration = value.count();
        // cout.precision(20);
        // cout << duration << "\n";
        message.ms = duration;    //set the system time the message is sent
        //
        
        publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<ap_interfaces::msg::Pos>::SharedPtr publisher_;
    size_t count_;
    double hz_;
    list<std::pair<int,int>> &waypoints;
};


int main(int argc, char* argv[])
{
    ap_interfaces::msg::Pos pos_raw;

    // Create default frequency for timer to update the dummy player position
    double desired_hz = 60;

    rclcpp::init(argc, argv);
    // Perform some simply argument parsing
    //If we received input arguments for desired hz, update it
    if(argc==1){}
    else if(argc==2){
        desired_hz = (double)atof(argv[1]);
    } else {
        cout << "Usage: no arguments (default timer is " << desired_hz <<
            "hz) or single input argument for hz.\n";
        return 1;
    }
    cout << "This program is a simple ros2 publisher that outputs an x,y position," 
         << "cycling through a list of waypoints, attempting a frequency corresponding to the"
        << "input argument hz or a default hz if non specified.\n";
    cout << "Running timer with hz set to " << desired_hz << ".\n";


    // Waypoints to move between, subject to demo table, may not work with full setup
    list<std::pair<int,int>> waypoints = {
        std::make_pair(180,400),
        std::make_pair(180,80),
        std::make_pair(500,80),
        std::make_pair(500,400)};
        // std::make_pair(280,240)}; //close to center for hitting ball

    rclcpp::spin(std::make_shared<PublisherNode>(&pos_raw, desired_hz, waypoints)); 
    rclcpp::shutdown();
    return 0;
}