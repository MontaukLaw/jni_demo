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

    env->DeleteLocalRef(newValue);    // 第五步 释放资源
    // 已测试可用
}

// 这个函数的意义是有形参, 把Java对象中的field传参进来, 然后同时有输出
extern "C"
JNIEXPORT jint JNICALL
Java_com_wulala_myjnidemo_MainActivity_plusOne(JNIEnv *env, jobject thiz, jint number) {
    return number + 1;    // 可见有传参的情况下, 无需那么多jni的调用.
}

// 这个函数调用了Java的一个没有形参没有返回值的method
// 最终现象是在Java的logd中输出.
extern "C"
JNIEXPORT void JNICALL
Java_com_wulala_myjnidemo_MainActivity_callJavaMethod(JNIEnv *env, jobject thiz) {

    jclass mainActivityClass = env->GetObjectClass(thiz);  // 第一步, 获取MainActivity类

    jmethodID methodFieldFid = env->GetMethodID(mainActivityClass, "callByC", "()V");  // 第二步, 获取Java中method的fid

    env->CallVoidMethod(thiz, methodFieldFid);    // 第三步, 调用

}

extern "C"
JNIEXPORT void JNICALL
Java_com_wulala_myjnidemo_MainActivity_changePersonZero(JNIEnv *env, jobject thiz, jobject person) {

    jclass personClass = env->GetObjectClass(person);   // 第一步 获取java类

    jstring personName = env->NewStringUTF("Wong");   // 第二步 新建一个jstring

    jmethodID setNameMethodFid = env->GetMethodID(personClass, "setName", "(Ljava/lang/String;)V");   // 第三步 获取java类的setName方法

    env->CallVoidMethod(person, setNameMethodFid, personName);   // 第四步, 用这个java method给java对象赋值

    env->DeleteLocalRef(personName);   // 第五步 释放资源

}
extern "C"
JNIEXPORT jobject JNICALL
Java_com_wulala_myjnidemo_MainActivity_createPerson(JNIEnv *env, jobject thiz) {

    jclass personClass = env->FindClass("com/wulala/myjnidemo/entity/Person");   // 第一步 获取类

    jobject personObj = env->AllocObject(personClass);     // 第二步 相当于new一个对象, 用c来说就是malloc

    jstring personName = env->NewStringUTF("Jacky");   // 第三步 准备设置name
    jint age = 11;                                           // 第四步 相当于new一个age对象, 需要释放么?

    jmethodID setNameMethodFid = env->GetMethodID(personClass, "setName", "(Ljava/lang/String;)V");   // 第五步 获取setName method
    jmethodID setAgeMethodFid = env->GetMethodID(personClass, "setAge", "(I)V");                      // 第五步 获取 setAge method

    env->CallVoidMethod(personObj, setNameMethodFid, personName);   // 第六步 用这个java method给java对象赋值
    env->CallVoidMethod(personObj, setAgeMethodFid, age);           // 第六步 用这个java method给java对象赋值

    env->DeleteLocalRef(personName);   // 第七步 释放资源

    return personObj;
}