package net.robot.wavem.jni;

import java.io.File;

public class Jni {
    public native void say_hello();

    static {
        String soPath = "/home/wavem/vsWorkspace/rcljava/src/rclcpp_for_java/binary/libjni.so";
        File r = new File(soPath);
        System.load(r.getAbsolutePath());
    }

    public static void main(String args[]) {
        Jni jni = new Jni();
        jni.say_hello();
    }
}