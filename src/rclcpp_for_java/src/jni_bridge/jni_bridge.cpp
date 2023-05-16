#include "jni_bridge/jni_bridge.hpp"

JNIEXPORT void JNICALL Java_net_robot_wavem_jni_Jni_rcljava_1init(JNIEnv * j_env, jobject j_obj, jstring j_node_name) {
    rclcpp::init(0, nullptr);
    const char * node_name = j_env->GetStringUTFChars(j_node_name, nullptr);
    auto node = std::make_shared<RclcppNode>(node_name);
    rclcpp::spin(node);
    rclcpp::shutdown();
}

JNIEXPORT void JNICALL Java_net_robot_wavem_jni_Jni_chatter_1subscription(JNIEnv * j_env, jobject j_obj, jstring j_topic_name) {
    RclcppNode * rclcpp_node_ptr;
    
    const char * topic_name = j_env->GetStringUTFChars(j_topic_name, nullptr);
    std::cout << "[JNI BRIDGE] chatter subscription topic name : " << topic_name << '\n';
    rclcpp_node_ptr->chatter_subscription(topic_name);

    delete rclcpp_node_ptr;
}