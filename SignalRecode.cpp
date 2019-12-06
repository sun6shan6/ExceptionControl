//
// Created by sgs on 19-11-28.
//

#include "SignalRecode.h"

const Signal &SignalRecode::getSignal() const {
    return signal;
}

void SignalRecode::setSignal(const Signal &signal) {
    SignalRecode::signal = signal;
}

int SignalRecode::getCount() const {
    return count;
}

void SignalRecode::setCount(int count) {
    SignalRecode::count = count;
}

SignalRecode::SignalRecode(const Signal &signal, int count) : signal(signal), count(count) {}
