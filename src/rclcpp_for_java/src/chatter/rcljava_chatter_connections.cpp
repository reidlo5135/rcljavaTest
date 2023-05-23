#include "chatter/rcljava_chatter_connections.hpp"

JNIEXPORT void JNICALL Java_net_robot_wavem_publisher_chatter_ChatterPublisher_publish_1to_1chatter(JNIEnv * j_env, jobject j_obj, jobjectArray j_chatter_message_array) {
    rclcpp::init(DEFAULT_ARGC, DEFAULT_ARGV);
    rclcpp::Node::SharedPtr node = std::make_shared<rclcpp::Node>(CHATTER_PUBLISHER_NODE_NAME, DEFAULT_NODE_NAME);
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr ros_chatter_publisher = node->create_publisher<std_msgs::msg::String>(CHATTER_TOPIC_NAME, rclcpp::QoS(rclcpp::KeepLast(DEFAULT_QOS)));

    jsize j_chatter_message_array_len = j_env->GetArrayLength(j_chatter_message_array);
    for(jsize i=0;i<j_chatter_message_array_len;i++) {
        jstring j_chatter_message = (jstring) j_env->GetObjectArrayElement(j_chatter_message_array, i);
        const char * c_chatter_message = j_env->GetStringUTFChars(j_chatter_message, nullptr);
        std::cout << "[RCLCPP] chatter message : " << c_chatter_message << '\n';
        std_msgs::msg::String publish_message = std_msgs::msg::String();
        publish_message.data = c_chatter_message;
        ros_chatter_publisher->publish(publish_message);
        j_env->ReleaseStringUTFChars(j_chatter_message, c_chatter_message);
    }

    rclcpp::spin(node);
    rclcpp::shutdown();
}

JNIEXPORT void JNICALL Java_net_robot_wavem_subscription_chatter_ChatterSubscription_subscribe_1from_1chatter(JNIEnv * j_env, jobject j_obj) {
    const char * j_callback_type = "(Ljava/lang/String;)V";
    jclass j_class = j_env->GetObjectClass(j_obj);
    jmethodID j_callback_method = j_env->GetMethodID(j_class, CHATTER_CALLBACK_METHOD_NAME, j_callback_type);

    rclcpp::init(DEFAULT_ARGC, DEFAULT_ARGV);
    rclcpp::Node::SharedPtr node = std::make_shared<rclcpp::Node>(CHATTER_SUBSCRIPTION_NODE_NAME, DEFAULT_NODE_NAME);
    auto c_callback_method = [j_env, j_obj, j_callback_method](const std_msgs::msg::String::SharedPtr c_chatter_callback_message) {
        jstring j_message = j_env->NewStringUTF(c_chatter_callback_message->data.c_str());
        j_env->CallVoidMethod(j_obj, j_callback_method, j_message);
        j_env->DeleteLocalRef(j_message);
    };

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr ros_chatter_subscription = node->create_subscription<std_msgs::msg::String>(
        CHATTER_TOPIC_NAME,
        rclcpp::QoS(rclcpp::KeepLast(DEFAULT_QOS)),
        c_callback_method
    );

    rclcpp::spin(node);
    rclcpp::shutdown();
}