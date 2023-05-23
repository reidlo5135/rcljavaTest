package net.robot.wavem.domain;

public class Twist {
    private float linearX;
    private float linearY;
    private float linearZ;
    private float angularX;
    private float angularY;
    private float angularZ;

    public Twist(float linearX, float linearY, float linearZ, float angularX, float angularY, float angularZ) {
        this.linearX = linearX;
        this.linearY = linearY;
        this.linearZ = linearZ;
        this.angularX = angularX;
        this.angularY = angularY;
        this.angularZ = angularZ;
    }

    public float getLinearX() {
        return linearX;
    }

    public void setLinearX(float linearX) {
        this.linearX = linearX;
    }

    public float getLinearY() {
        return linearY;
    }

    public void setLinearY(float linearY) {
        this.linearY = linearY;
    }

    public float getLinearZ() {
        return linearZ;
    }

    public void seLinearZ(float linearZ) {
        this.linearZ = linearZ;
    }

    public float getAngularX() {
        return angularX;
    }

    public void setAngularX(float angularX) {
        this.angularX = angularX;
    }

    public float getAngularY() {
        return angularY;
    }

    public void setAngularY(float angularY) {
        this.angularY = angularY;
    }

    public float getAngularZ() {
        return angularZ;
    }

    public void setAngularZ(float angularZ) {
        this.angularZ = angularZ;
    }
}
