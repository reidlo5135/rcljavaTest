#include "cmd_vel/rcljava_cmd_vel_connections.hpp"

JNIEXPORT void JNICALL Java_net_robot_wavem_publisher_cmd_1vel_CmdVelPublisher_publish_1to_1cmd_1vel(JNIEnv * j_env, jobject j_obj, jobject j_twist) {
    jclass j_class = j_env->GetObjectClass(j_obj);
    jclass j_twist_class = j_env->GetObjectClass(j_twist);

    rclcpp::init(DEFAULT_ARGC, DEFAULT_ARGV);
    rclcpp::Node::SharedPtr node = std::make_shared<rclcpp::Node>(CMD_VEL_PUBLISHER_NODE_NAME, DEFAULT_NODE_NAME);
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr ros_cmd_vel_publisher_ptr = node->create_publisher<geometry_msgs::msg::Twist>(
        CMD_VEL_TOPIC_NAME,
        rclcpp::QoS(rclcpp::KeepLast(DEFAULT_QOS))
    );

    geometry_msgs::msg::Twist::SharedPtr twist_message_ptr = std::make_shared<geometry_msgs::msg::Twist>();

    jfieldID j_linear_x_field = j_env->GetFieldID(j_twist_class, "linearX", J_DOUBLE);
    jfieldID j_linear_y_field = j_env->GetFieldID(j_twist_class, "linearY", J_DOUBLE);
    jfieldID j_linear_z_field = j_env->GetFieldID(j_twist_class, "linearZ", J_DOUBLE);

    jfieldID j_angular_x_field = j_env->GetFieldID(j_twist_class, "angularX", J_DOUBLE);
    jfieldID j_angular_y_field = j_env->GetFieldID(j_twist_class, "angularY", J_DOUBLE);
    jfieldID j_angular_z_field = j_env->GetFieldID(j_twist_class, "angularZ", J_DOUBLE);

    jdouble j_linear_x = j_env->GetDoubleField(j_twist, j_linear_x_field);
    jdouble j_linear_y = j_env->GetDoubleField(j_twist, j_linear_y_field);
    jdouble j_linear_z = j_env->GetDoubleField(j_twist, j_linear_z_field);

    jdouble j_angular_x = j_env->GetDoubleField(j_twist, j_angular_x_field);
    jdouble j_angular_y = j_env->GetDoubleField(j_twist, j_angular_y_field);
    jdouble j_angular_z = j_env->GetDoubleField(j_twist, j_angular_z_field);

    double linear_x = static_cast<double>(j_linear_x);
    double linear_y = static_cast<double>(j_linear_y);
    double linear_z = static_cast<double>(j_linear_z);

    double angular_x = static_cast<double>(j_angular_x);
    double angular_y = static_cast<double>(j_angular_y);
    double angular_z = static_cast<double>(j_angular_z);

    twist_message_ptr->linear.x = linear_x;
    twist_message_ptr->linear.y = linear_y;
    twist_message_ptr->linear.z = linear_z;

    twist_message_ptr->angular.x = angular_x;
    twist_message_ptr->angular.y = angular_y;
    twist_message_ptr->angular.z = angular_z;

    std::cout << "[RCLCPP] /cmd_vel publish jdouble linear x : " << j_linear_x  << '\n';
    std::cout << "[RCLCPP] /cmd_vel publish twist linear x : " << twist_message_ptr->linear.x << '\n';

    std::cout << "[RCLCPP] /cmd_vel publish jdouble angular z : " << j_angular_z  << '\n';
    std::cout << "[RCLCPP] /cmd_vel publish twist angular z : " << twist_message_ptr->angular.z << '\n';

    ros_cmd_vel_publisher_ptr->publish(*twist_message_ptr);

    rclcpp::spin(node);
    rclcpp::shutdown();
}

JNIEXPORT void JNICALL Java_net_robot_wavem_subscription_cmd_1vel_CmdVelSubscription_subscribe_1from_1cmd_1vel(JNIEnv * j_env, jobject j_obj) {
    jclass j_class = j_env->GetObjectClass(j_obj);
    jclass j_twist_class = j_env->FindClass("net/robot/wavem/message/geometry/Twist");
    jmethodID j_twist_constructor = j_env->GetMethodID(j_twist_class, "<init>", "(DDDDDD)V");
    jobject j_twist_instance = j_env->NewObject(j_twist_class, j_twist_constructor);

    const char * j_callback_type = "(Lnet/robot/wavem/message/geometry/Twist;)V";
    jmethodID j_callback_method = j_env->GetMethodID(j_class, CMD_VEL_CALLBACK_METHOD_NAME, j_callback_type);

    rclcpp::init(DEFAULT_ARGC, DEFAULT_ARGV);
    rclcpp::Node::SharedPtr node = std::make_shared<rclcpp::Node>(CMD_VEL_SUBSCRIPTION_NODE_NAME, DEFAULT_NODE_NAME);
    auto c_callback_method = [j_env, j_obj, j_twist_class, j_twist_instance, j_callback_method](const geometry_msgs::msg::Twist::SharedPtr c_twist_callback_message) {
        jfieldID j_linear_x_field = j_env->GetFieldID(j_twist_class, "linearX", J_DOUBLE);
        jfieldID j_linear_y_field = j_env->GetFieldID(j_twist_class, "linearY", J_DOUBLE);
        jfieldID j_linear_z_field = j_env->GetFieldID(j_twist_class, "linearZ", J_DOUBLE);

        jfieldID j_angular_x_field = j_env->GetFieldID(j_twist_class, "angularX", J_DOUBLE);
        jfieldID j_angular_y_field = j_env->GetFieldID(j_twist_class, "angularY", J_DOUBLE);
        jfieldID j_angular_z_field = j_env->GetFieldID(j_twist_class, "angularZ", J_DOUBLE);
        
        double linear_x = c_twist_callback_message->linear.x;
        double linear_y = c_twist_callback_message->linear.y;
        double linear_z = c_twist_callback_message->linear.z;

        double angular_x = c_twist_callback_message->angular.x;
        double angular_y = c_twist_callback_message->angular.y;
        double angular_z = c_twist_callback_message->angular.z;

        j_env->SetDoubleField(j_twist_instance, j_linear_x_field, linear_x);
        j_env->SetDoubleField(j_twist_instance, j_linear_y_field, linear_y);
        j_env->SetDoubleField(j_twist_instance, j_linear_z_field, linear_z);

        j_env->SetDoubleField(j_twist_instance, j_angular_x_field, angular_x);
        j_env->SetDoubleField(j_twist_instance, j_angular_y_field, angular_y);
        j_env->SetDoubleField(j_twist_instance, j_angular_z_field, angular_z);

        j_env->CallVoidMethod(j_obj, j_callback_method, j_twist_instance);
    };

    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr ros_cmd_vel_subscription_ptr = node->create_subscription<geometry_msgs::msg::Twist>(
        CMD_VEL_TOPIC_NAME,
        rclcpp::QoS(rclcpp::KeepLast(DEFAULT_QOS)),
        c_callback_method
    );

    rclcpp::spin(node);
    rclcpp::shutdown();
}