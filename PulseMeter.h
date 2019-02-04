#ifndef POWERSENSOR_PULSE_H
#define POWERSENSOR_PULSE_H

#include <arduino.h>
#include "Meter.h"

#define bit_test(reg, bit) (((reg) & (1UL << (bit))) == (1UL << (bit)))

// 10ms min between two pulses
#define DEBOUNCE_ms 10L

class PulseMeter
        : public Meter
{
public:
    explicit PulseMeter(uint8_t pin) : Meter(pin), _lastFall(0L), _lastState(false)
    {
    }
    
    void reset() override;
    boolean update(bool pinState, unsigned long tstamp) override;
private:
    // Time of the last increment
    unsigned long _lastFall;
    bool _lastState;
};

#endif //POWERSENSOR_PULSE_H
