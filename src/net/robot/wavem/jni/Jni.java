package net.robot.wavem.jni;

import java.io.File;

public class Jni {
    public native void spin();
    public native void chatter_publish(String chatter_message);
    
    static {
        String soPath = "/home/wavem/vsWorkspace/rcljava/src/rclcpp_for_java/build/rclcpp_for_java/librclcpp_for_java_jni.so";
        File r = new File(soPath);
        System.load(r.getAbsolutePath());
    }

    private void publish_to_chatter() {
        String chatter_arr[] = {"hi", "hio", "askdfjalsdkfj", "qwqerqwer"};
        for(String chatter : chatter_arr) {
            System.out.println("[Chatter] publish to chatter with " + chatter);
            chatter_publish(chatter);
        }
    }

    public static void main(String args[]) {
        Jni jni = new Jni();
        jni.spin();
        jni.publish_to_chatter();
    }
}