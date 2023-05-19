package net.robot.wavem.subscription.chatter;

import java.io.File;

public class ChatterSubscription {
    public native void subscribe_from_chatter();

    static {
        String soPath = "/home/wavem/vsWorkspace/rcljava/src/rclcpp_for_java/build/rclcpp_for_java/librclcpp_for_java_jni.so";
        File r = new File(soPath);
        System.load(r.getAbsolutePath());
    }

    public static void main(String[] args) {
        ChatterSubscription chatterSubscription = new ChatterSubscription();
        chatterSubscription.subscribe_from_chatter();
    }
}