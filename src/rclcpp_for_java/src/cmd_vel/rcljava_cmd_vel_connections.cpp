#include "cmd_vel/rcljava_cmd_vel_connections.hpp"

JNIEXPORT void JNICALL Java_net_robot_wavem_publisher_cmd_1vel_CmdVelPublisher_publish_1to_1cmd_1vel(JNIEnv * j_env, jobject j_obj) {
    std::cout << "[RCLJava] /cmd_vel publisher" << '\n';
    rclcpp::init(DEFAULT_ARGC, DEFAULT_ARGV);
    rclcpp::Node::SharedPtr node = std::make_shared<rclcpp::Node>(SUB_PUBLSIHER_NODE_NAME, DEFAULT_NODE_NAME);
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr ros_cmd_vel_publisher_ptr = node->create_publisher<geometry_msgs::msg::Twist>(
        DEFAULT_TOPIC_NAME,
        rclcpp::QoS(rclcpp::KeepLast(DEFAULT_QOS))
    );

    rclcpp::spin(node);
    rclcpp::shutdown();
}