#include "Bewaesserungsstation.h"
#include "BewaesserungsstationCommands.h"

class LoRaClass;

uint16_t counter = 0;

void setup()
{
	init_clock(SYSCLK,PLL,true,CLOCK_CALIBRATION);

	PORTA_DIRSET = 0xf0; // 4x Eingang, dann 4x LEDs
	PORTB_DIRSET = 0x00;; // nichts angeschlossen
	PORTC_DIRSET = 0b00001011; // 4x LED, dann 4x Ausgang
	PORTD_DIRSET = 0b10111000; // nur RS232 an Pin6/7
	PORTE_DIRSET = 0x00; // nichts angeschlossen

	PORTA_OUTSET = 0xf0;

  uint8_t i,led;
	led = 0x10;
	for(i=0;i<=3;i++)
	{
		PORTA_OUT = ~led | 0x0f;
		_delay_ms(100);
		led = led<<1;
	}
	PORTA_OUT = 0xFF;
	init_mytimer();

	PMIC_CTRL = PMIC_LOLVLEX_bm | PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm;
	sei();
	debug.open(Serial::BAUD_57600,F_CPU);

  debug.sendInfo("Bewaesserung sagt Hallo","BR");

  if (!LoRa.begin(868E6))
  {
    while(1)
    {
      LED_ROT_TOGGLE;
      _delay_ms(100);
    }
  }

  loraCmulti.clearChecksum();
  LoRa.onReceive(onReceive);
  LoRa_rxMode();
  initTemperatureMessung();
}

int main()
{
  float result,meanResult=0;
  char *toSend;
  counter = 0;
  setup();
  capaMeasure capa(&PORTB,3,2);

  while(1)
  {


    if( NEXTTempMeasure==true )
    {
      LED_ROT_ON;
      NEXTTempMeasure = false;
      startAdcMeasure();
    }
    if( NEXTCapaMeasure==true )
    {
      LED_GRUEN_ON;
      NEXTCapaMeasure = false;
      result = capa.makeMeasure();
      LED_GRUEN_OFF;
      meanResult += result;
      counter++;
    }
    if( NEXTTempSend==true )
    {
      LED_GELB_ON;
      NEXTTempSend = false;
      loraCmulti.clearChecksum();
      loraCmulti.sendStandardDouble("BR",'T','A','i',calcTemperatur());
      toSend = &(loraCmulti.get()[1]);
      toSend[strlen(toSend)-1]=0;
      LoRa_sendMessage(toSend);
      LED_GELB_OFF;
    }

    if( NEXTCapaSend==true )
    {
      NEXTCapaSend = false;
        LED_BLAU_ON;
        loraCmulti.clearChecksum();
        loraCmulti.sendStandardDouble("BR",'F','A','i',(double)meanResult/counter);
        toSend = &(loraCmulti.get()[1]);
        toSend[strlen(toSend)-1]=0;
        LoRa_sendMessage(toSend);
        counter = 0;
        meanResult = 0;
        LED_BLAU_OFF;
    }

    if( rxIsReady==true )
    {
      LED_GELB_ON;
      rxIsReady=false;
      LED_BLAU_ON;
      processLoraInfo();
      LED_GELB_OFF;
    }
  }
}

void processLoraInfo()
{
  debug.sendInfo(rxMessage,"BR");
}

void LoRa_rxMode(){
  //LoRa.enableInvertIQ();                // active invert I and Q signals // war auskommentiert
  LoRa.receive();                       // set receive mode
}

void LoRa_txMode(){
  LoRa.idle();                          // set standby mode
  LoRa.disableInvertIQ();               // normal mode
}

void LoRa_sendMessage(char *message) {
  txIsReady = false;
  //LoRa_txMode();                        // set tx mode
  LoRa.beginPacket();                   // start packet
  LoRa.write((uint8_t*)message,strlen(message));                  // add payload
  LoRa.endPacket(false);                 // finish packet and send it !!!!!!!!!!!!! war true
}

void onReceive(int packetSize)
{
  uint8_t cointer=0;
  while (LoRa.available()) {
    rxMessage[cointer] = (char)LoRa.read();
    cointer++;
    if (cointer>=LORAMESSAGELENGTH-1)
      cointer--;
  }
  rxMessage[cointer]=0;
  rxRssi = LoRa.packetRssi();
  rxIsReady=true;
}

void onTxDone() {
  txIsReady = true;
}
