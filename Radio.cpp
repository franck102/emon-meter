#include "Radio.h"

void Radio::init(byte nodeId)
{
    rf12_initialize(nodeId, RF_freq, networkGroup);
#ifdef DEBUG
    Serial.print("Radio initialized, network: ");Serial.print(networkGroup);
    Serial.print(", nodeId: ");Serial.println(nodeId);
#endif
}

void Radio::send(const void *payload, uint8_t len)
{
  rf12_sendWait(0);
  rf12_sendNow(0u, payload, len);
}


