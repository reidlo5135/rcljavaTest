cmake_minimum_required(VERSION 3.5)
project(rclcpp_for_java)

if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(
  include
  include/${PROJECT_NAME}
  /usr/local/include
  /usr/lib/jvm/java-8-openjdk-amd64/include
  /usr/lib/jvm/java-8-openjdk-amd64/include/linux
  ${JNI_INCLUDE_DIRS}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")

find_package(ament_cmake REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(rmw REQUIRED)
find_package(rcl REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(actionlib_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(nav2_msgs REQUIRED)
find_package(tf2_msgs REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(JNI REQUIRED)

add_library(rcljava_chatter_connections SHARED
  include/common/rcljava_common_connections.hpp
  include/chatter/rcljava_chatter_connections.hpp
  src/chatter/rcljava_chatter_connections.cpp
)

target_link_libraries(rcljava_chatter_connections
  ${JNI_LIBRARIES}
  ${rclcpp_LIBRARIES}
  ${std_msgs_LIBRARIES}
)

add_library(rcljava_odometry_connections SHARED
  include/common/rcljava_common_connections.hpp
  include/odometry/rcljava_odometry_connections.hpp
  src/odometry/rcljava_odometry_connections.cpp
)

target_link_libraries(rcljava_odometry_connections
  ${JNI_LIBRARIES}
  ${rclcpp_LIBRARIES}
  ${nav_msgs_LIBRARIES}
)

add_library(rcljava_cmd_vel_connections SHARED
  include/common/rcljava_common_connections.hpp
  include/cmd_vel/rcljava_cmd_vel_connections.hpp
  src/cmd_vel/rcljava_cmd_vel_connections.cpp
)

target_link_libraries(rcljava_cmd_vel_connections
  ${JNI_LIBRARIES}
  ${rclcpp_LIBRARIES}
  ${geometry_msgs_LIBRARIES}
)

install(TARGETS
  rcljava_chatter_connections
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()