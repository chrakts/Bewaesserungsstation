#ifndef HX711ADAPTER_H_INCLUDED
#define HX711ADAPTER_H_INCLUDED

#define LORAMESSAGELENGTH 30

#include <avr/io.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/sleep.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "myConstants.h"

#include "uartHardware.h"
#include "Serial.h"
#include "timer.h"
#include "External.h"
#include "../Secrets/secrets.h"
#include "Communication.h"
#include "ComReceiver.h"
#include "cmultiStandardCommands.h"
#include "BewaesserungsstationCommands.h"
#include "../xmegaClocks/xmegaClocks.h"
#include "LoRa.h"
#include "Cmulti2Buffer.h"
#include "capaMeasure.h"
#include "adcMessung.h"


void setup();
void processLoraInfo();
void onTxDone();
void onReceive(int packetSize);
void LoRa_sendMessage(char *message);
void LoRa_txMode();
void LoRa_rxMode();
void evaluate(void);
void gotInfoFromLora();

#endif // HX711ADAPTER_H_INCLUDED
