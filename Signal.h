//
// Created by sgs on 19-11-28.
//

#ifndef EXCEPTIONCONTROL_SIGNAL_H
#define EXCEPTIONCONTROL_SIGNAL_H


class Signal {

public:
    Signal(int signal, long timestamp);

    virtual ~Signal();

private:
    int signal;
    long timestamp;

public:
    int getSignal() const;

    void setSignal(int signal);

    long getTimestamp() const;

    void setTimestamp(long timestamp);

};


#endif //EXCEPTIONCONTROL_SIGNAL_H
