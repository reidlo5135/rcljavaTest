package net.robot.wavem.publisher.chatter;

import java.io.File;
import java.util.Arrays;

public class ChatterPublisher {
    private static final String SO_PATH = "../rcljava/src/rclcpp_for_java/build/rclcpp_for_java/librcljava_chatter_connections.so";
    public native void publish_to_chatter(String[] chatter_message_arr);

    private ChatterPublisher() {
        System.out.println("[RCLJava] /chatter publisher is ready for RCLJava!!");
    }

    static {
        File soFile = new File(SO_PATH);
        System.load(soFile.getAbsolutePath());
    }

    public static void main(String[] args) {
        ChatterPublisher publisher = new ChatterPublisher();
        String[] chatter_message_arr = {"a", "b", "c", "d"};
        System.out.println("[RCLJava-Publisher] chatter arr : " + Arrays.toString(chatter_message_arr));
        publisher.publish_to_chatter(chatter_message_arr);
    }
}