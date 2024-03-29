#ifndef EXTERNAL_H_INCLUDED
#define EXTERNAL_H_INCLUDED

#include "Serial.h"
#include "myConstants.h"
#include "Communication.h"
#include "CRC_Calc.h"
#include "SPI.h"
#include "LoRa.h"
#include "Cmulti2Buffer.h"
#include "ComReceiver.h"
#include "twi_master_driver.h"
#include "Bewaesserungsstation.h"

extern const char *Node;

extern volatile float fExternalTemperature;

extern char SecurityLevel;

extern CRC_Calc crcGlobal;

extern uint8_t outputPins[];
extern SPI mySPI;

extern Communication debug;

class LoRaClass;

extern LoRaClass LoRa;

extern volatile  uint8_t txIsReady;
extern volatile  uint8_t rxIsReady;

extern volatile int8_t rxRssi;
extern  char rxMessage[LORAMESSAGELENGTH];

extern uint8_t key[];

extern char LoraCmultiBuffer[];
extern Cmulti2Buffer loraCmulti;

extern bool NEXTCapaMeasure;
extern volatile bool NEXTCapaSend;
extern bool STOPRelais;
extern bool NEXTTempMeasure;
extern bool NEXTTempSend;
extern bool validTemperature;

extern TWI_MasterDriver_t twiE_Master;
extern TWI_MasterDriver_t twiC_Master;

extern uint8_t slaves[];
#endif // EXTERNAL_H_INCLUDED


