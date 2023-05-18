#ifndef RCLCPP_FOR_JAVA
#define RCLCPP_FOR_JAVA

#include <iostream>
#include <cstring>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class RCLJava : public rclcpp::Node {
  private :
    std::shared_ptr<rclcpp::Node> ros_node_ptr_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr ros_chatter_publisher_ptr_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr ros_chatter_subscription_ptr_;
  public :
    RCLJava();
    virtual ~RCLJava();
    void spin();
    void chatter_publish(const std::string& chatter_message);
};

void rcljava_init(int argc, char** argv);

#endif