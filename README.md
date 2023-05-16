# rclcpp-for-java

## Compile rclcpp_for_java
```bash
g++ -shared -o ./binary/libjni.so src/jni.cpp -I ./include -I /usr/lib/jvm/java-8-openjdk-amd64/include -I /usr/lib/jvm/java-8-openjdk-amd64/include/linux -fPIC
```

## Compile Java
```bash
cd /home/wavem/vsWorkspace/rcljava; /usr/bin/env /usr/lib/jvm/java-8-openjdk-amd64/bin/java -cp /home/wavem/vsWorkspace/rcljava/bin net.robot.wavem.jni.Jni
```