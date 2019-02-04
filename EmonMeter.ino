#include <arduino.h>
#include "PulseMeter.h"
#include "Radio.h"
#include "TimeMeter.h"
#include <avr/wdt.h>

// How long to wait, at least, between two radio updates, in millis
#define SEND_INTERVAL 60000L

// The emonHub node ID
#define NODE_ID 18

// To add a new meter:
// - define a new TimeMeter or PulseMeter object
// - insert the object in the meters array below
// The first argument to the meter constructor is the pin offset and determines to what pin
// the corresponding pulse in put should be connected:
// pin numder = PIN_OFFSET + <constructor argument>
// The pulse counts are sent to emonPi in the order they appear in the meters array.

// Fuel at 2.27125 L/h, 1 pulse / ml, digital pin 4
TimeMeter fuelMeter = TimeMeter(0, 2271, 3600);
// Three phase pulse meter (induction), digital pin 5
PulseMeter plaqueMeter = PulseMeter(1);
// Water meter, 1L / pulse, digital pin 6
PulseMeter waterMeter = PulseMeter(2);

#define NUM_METERS 6
// Meters, pin 4 to 9; use nullptr for unused slots
Meter *meters[NUM_METERS] = {
        &fuelMeter,
        &plaqueMeter,
        &waterMeter,
        nullptr,
        nullptr,
        nullptr
};

#define PIN_LED 3

// =========================

// ==== Initialize meters
unsigned long Meter::counters[8] = {0L, 0L, 0L, 0L, 0L, 0L};

unsigned long _ledOn = 0L;
unsigned long lastSend = 0UL;

Radio radio;

// First meter pin is D4
#define PIN_OFFSET 4

#ifdef DEBUG
uint32_t readings = 0ul;
#endif

uint8_t payloadLen;
bool pinState(int index, int ddrd, int ddrb);
void blink(unsigned long tstamp);
void updateLed(unsigned long tstamp);
void debug(const char msg[]);

void setup()
{
    wdt_enable(WDTO_500MS);
#ifdef DEBUG
    Serial.begin(115200);
#endif
    pinMode(PIN_LED, OUTPUT);
    payloadLen = 0;
    for (uint8_t i = 0; i < NUM_METERS; ++i) {
        if (meters[i] != nullptr) {
            pinMode(i + PIN_OFFSET, INPUT);
            payloadLen += sizeof(unsigned long);
        }
    }

    debug("Initializing radio...");
    radio.init(NODE_ID);
}

void debug(const char msg[])
{
#ifdef DEBUG
    Serial.println(msg);
#endif
}

void loop()
{
    wdt_reset();
    int reg_pind = PIND;
    int reg_pinb = PINB;
    unsigned long tstamp = millis();
    for (auto &meter : meters) {
        if (meter != nullptr) {
            if (meter->update(pinState(meter->index(), reg_pind, reg_pinb), tstamp)) {
                blink(tstamp);
            }
        }
    }

#ifdef DEBUG
    readings++;
#endif
    wdt_reset();
    // Send at most one update at a time
    if (tstamp - lastSend > SEND_INTERVAL) {
        radio.send(Meter::counters, payloadLen);
        wdt_reset();
        lastSend = tstamp;
    }
    updateLed(tstamp);
}

bool pinState(int index, int ddrd, int ddrb)
{
    int pin = index + PIN_OFFSET;
    bool pinState = pin < 8 ?
                    bit_test(ddrd, pin) :
                    bit_test(ddrb, pin - 8);
    return pinState;
}

void blink(unsigned long tstamp)
{
    if (_ledOn == 0L) {
        digitalWrite(PIN_LED, HIGH);
        _ledOn = tstamp;
    }
}

void updateLed(unsigned long tstamp)
{
    if (_ledOn > 0L && tstamp - _ledOn > 100L) {
        _ledOn = 0L;
        digitalWrite(PIN_LED, LOW);
    }
}
