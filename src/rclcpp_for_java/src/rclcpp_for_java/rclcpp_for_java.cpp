#include "rclcpp_for_java/rclcpp_for_java.hpp"

RclcppNode::RclcppNode(const char * node_name)
: Node(node_name) {
    std::cout << "[RCLCPP for JAVA] rcljava initialized with : " << node_name << '\n';
    ros_node_ptr_ = std::shared_ptr<rclcpp::Node>(this, [](rclcpp::Node*){});
}

RclcppNode::~RclcppNode() {

}

void RclcppNode::chatter_subscription(const std::string& topic_name) {
    std::cout << "[RCLCPP for JAVA] chatter subscription topic name : " << topic_name << '\n';
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription = ros_node_ptr_->create_subscription<std_msgs::msg::String>(
        topic_name,
        rclcpp::QoS(rclcpp::KeepLast(10)),
        [this](const std_msgs::msg::String::SharedPtr callback_std_msgs) {
            std::cout << "[RCLCPP for JAVA] chatter subscription callback " << callback_std_msgs->data.c_str() << '\n';
        }
    );
}

int main(int argc, char** argv) {
    return 0;
}