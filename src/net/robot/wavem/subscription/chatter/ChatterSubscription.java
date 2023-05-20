package net.robot.wavem.subscription.chatter;

import java.io.File;

public class ChatterSubscription {
    private static final String SO_PATH = "../rcljava/src/rclcpp_for_java/build/rclcpp_for_java/librcljava_chatter_connections.so";
    public native void subscribe_from_chatter();

    static {
        File soFile = new File(SO_PATH);
        System.load(soFile.getAbsolutePath());
    }

    void chatterSubscriptionCallback(String callbackChatterData) {
        System.out.println("[RCLJava] chatter subscription callback chatter : " + callbackChatterData);
    }

    public static void main(String[] args) {
        ChatterSubscription chatterSubscription = new ChatterSubscription();
        chatterSubscription.subscribe_from_chatter();
    }
}