#define EXTERNALS_H_

#include "Bewaesserungsstation.h"
#include "../Secrets/secrets.h"

const char *Node = "W1";

volatile float fExternalTemperature = 5.0;

char SecurityLevel = 0;


SPI mySPI(0);
LoRaClass LoRa(&mySPI);

Communication debug(0,Node,5,true);


volatile uint8_t txIsReady = false;
volatile uint8_t rxIsReady = false;

volatile int8_t rxRssi = 0;
char rxMessage[LORAMESSAGELENGTH];

uint8_t key[16] = {AES256_KEY};

bool NEXTCapaMeasure = true;
bool NEXTCapaSend = false;
bool STOPRelais = false;
bool NEXTTempMeasure = true;
bool NEXTTempSend = false;
bool validTemperature = false;

char LoraCmultiBuffer[LORACMULTIBUFFERR_LENGTH];
Cmulti2Buffer loraCmulti(LoraCmultiBuffer,LORACMULTIBUFFERR_LENGTH,Node);
