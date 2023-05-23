package net.robot.wavem.publisher.cmd_vel;

import java.io.File;
import java.util.HashMap;

public class CmdVelPublisher {
    private static final String SO_PATH = "../rcljava/src/rclcpp_for_java/build/rclcpp_for_java/librcljava_cmd_vel_connections.so";
    private native void publish_to_cmd_vel(HashMap<String, HashMap<String, Float>> defaultTwistHashMap);

    private CmdVelPublisher() {
        System.out.println("[RCLJava] /cmd_vel publisher is ready for RCLJava!!");
    }

    static {
        File soFile = new File(SO_PATH);
        System.load(soFile.getAbsolutePath());
    }

    private HashMap<String, HashMap<String, Float>> defaultTwistDataMap() {
        HashMap<String, HashMap<String, Float>> defaultHashMap = new HashMap<>();
        HashMap<String, Float> linearHashMap = new HashMap<>();
        HashMap<String, Float> angularHashMap = new HashMap<>();

        String linear = "linear";
        String angular = "angular";

        linearHashMap.put("x", 0.3f);
        linearHashMap.put("y", 0.0f);
        linearHashMap.put("z", 0.0f);

        angularHashMap.put("x", 0.0f);
        angularHashMap.put("y", 0.0f);
        angularHashMap.put("z", 0.3f);

        defaultHashMap.put(linear, linearHashMap);
        defaultHashMap.put(angular, angularHashMap);

        return defaultHashMap;
    }

    public static void main(String[] args) {
        CmdVelPublisher cmdVelPublisher = new CmdVelPublisher();
        HashMap<String, HashMap<String, Float>> defaultTwistHashMap = cmdVelPublisher.defaultTwistDataMap();
        cmdVelPublisher.publish_to_cmd_vel(defaultTwistHashMap);
    }
}