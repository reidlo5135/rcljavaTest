#include "jni.hpp"

JNIEXPORT void JNICALL Java_net_robot_wavem_jni_Jni_say_1hello(JNIEnv* env, jobject obj) {
    std::cout << "[RCLCPP FOR JAVA JNI]" << '\n';
}

int main(int argc, char** argv) {
    return 0;
}