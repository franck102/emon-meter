#ifndef EMONMETER_TIMEMETER_H
#define EMONMETER_TIMEMETER_H

#include "Meter.h"

// A TimeMeter continuously generates pulses at a configured rate as long as its input pin is HIGH.
// It can typically be used to track the working time of an appliance through a relay.
class TimeMeter : public Meter
{

public:
    // Generates pulseCount pulses for every periodSeconds period
    TimeMeter(uint8_t index, uint16_t pulseCount, uint16_t periodSeconds) :
            Meter(index), _millisPerPulse((unsigned long)(1000L * periodSeconds) / pulseCount),
            _working(false), _workTime(0L)
    {
    }

    // Generates pulseCount pulses for each period in milliseconds
    TimeMeter(uint8_t index, unsigned long millisPerPulse) :
            Meter(index), _millisPerPulse(millisPerPulse),
            _working(false), _workTime(0L)
    {
    }

    boolean update(bool pinState, unsigned long tstamp) override;

private:
    unsigned long _millisPerPulse;
    bool _working;
    unsigned long _workTime;
};


#endif //EMONMETER_TIMEMETER_H
