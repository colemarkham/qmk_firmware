/*! \file ********************************************************************
*
* Atmel Corporation
*
* - File              : main.c
* - Compiler          : GCC 4.9.2
*
*
* - Supported devices : ATmega328PB
*
* - AppNote           : AVR136 - Low-Jitter Multi-Channel Software PWM
*
* - Description       : ATmega328PB software PWM demo. This program demonstrates the
*                       generation of low-jitter PWM signals on multiple I/O ports
*                       for LED driving, meter driving, voltage generation etc.
*
*****************************************************************************/
/*
 *
 * Device Info
 * The included source code is written for ATmega328PB, using the 328PB Xplained mini.
 * - Default 16 Mhz @ 5V -important for BAUD.
 *
 * Target Setup
 * - Use AVR Studio Tool DataVisualizer, External Connection -> Serial Port -> COM16.
 * - Set BAUD rate to 38400, and 1 stop bit.
 * - Select connect
 *
 * Send commands using the four-character format: \#nHH
 * where:
 * - # is a sync character
 * - n = 0-9 for required channel number
 * - HH = hex value corresponding to 0-255 for PWM high period
 *
 * Channels are mapped to specific port pins setup in Atmel Start.
 * \section PWMinfo PWM frequency and crystal selection
 *
 * The 8 bit counter will have a max count of 256, and software counter 256,
 * resulting in a pwm resolution will be 65536.
 * The PWM base frequency is the crystal frequency divided by 65536 (256*256), e.g. for
 * a 16MHz Xplained mini crystal the PWM base frequency will be 256 Hz.
 * A lower clock freq (e.g. 3.6864MHz oscillator)  could be used as a clock source,
 * but the PWM base frequency would be reduced which may result in unacceptable ripple.
 * Jitter will be +/-1 clock cycle max, or +/-0.0015% of base frequency.
 *
 * This demonstration shows ten PWM channels, for GCC the ISR uses less than
 * 50% of processing time during the softcount=0 interrupt. The principles
 * shown should accommodate up to 24 channels on suitable AVR devices whilst
 * maintaining PWM accuracy, ISR optimization may improve this even further.
 *
 */

#include "atmel_start.h"
#include "main.h"
#include <ctype.h>
#include <avr/wdt.h>

//! global buffers
unsigned char          compare[CHMAX];
volatile unsigned char compbuff[CHMAX];

#if DEBUG_APP
volatile unsigned int debugTimer;
#endif

int main(void)
{
	system_init();
	module_init();
	USART0_Init(BAUD_38_4K_FOSC_EXT_5V_16M);
	while (1) {
#if DEBUG_APP
		DebugMonitor();
#else
		ManualControl();
#endif
	}
	return 0;
}

/*
 * Setting all pins individually allows the user to freely select pins regardless of port,
 * but it is not optimal for minimizing jitter.
 *
 * To lower the jitter, replace this function with code that sets the complete port(s)
 * at the same time.
 */
void PWM_allpins_set_level(const bool level)
{
	PWM_0_set_level(level);
	PWM_1_set_level(level);
	PWM_2_set_level(level);
	PWM_3_set_level(level);
	PWM_4_set_level(level);
	PWM_5_set_level(level);
	PWM_6_set_level(level);
	PWM_7_set_level(level);
	PWM_8_set_level(level);
	PWM_9_set_level(level);
}

/*! \brief Example of PWM control via the serial port. Waits for a synchronization character and acts upon it.
 */
void ManualControl(void)
{
	unsigned char rxdata, channel, temp, error;

	error = 0; // clear error flag
	while (USART0_Receive() != '#')
		;                              // wait for sync character
	USART0_Transmit('#');              // echo sync character
	channel = USART0_Receive() - 0x30; // receive channel number
	if (channel >= CHMAX)
		error = 1;                   // error if invalid channel
	USART0_Transmit(channel + 0x30); // echo received character

	temp = GetNextChar();  // fetch upper nibble
	USART0_Transmit(temp); // echo received character
	if (isxdigit(temp))    // check for a hex character
	{
		if (temp > '9')
			temp -= 7; // subtract offset for A-F
		temp -= 0x30;  // subtract ASCII offset
	} else
		error = 1;         // error if not hex
	rxdata    = temp << 4; // store received upper nibble

	temp = GetNextChar();  // fetch lower nibble
	USART0_Transmit(temp); // echo received character
	if (isxdigit(temp))    // check for a hex character
	{
		if (temp > '9')
			temp -= 7; // subtract offset for A-F
		temp -= 0x30;  // subtract ASCII offset
	} else
		error = 1;  // error if not hex
	rxdata += temp; // add lower nibble to upper nibble

	if (!error) // if data is good
	{
		compbuff[channel] = rxdata; // update compare buffer

		USART0_Transmit(':'); // send OK message
		USART0_Transmit('O');
		USART0_Transmit('K');
		USART0_Transmit('\r');
		USART0_Transmit('\n');
	} else // if data is not good
	{
		USART0_Transmit(':'); // send ERRor message
		USART0_Transmit('E');
		USART0_Transmit('R');
		USART0_Transmit('R');
		USART0_Transmit('\r');
		USART0_Transmit('\n');
	}
}

/*! \brief  Display debug timer value on attached terminal
 */
