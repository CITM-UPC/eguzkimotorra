#ifndef __TIMER_H__
#define __TIMER_H__

#include "core/definitions.h"

class Timer {
public:
    Timer(bool to_start = true);

    void Start();
    void Stop();

    uint Read() const;
    float ReadSeconds() const;

private:
    bool running_;
    uint ticks_started_;
    uint ticks_stopped_;
};

#endif
