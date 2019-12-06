//
// Created by sgs on 19-11-28.
//

#ifndef EXCEPTIONCONTROL_SIGNALRECODE_H
#define EXCEPTIONCONTROL_SIGNALRECODE_H


#include "Signal.h"

class SignalRecode {

public:
    SignalRecode(const Signal &signal, int count);

private:
    Signal signal;
    int count;


public:
    const Signal &getSignal() const;

    void setSignal(const Signal &signal);

    int getCount() const;

    void setCount(int count);
};


#endif //EXCEPTIONCONTROL_SIGNALRECODE_H
