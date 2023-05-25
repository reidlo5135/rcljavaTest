package net.robot.wavem.message.geometry;

public class Twist {
    private double linearX;
    private double linearY;
    private double linearZ;
    private double angularX;
    private double angularY;
    private double angularZ;

    public Twist() {

    };

    public Twist(double linearX, double linearY, double linearZ, double angularX, double angularY, double angularZ) {
        this.linearX = linearX;
        this.linearY = linearY;
        this.linearZ = linearZ;
        this.angularX = angularX;
        this.angularY = angularY;
        this.angularZ = angularZ;
    }

    public double getLinearX() {
        return linearX;
    }

    public void setLinearX(double linearX) {
        this.linearX = linearX;
    }

    public double getLinearY() {
        return linearY;
    }

    public void setLinearY(double linearY) {
        this.linearY = linearY;
    }

    public double getLinearZ() {
        return linearZ;
    }

    public void setLinearZ(double linearZ) {
        this.linearZ = linearZ;
    }

    public double getAngularX() {
        return angularX;
    }

    public void setAngularX(double angularX) {
        this.angularX = angularX;
    }

    public double getAngularY() {
        return angularY;
    }

    public void setAngularY(double angularY) {
        this.angularY = angularY;
    }

    public double getAngularZ() {
        return angularZ;
    }

    public void setAngularZ(double angularZ) {
        this.angularZ = angularZ;
    }
}
