#include "rclcpp_for_java/rclcpp_for_java.hpp"

RCLJava::RCLJava()
: Node("rclcpp_for_java") {
    ros_node_ptr_ = std::shared_ptr<rclcpp::Node>(this, [](rclcpp::Node*){});
    ros_chatter_publisher_ptr_ = ros_node_ptr_->create_publisher<std_msgs::msg::String>(
        "/chatter",
        rclcpp::QoS(rclcpp::KeepLast(10))
    );
    ros_chatter_subscription_ptr_ = ros_node_ptr_->create_subscription<std_msgs::msg::String>(
        "/chatter",
        rclcpp::QoS(rclcpp::KeepLast(10)),
        [this](const std_msgs::msg::String::SharedPtr callback_chatter_message) {
            const char * callback_chatter = callback_chatter_message->data.c_str();
            RCLCPP_INFO(ros_node_ptr_->get_logger(), "chatter callback : %s", callback_chatter);
        }
    );
}

RCLJava::~RCLJava() {

}

void RCLJava::chatter_publish(const std::string& chatter_message) {
    RCLCPP_INFO(ros_node_ptr_->get_logger(), "chatter_publish chatter_messgae : %s", chatter_message);
    std_msgs::msg::String chatter_publish_message = std_msgs::msg::String();
    chatter_publish_message.data = chatter_message;
    ros_chatter_publisher_ptr_->publish(chatter_publish_message);
}

void RCLJava::spin() {
    RCLCPP_INFO(ros_node_ptr_->get_logger(), "spin for java");
    rclcpp::spin(ros_node_ptr_);
    rclcpp::shutdown();
    return;
}

void rcljava_init(int argc, char** argv) {
    rclcpp::init(argc, argv);
}

int main(int argc, char** argv) {
    return 0;
}