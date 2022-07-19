#include <jni.h>
#include <string>

#include <android/log.h>

#define TAG "NATIVE_LIB"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__);

extern "C" JNIEXPORT jstring JNICALL
Java_com_wulala_myjnidemo_MainActivity_stringFromJNI(JNIEnv *env, jobject) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

// 这个函数的意义就是修改Java对象内的String类型的field.
extern "C" JNIEXPORT void JNICALL
Java_com_wulala_myjnidemo_MainActivity_changeText(JNIEnv *env, jobject thiz) {

    LOGD("Enter C .. \n");

    jclass mainActivityClass = env->GetObjectClass(thiz);  // 第一步, 获取MainActivity类

    jfieldID centerTextFid = env->GetFieldID(mainActivityClass, "centerText", "Ljava/lang/String;");   // 第二步, 获取centerText这个String对象的签名

    jstring newValue = env->NewStringUTF("Oh No!");   // 第三步, 生成一个新的jstring对象

    env->SetObjectField(thiz, centerTextFid, newValue);    // 第四步, 给java的field赋值

    // 已测试可用
}

// 这个函数的意义是有形参, 把Java对象中的field传参进来, 然后同时有输出
extern "C"
JNIEXPORT jint JNICALL
Java_com_wulala_myjnidemo_MainActivity_plusOne(JNIEnv *env, jobject thiz, jint number) {
    return number + 1;    // 可见有传参的情况下, 无需那么多jni的调用.
}