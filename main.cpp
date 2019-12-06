#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "utils/LogUtils.h"
#include <thread>
#include <sys/time.h>
#include "Signal.h"
#include "Control.h"


void fun() {
    srand((int)time(0));
    Control control;
    while(true) {
        int n = rand() % 3;
        struct timeval tv;
        gettimeofday(&tv, NULL);
        long time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        Signal signal = Signal(n, time_ms);
        control.watch(signal);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    ALOGD("PRINT");
    std::cout << "1234" << std::endl;
//    std::thread trigger = std::thread(&fun);
    fun();
    return 0;
}

