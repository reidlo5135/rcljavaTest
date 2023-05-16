package net.robot.wavem.jni;

import java.io.File;

public class Jni {
    public native void rcljava_init(String node_name);
    public native void chatter_subscription(String topic_name);

    static {
        String soPath = "/home/wavem/vsWorkspace/rcljava/src/rclcpp_for_java/build/rclcpp_for_java/librclcpp_for_java_jni.so";
        File r = new File(soPath);
        System.load(r.getAbsolutePath());
    }

    public static void main(String args[]) {
        Jni jni = new Jni();
        String node_name = "tester_node";
        jni.rcljava_init(node_name);
        jni.chatter_subscription("/chatter");
    }
}