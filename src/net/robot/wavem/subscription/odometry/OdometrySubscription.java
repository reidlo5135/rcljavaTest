package net.robot.wavem.subscription.odometry;

import java.io.File;

import net.robot.wavem.subscription.odometry.domain.Odometry;

public class OdometrySubscription {
    private static final String SO_PATH = "../rcljava/src/rclcpp_for_java/build/rclcpp_for_java/librcljava_odometry_connections.so";
    public native void subscribe_from_odom();

    private OdometrySubscription() {
        System.out.println("[RCLJava] /odom subscription is ready for RCLJava!!");
    }

    static {
        File soFile = new File(SO_PATH);
        System.load(soFile.getAbsolutePath());
    }

    public void odomSubscriptionCallback(Odometry odometry) {
        System.out.println("[RCLJava] odometry position x : " + odometry.getPositionX());
    }

    public static void main(String[] args) {
        OdometrySubscription odometrySubscription = new OdometrySubscription();
        odometrySubscription.subscribe_from_odom();
    }
}
