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

#include "pt.h"

#define MSG_SIZE 50

#define TIMER_PERIOD_MS 10 // period for main timer A

#define TIMER_CAPTURE_PERIOD_MS 1000    // period for temperature capture 
#define TIMER_RADIO_PERIOD_MS   1000    // period for radio rx/tx checks

#define NUM_TIMERS 2

static uint16_t timer[NUM_TIMERS];

#define TIMER_TEMP timer[0]	// Data gathering
#define TIMER_RADIO timer[1] // Rx Tx and state transitions

#define NUM_PT 2
static struct pt pt[NUM_PT];

#define USER_RFCONFIG config0
const RF_SETTINGS config0 = {
    0x12,   // FSCTRL1   Frequency synthesizer control.
    0x00,   // FSCTRL0   Frequency synthesizer control.
    0x5D,   // FREQ2     Frequency control word, high byte.
    0x93,   // FREQ1     Frequency control word, middle byte.
    0xB1,   // FREQ0     Frequency control word, low byte.
    0x2D,   // MDMCFG4   Modem configuration.
    0x3B,   // MDMCFG3   Modem configuration.
    0xF3,   // MDMCFG2   Modem configuration.
    0x22,   // MDMCFG1   Modem configuration.
    0xF8,   // MDMCFG0   Modem configuration.
    0x03,   // CHANNR    Channel number.
    0x01,   // DEVIATN   Modem deviation setting (when FSK modulation is enabled).
    0xB6,   // FREND1    Front end RX configuration.
    0x10,   // FREND0    Front end TX configuration.
    0x18,   // MCSM0     Main Radio Control State Machine configuration.
    0x1D,   // FOCCFG    Frequency Offset Compensation Configuration.
    0x1C,   // BSCFG     Bit synchronization Configuration.
    0xC7,   // AGCCTRL2  AGC control.
    0x00,   // AGCCTRL1  AGC control.
    0xB0,   // AGCCTRL0  AGC control.
    0xEA,   // FSCAL3    Frequency synthesizer calibration.
    0x0A,   // FSCAL2    Frequency synthesizer calibration.
    0x00,   // FSCAL1    Frequency synthesizer calibration.
    0x11,   // FSCAL0    Frequency synthesizer calibration.
    0x59,   // FSTEST    Frequency synthesizer calibration.
    0x88,   // TEST2     Various test settings.
    0x31,   // TEST1     Various test settings.
    0x0B,   // TEST0     Various test settings.
    0x07,   // FIFOTHR   RXFIFO and TXFIFO thresholds.
    0x29,   // IOCFG2    GDO2 output pin configuration.
    0x06,   // IOCFG0D   GDO0 output pin configuration. Refer to SmartRF® Studio User Manual for detailed pseudo register explanation.
    0x04,   // PKTCTRL1  Packet automation control.
    0x05,   // PKTCTRL0  Packet automation control.
    0x00,   // ADDR      Device address.
    0xFF    // PKTLEN    Packet length.
};

/*  Timer   */
int timer_reached(uint16_t timer, uint16_t count) {
    return (timer >= count);
}

void timer_tick_cb() {
    int i;
    for(i = 0; i < NUM_TIMERS; i++)
    {
        if(timer[i] != UINT_MAX) {
            timer[i]++;
        }
    }
}

// Periodically capture temperature
static PT_THREAD(thread_periodic_capture(struct pt *pt))
{
    PT_BEGIN(pt);

    while(1)
    {
        TIMER_TEMP_PRINT = 0;
        PT_WAIT_UNTIL(pt,timer_reached( TIMER_TEMP, TIMER_CAPTURE_PERIOD_MS/TIMER_PERIOD_MS));
        //TODO
    }
    PT_END(pt);
}

// Periodically check and empties rx buffer/send msg and switch states accordingly to received msg
static PT_THREAD(thread_periodic_radio(struct pt *pt))
{
    PT_BEGIN(pt);

    while(1)
    {
        TIMER_TEMP_PRINT = 0;
        PT_WAIT_UNTIL(pt,timer_reached( TIMER_RADIO, TIMER_RADIO_PERIOD_MS/TIMER_PERIOD_MS));
        //TODO
    }
    PT_END(pt);
}

int main ()
{
    watchdog_stop();

    set_mcu_speed_dco_mclk_16MHz_smclk_8MHz(); // set global clock

    /* Initialisation begin */
    leds_init();	// leds :')
    spi_init();	//
    cc2500_init();	// radio init
    #if defined(USER_RFCONFIG)
    cc2500_configure(& USER_RFCONFIG );
    #endif

    timerA_init(); // global timer
    timerA_register_cb(&timer_tick_cb); // protothread timer increment callback
    timerA_start_milliseconds(TIMER_PERIOD_MS);

    uart_init(UART_9600_SMCLK_8MHZ); // serial link

    printf("adc test application: temperature\n\n");

    adc10_start(); // temperature sensor

    __enable_interrupt();
        
    /* Initialisation end */

    while(1)
    {
        thread_periodic_capture(&pt[0]);
        thread_periodic_radio(&pt[1]);
        //do something
    }

    return 0;
}
