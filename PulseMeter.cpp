#include "PulseMeter.h"

boolean PulseMeter::update(bool pinState, unsigned long tstamp)
{
    bool updated = false;

    if (_lastState && tstamp - _lastFall > DEBOUNCE_ms && !pinState) {
        inc();
        _lastFall = tstamp;
        updated = true;
#ifdef DEBUG
        Serial.print("Updated: "); Serial.println(index());
#endif
    }

    _lastState = pinState;
    return updated;
}

void PulseMeter::reset()
{
    Meter::reset();
    _lastFall = millis();
}
