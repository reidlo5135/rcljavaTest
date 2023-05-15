#include "jni.hpp"

JNIEXPORT void JNICALL Java_net_robot_wavem_jni_Jni_say_1hello(JNIEnv* env, jobject obj) {
    std::cout << "[RCLCPP FOR JAVA JNI]" << '\n';
}

void chatter_callback(const std_msgs::msg::String::SharedPtr msg) {
    std::cout << "[RCLCPP for JAVA JNI] Received message: " << msg->data << std::endl;
}

JNIEXPORT void JNICALL Java_net_robot_wavem_jni_Jni_chatter_1subscription(JNIEnv * env, jobject obj) {
    std::cout << "[RCLCPP for JAVA JNI] chatter subscription" << '\n';

    rclcpp::init(0, nullptr);
    auto node = std::make_shared<rclcpp::Node>("rclcpp_for_java_chatter");
    auto callback = [](const std_msgs::msg::String::SharedPtr msg) {
        chatter_callback(msg);
    };

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr ros_chatter_subscription_ptr = node->create_subscription<std_msgs::msg::String>(
        "/chatter", 
        rclcpp::QoS(rclcpp::KeepLast(10)), 
        chatter_callback
    );

    rclcpp::spin(node);
    rclcpp::shutdown();
}

int main(int argc, char** argv) {
    return 0;
}