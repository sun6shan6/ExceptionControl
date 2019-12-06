//
// Created by sgs on 19-11-28.
//

#include "Signal.h"

int Signal::getSignal() const {
    return signal;
}

void Signal::setSignal(int signal) {
    Signal::signal = signal;
}

long Signal::getTimestamp() const {
    return timestamp;
}

void Signal::setTimestamp(long timestamp) {
    Signal::timestamp = timestamp;
}

Signal::Signal(int signal, long timestamp) : signal(signal), timestamp(timestamp) {}

Signal::~Signal() {

}
