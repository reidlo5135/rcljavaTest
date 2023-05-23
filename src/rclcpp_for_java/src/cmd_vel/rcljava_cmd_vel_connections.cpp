#include "cmd_vel/rcljava_cmd_vel_connections.hpp"

JNIEXPORT void JNICALL Java_net_robot_wavem_publisher_cmd_1vel_CmdVelPublisher_publish_1to_1cmd_1vel(JNIEnv * j_env, jobject j_obj, jobject j_twist_hash_map) {
    rclcpp::init(DEFAULT_ARGC, DEFAULT_ARGV);
    rclcpp::Node::SharedPtr node = std::make_shared<rclcpp::Node>(CMD_VEL_PUBLISHER_NODE_NAME, DEFAULT_NODE_NAME);
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr ros_cmd_vel_publisher_ptr = node->create_publisher<geometry_msgs::msg::Twist>(
        CMD_VEL_TOPIC_NAME,
        rclcpp::QoS(rclcpp::KeepLast(DEFAULT_QOS))
    );

    geometry_msgs::msg::Twist::SharedPtr twist_message_ptr = std::make_shared<geometry_msgs::msg::Twist>();

    jclass j_hash_map_class = j_env->FindClass("java/util/HashMap");
    jmethodID j_hash_map_get_method = j_env->GetMethodID(j_hash_map_class, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
    jmethodID j_hash_map_get_key_method = j_env->GetMethodID(j_hash_map_class, "keySet", "()Ljava/util/Set;");

    jclass j_set_class = j_env->FindClass("java/util/Set");
    jmethodID j_iterator_method = j_env->GetMethodID(j_set_class, "iterator", "()Ljava/util/Iterator;");

    jclass j_interator_class = j_env->FindClass("java/util/Iterator");
    jmethodID j_iterator_has_next_method = j_env->GetMethodID(j_interator_class, "hasNext", "()Z");
    jmethodID j_iterator_next_method = j_env->GetMethodID(j_interator_class, "next", "()Ljava/lang/Object;");

    jobject j_key_set_object = j_env->CallObjectMethod(j_twist_hash_map, j_hash_map_get_key_method);
    jobject j_iterator_key_set_object = j_env->CallObjectMethod(j_key_set_object, j_iterator_method);

    while (j_env->CallBooleanMethod(j_iterator_key_set_object, j_iterator_has_next_method)) {
        jobject j_key_object = j_env->CallObjectMethod(j_iterator_key_set_object, j_iterator_next_method);

        const char* c_key_object = j_env->GetStringUTFChars((jstring)j_key_object, NULL);
        std::string c_key(c_key_object);
        j_env->ReleaseStringUTFChars((jstring)j_key_object, c_key_object);

        jobject j_twist_value_hash_map = j_env->CallObjectMethod(j_twist_hash_map, j_hash_map_get_method, j_key_object);
        jclass j_value_hash_map_class = j_env->GetObjectClass(j_twist_value_hash_map);

        jmethodID j_value_hash_map_get_method = j_env->GetMethodID(j_value_hash_map_class, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");

        jobject j_value_key_set_object = j_env->CallObjectMethod(j_twist_value_hash_map, j_hash_map_get_key_method);
        jobject j_value_interator_key_set_object = j_env->CallObjectMethod(j_value_key_set_object, j_iterator_method);

        while (j_env->CallBooleanMethod(j_value_interator_key_set_object, j_iterator_has_next_method)) {
            jobject j_value_key_object = j_env->CallObjectMethod(j_value_interator_key_set_object, j_iterator_next_method);

            const char* c_value_key_object = j_env->GetStringUTFChars((jstring)j_value_key_object, NULL);
            std::string c_value_key(c_value_key_object);
            j_env->ReleaseStringUTFChars((jstring)j_value_key_object, c_value_key_object);

            jobject j_twist_value_object = j_env->CallObjectMethod(j_twist_value_hash_map, j_value_hash_map_get_method, j_value_key_object);

            if (j_env->IsInstanceOf(j_twist_value_object, j_env->FindClass("java/lang/Float"))) {
                jclass j_float_class = j_env->GetObjectClass(j_twist_value_object);
                jmethodID j_float_value_method = j_env->GetMethodID(j_float_class, "floatValue", "()F");
                float c_twist_value_float = j_env->CallFloatMethod(j_twist_value_object, j_float_value_method);

                if(c_key == J_TWIST_LINEAR_KEY) {
                    if(c_value_key == "x") {
                        std::cout << "[RCLCPP] twist value hash map linear x value : " << c_twist_value_float << '\n';
                        twist_message_ptr->linear.x = c_twist_value_float;
                    } else if (c_value_key == "y") {
                        twist_message_ptr->linear.y = c_twist_value_float;
                    } else {
                        twist_message_ptr->linear.z = c_twist_value_float;
                    }
                } else if (c_key == J_TWIST_ANGULAR_KEY) {
                    if(c_value_key == "x") {
                        twist_message_ptr->angular.x = c_twist_value_float;
                    } else if (c_value_key == "y") {
                        twist_message_ptr->angular.y = c_twist_value_float;
                    } else {
                        std::cout << "[RCLCPP] twist value hash map angular z value : " << c_twist_value_float << '\n';
                        twist_message_ptr->angular.z = c_twist_value_float;
                    }
                } else {
                    std::cerr << "[RCLCPP] is not a /cmd_vel type" << '\n';
                    return;
                }
            }
            j_env->DeleteLocalRef(j_twist_value_object);
        }
        j_env->DeleteLocalRef(j_twist_value_hash_map);
    }
    ros_cmd_vel_publisher_ptr->publish(*twist_message_ptr);

    rclcpp::spin(node);
    rclcpp::shutdown();
}

JNIEXPORT void JNICALL Java_net_robot_wavem_subscription_cmd_1vel_CmdVelSubscription_subscribe_1from_1cmd_1vel(JNIEnv * j_env, jobject j_obj) {
    jclass j_class = j_env->GetObjectClass(j_obj);
    jclass j_twist_class = j_env->FindClass("net/robot/wavem/domain/Twist");
    jmethodID j_twist_constructor = j_env->GetMethodID(j_twist_class, "<init>", "(FFFFFF)V");
    jobject j_twist_instance = j_env->NewObject(j_twist_class, j_twist_constructor);

    const char * j_callback_type = "(Lnet/robot/wavem/domain/Twist;)V";
    jmethodID j_callback_method = j_env->GetMethodID(j_class, CMD_VEL_CALLBACK_METHOD_NAME, j_callback_type);
    bool is_null = j_callback_method == NULL;

    rclcpp::init(DEFAULT_ARGC, DEFAULT_ARGV);
    rclcpp::Node::SharedPtr node = std::make_shared<rclcpp::Node>(CMD_VEL_SUBSCRIPTION_NODE_NAME, DEFAULT_NODE_NAME);
    auto c_callback_method = [j_env, j_obj, j_twist_class, j_twist_instance, j_callback_method](const geometry_msgs::msg::Twist::SharedPtr c_twist_callback_message) {
        jfieldID j_linear_x_field = j_env->GetFieldID(j_twist_class, "linearX", "F");
        jfieldID j_linear_y_field = j_env->GetFieldID(j_twist_class, "linearY", "F");
        jfieldID j_linear_z_field = j_env->GetFieldID(j_twist_class, "linearZ", "F");

        jfieldID j_angular_x_field = j_env->GetFieldID(j_twist_class, "angularX", "F");
        jfieldID j_angular_y_field = j_env->GetFieldID(j_twist_class, "angularY", "F");
        jfieldID j_angular_z_field = j_env->GetFieldID(j_twist_class, "angularZ", "F");
        
        double linear_x = c_twist_callback_message->linear.x;
        double linear_y = c_twist_callback_message->linear.y;
        double linear_z = c_twist_callback_message->linear.z;

        double angular_x = c_twist_callback_message->angular.x;
        double angular_y = c_twist_callback_message->angular.y;
        double angular_z = c_twist_callback_message->angular.z;

        j_env->SetFloatField(j_twist_instance, j_linear_x_field, linear_x);
        j_env->SetFloatField(j_twist_instance, j_linear_y_field, linear_y);
        j_env->SetFloatField(j_twist_instance, j_linear_z_field, linear_z);

        j_env->SetFloatField(j_twist_instance, j_angular_x_field, angular_x);
        j_env->SetFloatField(j_twist_instance, j_angular_y_field, angular_y);
        j_env->SetFloatField(j_twist_instance, j_angular_z_field, angular_z);

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