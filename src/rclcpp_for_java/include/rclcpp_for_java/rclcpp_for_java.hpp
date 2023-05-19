#ifndef RCLCPP_FOR_JAVA
#define RCLCPP_FOR_JAVA

#include <iostream>
#include <cstring>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

void publish_to_chatter(rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher, const std::string& message);

#endif