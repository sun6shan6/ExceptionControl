//
// Created by sgs on 19-12-4.
//

#ifndef EXCEPTIONCONTROL_LOGUTILS_H
#define EXCEPTIONCONTROL_LOGUTILS_H

#include <iostream>
#include "../Signal.h"
#define TAG "default"
//#define ANDROID 123
#ifdef ANDROID
#include <android/log.h>
#include <jni.h>

#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#else
#define ALOGD(...) std::cout << __VA_ARGS__ << std::endl;
#endif

static void printSignal(std::string s, Signal signal){
    char string[180];
    sprintf(string, "%s Signal %d  timestamp %ld", s.c_str(), signal.getSignal(), signal.getTimestamp());
    ALOGD(string);
}



#endif //EXCEPTIONCONTROL_LOGUTILS_H
