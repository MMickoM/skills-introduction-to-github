#include "si_toolchain.h"
#include <stdio.h>


void timer0_ISR (void) interrupt 1
{

	i++;

	TF1 = 0;

} 


