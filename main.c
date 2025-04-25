#include <stdio.h>
#include <string.h>
#include "C8051F120_defs.h"
#include "si_toolchain.h"


void Oscillator_Init (void)
{

	char SFRPAGE_SAVE = SFRPAGE;
	SFRPAGE = CONFIG_PAGE;

	OSCICN = 0x83;                  // Dozvoljen interni oscilator, na maksimalnoj frekvenciji
	CLKSEL = 0x00;                  // Interni osc. kao sistemski klok


	SFRPAGE = SFRPAGE_SAVE;
}


void Disable_WDT(void)
{
	WDTCN = 0xde;
	WDTCN = 0xad;  
}

void Timer1_Init(void)
{
	char SFRPAGE_SAVE = SFRPAGE;
	SFRPAGE = TIMER01_PAGE;

	CKCON = 0x01;                 // Koristi sistemski klok / 4 (2450000 Hz / 4 = 6125000 Hz)
	TMOD |= 0x00;                 // Timer 1 radi u mod 0


	TCON |= 0x40;                 // Dozvola tajmera br.1

	TH1  = 0x40;                 // 0x132 za 500ms (306 takta)
	TL1  = 0x12;

	ET1   = 1;                    // Dozvola interapta od tajmera br.1

	SFRPAGE = SFRPAGE_SAVE;
}
/////////////////////////////////////////////////////////////////////////////////////////

unsigned int i=0, j;
unsigned char MyArray[100];
unsigned int t=1;
//bit p==0;

void main(void)
{
	
	Disable_WDT();
	Oscillator_Init();
	Timer1_Init();
	EA = 1;

	while(t)
	{
		MyArray[i] = i;
		i++;
		
		if (MyArray[i] == 100)
			i = 0;

		for (j=0; j<5; j++)
		{
			//i = i + 1;
			//j++;
		}

		j++;
	}

}



void timer1_ISR (void) interrupt 3
{

	i = i + 1;

	TH1  = 0x40;                 // 0x132 za 500ms (306 takta)
	TL1  = 0x12;

	TF1 = 0;

}