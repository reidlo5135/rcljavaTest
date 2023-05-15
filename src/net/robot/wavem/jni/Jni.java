package net.robot.wavem.jni;

import java.io.File;

public class Jni {
    public native void say_hello();
    public native void chatter_subscription();

    static {
        // String soPath = "/home/wavem/vsWorkspace/rcljava/src/rclcpp_for_java/binary/libjni.so";
        String soPath = "/home/wavem/vsWorkspace/rcljava/src/rclcpp_for_java/build/rclcpp_for_java/librclcpp_for_java_jni.so";
        File r = new File(soPath);
        System.load(r.getAbsolutePath());
    }

    public static void main(String args[]) {
        Jni jni = new Jni();
        jni.say_hello();
        jni.chatter_subscription();
    }
}