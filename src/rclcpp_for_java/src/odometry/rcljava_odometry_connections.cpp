#include "odometry/rcljava_odometry_connections.hpp"

JNIEXPORT void JNICALL Java_net_robot_wavem_subscription_odometry_OdometrySubscription_subscribe_1from_1odom(JNIEnv * j_env, jobject j_obj) {
    const char * j_callback_type = "(Ljava/lang/String;)V";
    jclass j_class = j_env->GetObjectClass(j_obj);
    jmethodID j_callback_method = j_env->GetMethodID(j_class, ODOM_CALLBACK_METHOD_NAME, j_callback_type);

    rclcpp::init(DEFAULT_ARGC, DEFAULT_ARGV);
    rclcpp::Node::SharedPtr node = std::make_shared<rclcpp::Node>(ODOM_SUBSCRIPTION_NODE_NAME, DEFAULT_NODE_NAME);
    auto c_callback_method = [j_env, j_obj, j_callback_method](const nav_msgs::msg::Odometry::SharedPtr c_odom_callback_message) {
        jclass j_odom_class = j_env->FindClass("net/robot/wavem/subscription/odometry/domain/Odometry");
        jmethodID j_odom_constructor = j_env->GetMethodID(j_odom_class, "<init>", "()V");

        jobject j_odom_instance = j_env->NewObject(j_odom_class, j_odom_constructor);

        jfieldID j_position_x_field = j_env->GetFieldID(j_odom_class, "positionX", "D");
        jfieldID j_position_y_field = j_env->GetFieldID(j_odom_class, "positionY", "D");
        jfieldID j_position_z_field = j_env->GetFieldID(j_odom_class, "positionZ", "D");

        jfieldID j_orientation_x_field = j_env->GetFieldID(j_odom_class, "orientationX", "D");
        jfieldID j_orientation_y_field = j_env->GetFieldID(j_odom_class, "orientationY", "D");
        jfieldID j_orientation_z_field = j_env->GetFieldID(j_odom_class, "orientationZ", "D");
        jfieldID j_orientation_w_field = j_env->GetFieldID(j_odom_class, "orientationW", "D");
        
        double position_x = c_odom_callback_message->pose.pose.position.x;
        double position_y = c_odom_callback_message->pose.pose.position.y;
        double position_z = c_odom_callback_message->pose.pose.position.z;

        double orientation_x = c_odom_callback_message->pose.pose.orientation.x;
        double orientation_y = c_odom_callback_message->pose.pose.orientation.y;
        double orientation_z = c_odom_callback_message->pose.pose.orientation.z;
        double orientation_w = c_odom_callback_message->pose.pose.orientation.w;

        j_env->SetDoubleField(j_odom_instance, j_position_x_field, position_x);
        j_env->SetDoubleField(j_odom_instance, j_position_y_field, position_y);
        j_env->SetDoubleField(j_odom_instance, j_position_z_field, position_z);
        j_env->SetDoubleField(j_odom_instance, j_orientation_x_field, orientation_x);
        j_env->SetDoubleField(j_odom_instance, j_orientation_y_field, orientation_y);
        j_env->SetDoubleField(j_odom_instance, j_orientation_z_field, orientation_z);
        j_env->SetDoubleField(j_odom_instance, j_orientation_w_field, orientation_w);


        j_env->CallVoidMethod(j_obj, j_callback_method, j_odom_instance);
    };

    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr ros_odom_subscription = node->create_subscription<nav_msgs::msg::Odometry>(
        ODOM_TOPIC_NAME,
        rclcpp::QoS(rclcpp::KeepLast(DEFAULT_QOS)),
        c_callback_method
    );

    rclcpp::spin(node);
    rclcpp::shutdown();
}