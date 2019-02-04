#ifndef EMONMETER_RADIO_H
#define EMONMETER_RADIO_H

#define RF69_COMPAT 1                                                 // Set to 1 if using RFM69CW or 0 is using RFM12B
#include <JeeLib.h>                                                   // https://github.com/jcw/jeelib

class Radio
{
public:
    void init(byte nodeId);
    void send(const void *payload, uint8_t len);

private:
    // Frequency of RF12B module can be RF12_433MHZ, RF12_868MHZ or RF12_915MHZ. You should use the one matching the module you have.
    byte RF_freq = RF12_433MHZ;
    int networkGroup = 210;
};


#endif //EMONMETER_RADIO_H
