package net.robot.wavem.publisher.cmd_vel;

import java.io.File;
import net.robot.wavem.message.geometry.Twist;

public class CmdVelPublisher {
    private static final String SO_PATH = "../rcljava/src/rclcpp_for_java/build/rclcpp_for_java/librcljava_cmd_vel_connections.so";
    private native void publish_to_cmd_vel(Twist twist);

    private CmdVelPublisher() {
        System.out.println("[RCLJava] /cmd_vel publisher is ready for RCLJava!!");
    }

    static {
        File soFile = new File(SO_PATH);
        System.load(soFile.getAbsolutePath());
    }

    private Twist setTwist() {
        Twist twist = new Twist();
        twist.setLinearX(0.3);
        twist.setLinearY(0.0);
        twist.setLinearZ(0.0);

        twist.setAngularX(0.0);
        twist.setAngularY(0.0);
        twist.setAngularZ(0.3);

        return twist;
    }

    public static void main(String[] args) {
        CmdVelPublisher cmdVelPublisher = new CmdVelPublisher();
        Twist twist = cmdVelPublisher.setTwist();
        cmdVelPublisher.publish_to_cmd_vel(twist);
    }
}