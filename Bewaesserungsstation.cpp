#include "Bewaesserungsstation.h"
#include "BewaesserungsstationCommands.h"



class LoRaClass;

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
  int16_t result;
  uint8_t i,k;
  setup();

  k=0;
  for(i=0;i<NUM_SLAVES;i++)
  {
    result = readFromSensor(FIRST_SLAVE_ADDRESS+i, adrId, lenId);
    if(result!= 0x7fff)
    {
      debug.sendAnswer("found","BR",'I',SLAVE_ADDRESS+i,'i',true);
      slaves[k] = SLAVE_ADDRESS+i;
      k++;
    }
    else
      debug.sendAnswer("not found","BR",'I',SLAVE_ADDRESS+i,'i',false);

  }

  // ID auslesen
  result = readFromSensor(SLAVE_ADDRESS, adrId, lenId);
  if(result!= 0x7fff)
    debug.sendStandardInt("BR",'I',SLAVE_ADDRESS,'i',result);

  while(1)
  {
    if( NEXTCapaSend==true )
    {
      NEXTCapaSend = false;
      result = readFromSensor(SLAVE_ADDRESS, adrHumidity, lenHumidity);
      if (result!= 0x7fff)
        debug.sendStandardInt("BR",'H',SLAVE_ADDRESS,'i',result);
      result = readFromSensor(SLAVE_ADDRESS, adrTemperature, lenTemperature);
      if (result!= 0x7fff)
        debug.sendStandardDouble("BR",'T',SLAVE_ADDRESS,'i',((double)result)/100.0);
    }

  }
}

int16_t readFromSensor(uint8_t slave, uint8_t address, uint8_t length)
{
  uint8_t data;
  bool test;
  int16_t result=0;
  data = address;
  test = TWI_MasterWriteRead(&twiC_Master,slave,&data,1,length);
  while(!TWI_MasterReady(&twiC_Master))
    ;
  if(twiC_Master.result==TWIM_RESULT_OK)
  {
    if (length>1)
      result = ((int16_t)twiC_Master.readData[1])<<8;
    result |= twiC_Master.readData[0];
    return(result);
  }
  else
    return(0x7fff);
}
