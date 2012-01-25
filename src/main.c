#include <msp430x22x4.h>

#if defined(__GNUC__) && defined(__MSP430__)
/* This is the MSPGCC compiler */
#include <msp430.h>
#include <iomacros.h>
#include <legacymsp430.h>
#elif defined(__IAR_SYSTEMS_ICC__)
/* This is the IAR compiler */
//#include <io430.h>
#endif

#include <stdio.h>
#include <string.h>

#include "math.h"
#include "leds.h"
#include "clock.h"
#include "timer.h"
#include "uart.h"
#include "watchdog.h"
#include "spi.h"
#include "cc2500.h"



int main ()
{
	return 0;
}
