//
// Created by sgs on 19-11-28.
//

#ifndef EXCEPTIONCONTROL_CONTROL_H
#define EXCEPTIONCONTROL_CONTROL_H

#define TAG Control
#include <vector>
#include "Signal.h"
#include "SignalRecode.h"
#include <map>
#include <mutex>
#include <thread>
#include "utils/LogUtils.h"

class Control {

public:

    static const int MAX_RECODE = 5;
    static const int RECOVER_INTERVAL = 1000 * 6;
    Control();

    bool watch(Signal signal);
    void looper();
    SignalRecode initRecode(Signal signal);
    void deleteOutDatedData(Signal signal);
    bool updateException(Signal signal);
    void warning(Signal signal);

    virtual ~Control();

private:
    std::vector<Signal>           mCacheSignal;
    std::mutex                    mCacheLock;
    std::map<int, SignalRecode>   mSignalRecodes;
    std::map<int, Signal>         mExceptionSignalRecodes;
    std::thread                   mLooper;



};


#endif //EXCEPTIONCONTROL_CONTROL_H
