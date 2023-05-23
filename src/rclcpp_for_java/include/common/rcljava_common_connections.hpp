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

#define CHATTER_PUBLISHER_NODE_NAME "chatter_publisher"
#define CHATTER_SUBSCRIPTION_NODE_NAME "chatter_subscription"
#define CHATTER_TOPIC_NAME "/chatter"
#define CHATTER_CALLBACK_METHOD_NAME "chatterSubscriptionCallback"

#define CMD_VEL_PUBLISHER_NODE_NAME "cmd_vel_publisher"
#define CMD_VEL_SUBSCRIPTION_NODE_NAME "cmd_vel_subscription"
#define CMD_VEL_TOPIC_NAME "/cmd_vel"
#define CMD_VEL_CALLBACK_METHOD_NAME "cmdVelSubscriptionCallback"
#define J_TWIST_LINEAR_KEY "linear"
#define J_TWIST_ANGULAR_KEY "angular"

#define ODOM_SUBSCRIPTION_NODE_NAME "odom_subscription"
#define ODOM_TOPIC_NAME "/odom"
#define ODOM_CALLBACK_METHOD_NAME "odomSubscriptionCallback"

#endif