# RCLJava

## Git Clone
```bash
git clone https://github.com/reidlo5135/rcljava.git
```

## Compile cpp into so (CMake)
```bash
cd ${your workspace}/rcljava/src/rclcpp_for_java
colcon build --symlink-install
```

## Test ROS2 /chatter in Java
### ROS2 /chatter publishing
run ROS2 demo listener node
```bash
ros2 run demo_nodes_py listener
```
run ChatterPublisher.java
```bash
cd ${your workspace}/rcljava; /usr/bin/env /usr/lib/jvm/java-8-openjdk-amd64/bin/java -cp ${your workspace}/rcljava/bin net.robot.wavem.publisher.chatter.ChatterPublisher
```
check your result in ROS2 demo listener node
```bash
[INFO] [1684547636.811141065] [listener]: I heard: [a]
[INFO] [1684547636.812233860] [listener]: I heard: [b]
[INFO] [1684547636.812883783] [listener]: I heard: [c]
[INFO] [1684547636.813470788] [listener]: I heard: [d]
.
.
.
```

### ROS2 /chatter subscription
run ROS2 demo talker node
```bash
ros2 run demo_nodes_cpp talker
```
run ChatterSubscription.java
```bash
cd ${your workspace}/rcljava; /usr/bin/env /usr/lib/jvm/java-8-openjdk-amd64/bin/java -cp ${your workspace}/rcljava/bin net.robot.wavem.subscription.chatter.ChatterSubscription
```
check your result in ROS2 demo talker node
```bash
[RCLJava] chatter subscription callback chatter : Hello World: 743
[RCLJava] chatter subscription callback chatter : Hello World: 744
[RCLJava] chatter subscription callback chatter : Hello World: 745
[RCLJava] chatter subscription callback chatter : Hello World: 746
[RCLJava] chatter subscription callback chatter : Hello World: 747
[RCLJava] chatter subscription callback chatter : Hello World: 748
[RCLJava] chatter subscription callback chatter : Hello World: 749
```