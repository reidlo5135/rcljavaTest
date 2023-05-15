# rclcpp-for-java

## Compile rclcpp_for_java
```bash
g++ -shared -o ./binary/libjni.so src/jni.cpp -I ./include -I /usr/lib/jvm/java-8-openjdk-amd64/include -I /usr/lib/jvm/java-8-openjdk-amd64/include/linux -fPIC
```