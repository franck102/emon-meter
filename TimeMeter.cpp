//
// Created by Franck on 12/20/2018.
//

#include "TimeMeter.h"

boolean TimeMeter::update(bool pinState, unsigned long tstamp)
{
    bool updated = false;

    if (pinState) {
        if (_working && tstamp - _workTime >= _millisPerPulse) {
            inc();
            _workTime = tstamp;
            updated = true;
        }
        _working = true;
    }
    else {
        _working = false;
    }
    return updated;
}
