#ifndef RCLJAVA_COMMON_CONNECTIONS
#define RCLJAVA_COMMON_CONNECTIONS

#include <cstdlib>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"

#define DEFAULT_ARGC 0
#define DEFAULT_ARGV nullptr 
#define DEFAULT_NODE_NAME "rcljava"
#define DEFAULT_QOS 10

#define J_STRING "S"
#define J_DOUBLE "D"
#define J_FLOAT "F"

#define J_VOID "V"

#define CHATTER_PUBLISHER_NODE_NAME "chatter_publisher"
#define CHATTER_SUBSCRIPTION_NODE_NAME "chatter_subscription"
#define CHATTER_TOPIC_NAME "/chatter"
#define CHATTER_CALLBACK_METHOD_NAME "chatterSubscriptionCallback"

#define CMD_VEL_PUBLISHER_NODE_NAME "cmd_vel_publisher"
#define CMD_VEL_SUBSCRIPTION_NODE_NAME "cmd_vel_subscription"
#define CMD_VEL_TOPIC_NAME "/cmd_vel"
#define CMD_VEL_CALLBACK_METHOD_NAME "cmdVelSubscriptionCallback"

#define J_TWIST_LINEAR_X "linearX"
#define J_TWIST_LINEAR_Y "linearY"
#define J_TWIST_LINEAR_Z "linearZ"
#define J_TWIST_ANGULAR_X "angularX"
#define J_TWIST_ANGULAR_Y "angularY"
#define J_TWIST_ANGULAR_Z "angularZ"

#define ODOM_SUBSCRIPTION_NODE_NAME "odom_subscription"
#define ODOM_TOPIC_NAME "/odom"
#define ODOM_CALLBACK_METHOD_NAME "odomSubscriptionCallback"

double cast_jdouble_to_double(jdouble c_double) {
    return static_cast<double>(c_double);
}

#endif