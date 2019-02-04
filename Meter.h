#ifndef EMONMETER_METER_H
#define EMONMETER_METER_H

#include <arduino.h>

class Meter
{
public:
    explicit Meter(uint8_t index) : _index(index), _count(&counters[index])
    {}

    uint8_t index();
    virtual void reset();
    virtual boolean update(bool pinState, unsigned long tstamp)= 0;

    static unsigned long counters[];

protected:
 
    void inc();

private:
    unsigned long *_count;
    uint8_t _index;
};


#endif //EMONMETER_METER_H
