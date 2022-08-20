#include "Bewaesserungsstation.h"
#include "BewaesserungsstationCommands.h"



class LoRaClass;

uint16_t counter = 0;
uint16_t tempCounter = 0;

void setup()
{
	init_clock(SYSCLK,PLL,true,CLOCK_CALIBRATION);

	PORTA_DIRSET = 0b00011100; // 3x LEDs
	PORTB_DIRSET = 0x00;; // nichts angeschlossen
	PORTC_DIRSET = 0b00000010; // I2C
	PORTD_DIRSET = 0b00000000; // nichts angeschlossen
	PORTE_DIRSET = 0b00001011; // nichts angeschlossen

	PORTA_OUTSET = 0b00011100;

  uint8_t i,led;
	led = 0b00000100;
	for(i=0;i<=3;i++)
	{
		PORTA_OUT = ~led;
		_delay_ms(100);
		led = led<<1;
	}
	PORTA_OUTSET = 0b00011100;
	init_mytimer();

  TWI_MasterInit(&twiC_Master, &TWIC, TWI_MASTER_INTLVL_LO_gc, TWI_BAUDSETTING);

	PMIC_CTRL = PMIC_LOLVLEX_bm | PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm;
	sei();
	debug.open(Serial::BAUD_57600,F_CPU);


  debug.sendInfo("Bewaesserung sagt Hallo","BR");

}

int main()
{
  bool test;
  float meanResult=0;
  counter = 0;
  float meanTempResult=0;
  tempCounter = 0;
  uint8_t data;
  setup();
  // ID auslesen
  data = adrId;
  test = TWI_MasterWriteRead(&twiC_Master,SLAVE_ADDRESS,&data,1,lenId);
  while(!TWI_MasterReady(&twiC_Master))
      ;
  if(test==true)
  {
    debug.sendStandardInt("BR",'I',SLAVE_ADDRESS,'i',twiC_Master.readData[0]);
  }

  while(1)
  {
    if( NEXTCapaMeasure==true )
    {
      // Feuchte auslesen
      data = adrHumidity;
      test = TWI_MasterWriteRead(&twiC_Master,SLAVE_ADDRESS,&data,1,lenHumidity);
      while(!TWI_MasterReady(&twiC_Master))
          ;
      if(test==true)
      {
        meanResult += (float)(twiC_Master.readData[0]+twiC_Master.readData[1]*256);
        counter++;
      }

      // Temperatur auslesen
      data = adrTemperature;
      test = TWI_MasterWriteRead(&twiC_Master,SLAVE_ADDRESS,&data,1,lenTemperature);
      while(!TWI_MasterReady(&twiC_Master))
          ;
      if(test==true)
      {
        meanTempResult += (float)(twiC_Master.readData[0]+twiC_Master.readData[1]*256);
        tempCounter++;
      }

      NEXTCapaMeasure = false;
    }
    if( NEXTCapaSend==true )
    {
      NEXTCapaSend = false;
        LED_BLAU_ON;
        if( counter>0 )
        {
          debug.sendStandardDouble("BR",'H',SLAVE_ADDRESS,'i',(double)meanResult/counter);
          counter = 0;
          meanResult = 0;
        }
        if( tempCounter>0 )
        {
          debug.sendStandardDouble("BR",'T',SLAVE_ADDRESS,'i',(double)(meanTempResult/tempCounter)/100.0);
          tempCounter = 0;
          meanTempResult = 0;
        }
        LED_BLAU_OFF;
    }

  }
}

