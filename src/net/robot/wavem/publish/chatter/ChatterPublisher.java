package net.robot.wavem.publish.chatter;

import java.io.File;
import java.util.Arrays;

public class ChatterPublisher {
    public native void publish_to_chatter(String[] chatter_message_arr);

    static {
        String soPath = "/home/wavem/vsWorkspace/rcljava/src/rclcpp_for_java/build/rclcpp_for_java/librclcpp_for_java_jni.so";
        File r = new File(soPath);
        System.load(r.getAbsolutePath());
    }

    public static void main(String[] args) {
        ChatterPublisher publisher = new ChatterPublisher();
        String[] chatter_message_arr = {"a", "b", "c", "d"};
        System.out.println("[RCLJava-Publisher] chatter arr : " + Arrays.toString(chatter_message_arr));
        publisher.publish_to_chatter(chatter_message_arr);
    }
}