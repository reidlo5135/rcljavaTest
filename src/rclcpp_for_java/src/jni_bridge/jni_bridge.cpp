#include "jni_bridge/jni_bridge.hpp"

JNIEXPORT void JNICALL Java_net_robot_wavem_jni_Jni_spin(JNIEnv * j_env, jobject j_obj) {
    int argc = 0;
    char ** argv = nullptr;
    rcljava_init(argc, argv);
    RCLJava * rcl_java = new RCLJava();
    rcl_java->spin();
    delete rcl_java;
}

JNIEXPORT void JNICALL Java_net_robot_wavem_jni_Jni_chatter_1publish(JNIEnv * j_env, jobject j_obj, jstring j_chatter_message) {
    const char * chatter_message = j_env->GetStringUTFChars(j_chatter_message, nullptr);
    std::cout << "[JNI Bridge] chatter message : " << chatter_message << '\n';
    RCLJava * rcl_java;
    std::cout << "[JNI Bridge] publish into /chatter" << '\n';
    rcl_java->chatter_publish(chatter_message);
    j_env->ReleaseStringUTFChars(j_chatter_message, chatter_message);
}

JNIEXPORT void JNICALL Java_net_robot_wavem_jni_Jni_chatter_1subscription(JNIEnv * j_env, jobject j_obj, jstring j_topic_name) {
    
}