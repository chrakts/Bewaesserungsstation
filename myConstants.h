#ifndef MYCONSTANTS_H_INCLUDED
#define MYCONSTANTS_H_INCLUDED

//enum{QUARZ,CLK2M,CLK32M};

#define SYSCLK CLK32M

#define PLL 0

#define LORACMULTIBUFFERR_LENGTH 25

#define LED_ROT_ON		PORTA_OUTCLR = PIN4_bm
#define LED_ROT_OFF		PORTA_OUTSET = PIN4_bm
#define LED_ROT_TOGGLE	PORTA_OUTTGL = PIN4_bm
#define LED_GELB_ON		PORTA_OUTCLR = PIN5_bm
#define LED_GELB_OFF		PORTA_OUTSET = PIN5_bm
#define LED_GELB_TOGGLE	PORTA_OUTTGL = PIN5_bm
#define LED_GRUEN_ON		PORTA_OUTCLR = PIN6_bm
#define LED_GRUEN_OFF		PORTA_OUTSET = PIN6_bm
#define LED_GRUEN_TOGGLE	PORTA_OUTTGL = PIN6_bm
#define LED_BLAU_ON		PORTA_OUTCLR = PIN7_bm
#define LED_BLAU_OFF		PORTA_OUTSET = PIN7_bm
#define LED_BLAU_TOGGLE	PORTA_OUTTGL = PIN7_bm


#endif // MYCONSTANTS_H_INCLUDED