#if DEBUG_APP
void DebugMonitor(void)
{
	signed char  i;
	unsigned int temp;

	temp = debugTimer; // fetch latest timer value
	USART0_Transmit('\r');
	USART0_Transmit('0');
	USART0_Transmit('x');
	// transmit 16 bit timer value as four hex characters
	for (i = 3; i >= 0; i--)
		USART0_Transmit(HexToASCII(0x0F & (temp >> (4 * i))));

	DEBUG_LED_toggle_level(); // TOGGL LED pin when in DEBUG mode
}
#endif
/*! \brief Init function. This function initializes the hardware
 */
void module_init(void)
{
	unsigned char i, pwm;

	CLKPR = (1 << CLKPCE); // enable clock prescaler update
	CLKPR = 0;             // set clock to maximum (= crystal)

	wdt_reset();                        // reset watchdog timer
	MCUSR &= ~(1 << WDRF);              // clear the watchdog reset flag
	WDTCSR |= (1 << WDCE) | (1 << WDE); // start timed sequence
	WDTCSR = 0x00;                      // disable watchdog timer

	PRR0 &= ~(1 << PRUSART0); // enable USART 0
	PRR0 &= ~(1 << PRTIM0);   // enable Timer/Counter 0

#if DEBUG_APP
	DEBUG_LED_set_dir(PORT_DIR_OUT); // make debug pin output (header file macro)
	pwm = 0;                         // worst-case default PWM level
#else
	pwm = PWMDEFAULT;
#endif

	for (i = 0; i < CHMAX; i++) // initialise all channels
	{
		compare[i]  = pwm; // set default PWM values
		compbuff[i] = pwm; // set default PWM values
	}

#if DEBUG_APP
	compare[0]  = 0x01; // make one channel active
	compbuff[0] = 0x01;
#endif

	TIFR0  = (1 << TOV0);  // clear interrupt flag
	TIMSK0 = (1 << TOIE0); // enable overflow interrupt
	TCCR0B = (1 << CS00);  // start timer, no prescale

	sei(); // enable interrupts
}

/*! \brief Interrupt Service Routine
 */
ISR(TIMER0_OVF_vect)
{
	// static unsigned char pinlevelB=PORTB_MASK, pinlevelD=PORTD_MASK;
	static unsigned char softcount = 0xFF;

#if DEBUG_APP
	DEBUG_LED_set_level(true); // set debug pin
	TCNT1  = 0;                // clear timer
	TCCR1B = (1 << CS10);      // start timer
#endif

	if (++softcount == 0) {       // increment modulo 256 counter and update
		                          // the compare values only when counter = 0.
		compare[0] = compbuff[0]; // verbose code for speed
		compare[1] = compbuff[1];
		compare[2] = compbuff[2];
		compare[3] = compbuff[3];
		compare[4] = compbuff[4];
		compare[5] = compbuff[5];
		compare[6] = compbuff[6];
		compare[7] = compbuff[7];
		compare[8] = compbuff[8];
		compare[9] = compbuff[9]; // last element should equal CHMAX - 1

		PWM_allpins_set_level(true);
	}
	// clear port pin on compare match (executed on next interrupt)
	if (compare[0] == softcount)
		PWM_0_set_level(false);
	if (compare[1] == softcount)
		PWM_1_set_level(false);
	if (compare[2] == softcount)
		PWM_2_set_level(false);
	if (compare[3] == softcount)
		PWM_3_set_level(false);
	if (compare[4] == softcount)
		PWM_4_set_level(false);

	if (compare[5] == softcount)
		PWM_5_set_level(false);
	if (compare[6] == softcount)
		PWM_6_set_level(false);
	if (compare[7] == softcount)
		PWM_7_set_level(false);
	if (compare[8] == softcount)
		PWM_8_set_level(false);
	if (compare[9] == softcount)
		PWM_9_set_level(false);

#if DEBUG_APP
	DEBUG_LED_set_level(false); // clear debug pin
	TCCR1B = 0;                 // stop timer
	if (!softcount)
		debugTimer = TCNT1; // store value for softcount=0 ISR
#endif
}

/*! \brief  USART0_Init - initialise USART (derived from AVR 306 Applications Note)
 */
void USART0_Init(unsigned int baudrate)
{
	// Set the baud rate
	UBRR0H = (unsigned char)(baudrate >> 8);
	UBRR0L = (unsigned char)baudrate;

	// Enable UART receiver and transmitter
	UCSR0B = ((1 << RXEN0) | (1 << TXEN0));

	// Set frame format: 8 data, 1 stop
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

/*! \brief  USART0_Receive - wait for incoming data (blocking function, from AVR 306)
 */
unsigned char USART0_Receive(void)
{
	while (!(UCSR0A & (1 << RXC0)))
		;        // Wait for incoming data
	return UDR0; // Return the data
}

/*! \brief  USART0_Transmit - send data (blocking function, from AVR 306)
 */
void USART0_Transmit(unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0)))
		;        // Wait for empty transmit buffer
	UDR0 = data; // Start transmittion
}

/*! \brief  HexToASCII - convert single hex digit to ASCII equivalent
 */
unsigned char HexToASCII(unsigned char ch)
{
	ch += 0x30; // add offset to ASCII '0'
	if (ch > '9')
		ch += 7; // if alphabetic add offset to ASCII 'A'
	return ch;
}

/*! \brief  GetNextChar - receive and normalise next character from USART
 */
unsigned char GetNextChar(void)
{
	char tmp;

	tmp = USART0_Receive(); // get next character
	tmp = toupper(tmp);     // force to upper case
	return (tmp);
}
