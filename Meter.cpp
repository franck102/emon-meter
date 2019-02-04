//
// Created by Franck on 12/20/2018.
//

#include "PulseMeter.h"
#include "Meter.h"

void Meter::reset()
{
    * _count = 0;
}

uint8_t Meter::index()
{
    return _index;
}

void Meter::inc()
{
    *_count = *_count + 1;
}


