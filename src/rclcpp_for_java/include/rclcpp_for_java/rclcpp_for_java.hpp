#ifndef RCLCPP_FOR_JAVA
#define RCLCPP_FOR_JAVA

#include <iostream>
#include <cstring>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class RclcppNode : public rclcpp::Node {
    private :
        std::shared_ptr<rclcpp::Node> ros_node_ptr_;
    public :
        RclcppNode(const char * node_name);
        virtual ~RclcppNode();
        void chatter_subscription(const std::string& topic_name);
};

#endif