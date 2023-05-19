#include "jni_bridge/jni_bridge.hpp"

JNIEXPORT void JNICALL Java_net_robot_wavem_publish_chatter_ChatterPublisher_publish_1to_1chatter(JNIEnv * j_env, jobject j_obj, jobjectArray j_chatter_message_array) {
    rclcpp::init(0, nullptr);
    auto node = std::make_shared<rclcpp::Node>("rclcpp_for_java", "chatter_publisher");
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher = node->create_publisher<std_msgs::msg::String>("/chatter", rclcpp::QoS(rclcpp::KeepLast(10)));

    jsize j_chatter_message_array_len = j_env->GetArrayLength(j_chatter_message_array);
    for(jsize i=0;i<j_chatter_message_array_len;i++) {
        jstring j_chatter_message = (jstring) j_env->GetObjectArrayElement(j_chatter_message_array, i);
        const char * c_chatter_message = j_env->GetStringUTFChars(j_chatter_message, nullptr);
        std::cout << "[JNI-Bridge] chatter message : " << c_chatter_message << '\n';
        publish_to_chatter(publisher, c_chatter_message);
        j_env->ReleaseStringUTFChars(j_chatter_message, c_chatter_message);
    }

    rclcpp::spin(node);
    rclcpp::shutdown();
}

JNIEXPORT void JNICALL Java_net_robot_wavem_subscription_chatter_ChatterSubscription_subscribe_1from_1chatter(JNIEnv * j_env, jobject j_obj) {
    rclcpp::init(0, nullptr);
    auto node = std::make_shared<rclcpp::Node>("rclcpp_for_java", "chatter_subscription");
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr chatter_subscription = node->create_subscription<std_msgs::msg::String>(
        "/chatter",
        rclcpp::QoS(rclcpp::KeepLast(10)),
        [](const std_msgs::msg::String::SharedPtr callback_chatter_message) {
            std::cout << "[JNI-Bridge] /chatter subscription callback : " << callback_chatter_message->data.c_str() << '\n';
        }
    );

    rclcpp::spin(node);
    rclcpp::shutdown();
}