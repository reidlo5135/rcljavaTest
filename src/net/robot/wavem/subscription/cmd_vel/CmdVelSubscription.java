package net.robot.wavem.subscription.cmd_vel;

import java.io.File;

import net.robot.wavem.domain.Twist;

public class CmdVelSubscription {
    private static final String SO_PATH = "../rcljava/src/rclcpp_for_java/build/rclcpp_for_java/librcljava_cmd_vel_connections.so";
    private native void subscribe_from_cmd_vel();

    public CmdVelSubscription() {
        System.out.println("[RCLJava] /cmd_vel subscription is ready for RCLJava!!");
    }

    static {
        File soFile = new File(SO_PATH);
        System.load(soFile.getAbsolutePath());
    }

    void cmdVelSubscriptionCallback(Twist twist) {
        float linearX = twist.getLinearX();
        float linearY = twist.getLinearY();
        float linearZ = twist.getLinearZ();
        float angularX = twist.getAngularX();
        float angularY = twist.getAngularY();
        float angularZ = twist.getAngularZ();

        System.out.println("[RCLJava] /cmd_vel subscription callback linear x : " + linearX);
        System.out.println("[RCLJava] /cmd_vel subscription callback linear y : " + linearY);
        System.out.println("[RCLJava] /cmd_vel subscription callback linear z : " + linearZ);
        System.out.println("[RCLJava] /cmd_vel subscription callback angular x : " + angularX);
        System.out.println("[RCLJava] /cmd_vel subscription callback angular y : " + angularY);
        System.out.println("[RCLJava] /cmd_vel subscription callback angular z : " + angularZ);
    }

    public static void main(String[] args) {
        CmdVelSubscription cmdVelSubscription = new CmdVelSubscription();
        cmdVelSubscription.subscribe_from_cmd_vel();
    }
}