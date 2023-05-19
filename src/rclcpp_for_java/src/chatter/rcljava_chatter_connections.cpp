#include "chatter/rcljava_chatter_connections.hpp"

JNIEXPORT void JNICALL Java_net_robot_wavem_publish_chatter_ChatterPublisher_publish_1to_1chatter(JNIEnv * j_env, jobject j_obj, jobjectArray j_chatter_message_array) {
    rclcpp::init(0, nullptr);
    auto node = std::make_shared<rclcpp::Node>("rclcpp_for_java", "chatter_publisher");
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher = node->create_publisher<std_msgs::msg::String>("/chatter", rclcpp::QoS(rclcpp::KeepLast(10)));

    jsize j_chatter_message_array_len = j_env->GetArrayLength(j_chatter_message_array);
    for(jsize i=0;i<j_chatter_message_array_len;i++) {
        jstring j_chatter_message = (jstring) j_env->GetObjectArrayElement(j_chatter_message_array, i);
        const char * c_chatter_message = j_env->GetStringUTFChars(j_chatter_message, nullptr);
        std::cout << "[JNI-Bridge] chatter message : " << c_chatter_message << '\n';
        std_msgs::msg::String publish_message = std_msgs::msg::String();
        publish_message.data = c_chatter_message;
        publisher->publish(publish_message);
        j_env->ReleaseStringUTFChars(j_chatter_message, c_chatter_message);
    }

    rclcpp::spin(node);
    rclcpp::shutdown();
}

JNIEXPORT void JNICALL Java_net_robot_wavem_subscription_chatter_ChatterSubscription_subscribe_1from_1chatter(JNIEnv * j_env, jobject j_obj) {
    jclass j_class = j_env->GetObjectClass(j_obj);
    jmethodID j_callback_method = j_env->GetMethodID(j_class, "chatterSubscriptionCallback", "(Ljava/lang/String;)V");

    rclcpp::init(0, nullptr);
    auto node = std::make_shared<rclcpp::Node>("rclcpp_for_java", "chatter_subscription");
    auto callback = [j_env, j_obj, j_callback_method](const std_msgs::msg::String::SharedPtr c_message) {
        jstring j_message = j_env->NewStringUTF(c_message->data.c_str());
        j_env->CallVoidMethod(j_obj, j_callback_method, j_message);
        j_env->DeleteLocalRef(j_message);
    };

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr ros_chatter_subscription_ = node->create_subscription<std_msgs::msg::String>(
        "/chatter",
        rclcpp::QoS(rclcpp::KeepLast(10)),
        callback
    );

    rclcpp::spin(node);
    rclcpp::shutdown();
}