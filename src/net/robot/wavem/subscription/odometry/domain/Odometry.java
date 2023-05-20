package net.robot.wavem.subscription.odometry.domain;

public class Odometry {
    private double positionX;
    private double positionY;
    private double positionZ;
    private double orientationX;
    private double orientationY;
    private double orientationZ;
    private double orientationW;

    public double getPositionX() {
        return positionX;
    }

    public void setPositionX(double positionX) {
        this.positionX = positionX;
    }
}
