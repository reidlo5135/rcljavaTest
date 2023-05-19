#include "rclcpp_for_java/rclcpp_for_java.hpp"

void publish_to_chatter(rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher, const std::string& message) {
    std::cout << "[RCLCPP] chatter publish message : " << message << '\n';
    std_msgs::msg::String publish_message = std_msgs::msg::String();
    publish_message.data = message;
    publisher->publish(publish_message);
}

int main(void) {
    return 0;
}