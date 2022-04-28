#include <jni.h>
#include <stdlib.h> // for NULL
#include "include/android_log.h"


#ifdef __cplusplus
extern "C" {
#endif

int a = 0;



JNIEXPORT jint JNICALL Java_com_wes_myjnitest_TestUtil_myInit
        (JNIEnv *env, jobject obj, jint nsHandler){
    LOGI(" test jni init!!! %d", nsHandler);
    return 1;
}



JNIEXPORT jint JNICALL Java_com_wes_myjnitest_TestUtil_myRead
        (JNIEnv *env, jobject obj, jbyteArray rData){


    return a;
}



JNIEXPORT jint JNICALL Java_com_wes_myjnitest_TestUtil_myWrite
        (JNIEnv *env, jobject obj, jbyteArray wData){

    char *in = nullptr;

    in = reinterpret_cast<char *>((*env).GetByteArrayElements(wData, NULL));

    for(char i = 0; i < 100; i++)
    {
        in[i] = 55;
    }


    (*env).ReleaseByteArrayElements(wData, reinterpret_cast<jbyte *>(in), 0);
    return 1;
}



#ifdef __cplusplus
}
#endif