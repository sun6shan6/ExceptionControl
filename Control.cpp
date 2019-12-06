//
// Created by sgs on 19-11-28.
//

#include <thread>
#include "Control.h"

Control::Control() {
    mLooper = std::thread(&Control::looper, this);
}

bool Control::watch(Signal signal) {
    mCacheLock.lock();
    mCacheSignal.push_back(signal);
    mCacheLock.unlock();
    return false;
}

void Control::looper() {

    while (true) {
        while (!mCacheSignal.empty()) {
            mCacheLock.lock();
            Signal signal = mCacheSignal.back();
            mCacheSignal.pop_back();
            mCacheLock.unlock();
            if (updateException(signal)) {
                continue;
            }
            deleteOutDatedData(signal);

            std::map<int, SignalRecode, std::less<int>, std::allocator<std::pair<const int, SignalRecode>>>::iterator it;
            if (mSignalRecodes.size() > 0) {
                it = mSignalRecodes.find(signal.getSignal());
//                for (auto item: mSignalRecodes) {
//                    printSignal("auto print:", item.second.getSignal());
//                }
                if (it != mSignalRecodes.end()) {
                    SignalRecode recode = it->second;

                    if (signal.getTimestamp() - it->second.getSignal().getTimestamp() > RECOVER_INTERVAL) {                     //reset
                        printSignal("reset", signal);
                        mSignalRecodes.erase(signal.getSignal());
                        mSignalRecodes.insert(std::map<int,  SignalRecode>::value_type(signal.getSignal(), initRecode(signal)));
                    } else if (recode.getCount() > MAX_RECODE -1) {                                                             //warning
                        //todo warning
                        warning(signal);
                    } else {                                                                                                    //count
                        //count
                        char string[180];
                        printSignal(string, signal);
                        recode.setCount(recode.getCount() +1);
                        sprintf(string,"count %d", recode.getCount());
//                        mSignalRecodes.erase(signal.getSignal());
//                        mSignalRecodes.insert(std::map<int,  SignalRecode>::value_type(signal.getSignal(), recode));
                        it->second = recode;
                    }
                } else {
                    printSignal("init", signal);
                    mSignalRecodes.insert(std::map<int,  SignalRecode>::value_type(signal.getSignal(), initRecode(signal)));
                }
            } else {
                printSignal("first", signal);
                mSignalRecodes.insert(std::map<int,  SignalRecode>::value_type(signal.getSignal(), initRecode(signal)));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
}


Control::~Control() {

}

SignalRecode Control::initRecode(Signal signal) {
    return SignalRecode(signal, 0);
}

void Control::deleteOutDatedData(Signal signal) {
    if (mSignalRecodes.size() == 0) {
        return;
    }
    std::map<int, SignalRecode>::iterator iterator;
    for (iterator = mSignalRecodes.begin(); iterator != mSignalRecodes.end(); iterator++) {
        if (signal.getTimestamp() - iterator->second.getSignal().getTimestamp() > RECOVER_INTERVAL) {
            printSignal("deleteOutDatedData", iterator->second.getSignal());
            mSignalRecodes.erase(iterator);
        }
    }
}

bool Control::updateException(Signal signal) {

    std::map<int, Signal, std::less<int>, std::allocator<std::pair<const int, Signal>>>::iterator exceptionIt;
    if (mExceptionSignalRecodes.size() > 0) {                                    // check exception
        exceptionIt = mExceptionSignalRecodes.find(signal.getSignal());
        if (exceptionIt != mExceptionSignalRecodes.end()) {
            Signal exceptionSignal = exceptionIt->second;
            if (signal.getTimestamp() - exceptionSignal.getTimestamp() < RECOVER_INTERVAL) {     // update exception
                mExceptionSignalRecodes.insert(std::map<int, Signal>::value_type(signal.getSignal(), exceptionSignal));
                printSignal("updateException updated", signal);
                return true;
            } else {
                mExceptionSignalRecodes.erase(signal.getSignal());                                         // erase exception
            }
        }
    }
    printSignal("updateException not updated", signal);
    return false;
}

void Control::warning(Signal signal) {
    printSignal("warning", signal);
    mExceptionSignalRecodes.insert(std::map<int, Signal>::value_type(signal.getSignal(), signal));
}






