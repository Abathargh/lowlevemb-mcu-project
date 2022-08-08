/**
 * keyboard_ifc.c
 *
 * This module implements the keyboard interface logic.
 * The keyboard is a NxM matrix made of push buttons; this approach is 
 * a classical one that allows to use NxM key buttons or generic key 
 * inputs with only N+M pins.
 * In the case of this module, a whole octave is implemented as a 4x3 
 * matrix, of 4 output rows and 3 input columns
 *
 *      c0  c1  c2
 *   ---|---|---|-------
 *   |  |   |   |      |
 * r0---O---O---O------|
 *   |   |   |   |     |
 * r1----O---O---O-----|
 *   |    |   |   |    |
 * r2-----O---O---O----|
 *   |     |   |   |   |
 * r3------O---O---O---|
 *
 * These keys are sampled by iterating on each row, and checking on the 
 * columns which are initialized with a pull-up configuration. On each 
 * row iteration, the row is set to the low state, and the algorithm 
 * checks if any column is driven low  meaning that the key (i, j) is 
 * being pressed. These configuration can be used to check if more than 
 * one key is being pressed, and avoids errors thanks to the hardware 
 * configuration, where each key connection that goes back to the output 
 * row is done through a diode.
 *
 */

/************************************************************************/
/* Includes                                                             */
/************************************************************************/

#include "keyboard_ifc.h"

#include "delay.h"
#include "pinout.h"
#include "pin_config.h"

#include <avr/interrupt.h>
#include <stdint.h>

/************************************************************************/
/* Defines                                                              */
/************************************************************************/

#define OCR_DEBOUNCE_VAL 250 // This w prescaler @256 => 4ms debounce 
#define DEBOUNCE_MAX     5   // ~20ms total debounce

#define ROW_NUM 4
#define COL_NUM 3

#define COL_MASK 0x07 // 3 cols => 00000111
#define ROW_MASK 0x0F // 4 rows => 00001111

#define ROW(n) keyboard_out,n

/************************************************************************/
/* Private function declarations                                        */
/************************************************************************/

static void keyboard_init_timer(void);

/************************************************************************/
/* Private variables                                                    */
/************************************************************************/

static volatile uint8_t browse_debounce  = 0;
static volatile uint8_t confirm_debounce = 0;

/************************************************************************/
/* Function implementations                                             */
/************************************************************************/

/**
 * Initializes the keyboard matrix peripheral
 * 
 */
void keyboard_init(void)
{
	// Initialize keyboard rows as outputs
	// columns as pulled-up inputs
	InitOrPort(keyboard_out, ROW_MASK);
	InitAndPort(keyboard_in, ~COL_MASK);
	
	SetPort(keyboard_out, ROW_MASK);
	SetLoPort(keyboard_in, COL_MASK);

	keyboard_init_timer();
}

/**
 * Keyboard acquisition matrix sampling routine.
 * The pressed buttons are coded into a mask that has
 * the ith bit set to 1 if the ith key is pressed.
 *  
 * The mask pointer argument that is passed acts as 
 * the old mask from the last iteration, and the new 
 * mask if a different combination of keys was pressed.
 * 
 * @param mask the old mask, modified on key changes.
 * @return true a new key combination was detected
 * @return false same key combination was detected
 */
bool keyboard_acquire(uint16_t *mask)
{
	uint16_t cur_mask = 0;
	uint8_t columns;
	
	for(int i = 0; i < ROW_NUM; i++)
	{
		// ground one by one to check for key presses
		ResetPin(ROW(i));
		delay_ms(2);
		columns = GetPort(keyboard_in) & COL_MASK;
		
		for(int j = 0; j < COL_NUM; j++)
		{
			if(!(columns & (1 << j)))
			{
				cur_mask |= 1 << ((ROW_NUM-1)*i + j);
			}
			else
			{
				cur_mask &= ~(1 << ((ROW_NUM-1)*i + j));
			}
		}
		SetPin(ROW(i));
	}

	if(cur_mask != *mask)
	{
		// New key press
		*mask = cur_mask & 0x0FFF;
		return true;
	}
	return false;
}

/**
 * Returns the last reading from the debounced browse key
 * 
 */
inline __attribute__((always_inline))
bool keyboard_get_browse(void)
{
	return browse_debounce == DEBOUNCE_MAX;
}

/**
 * Returns the last reading from the debounced confirm key
 * 
 */
inline __attribute__((always_inline))
bool keyboard_get_confirm(void)
{
	return confirm_debounce == DEBOUNCE_MAX;
}


/************************************************************************/
/* Private Helpers                                                      */
/************************************************************************/

/**
 * Initializes the confirm and browse keys, together with the
 * timer used to debounce them. 
 * 
 */
static void keyboard_init_timer(void)
{
	InitInPin(browse);
	InitInPin(confirm);
	
	OCR0A = OCR_DEBOUNCE_VAL;

	TCCR0A = (0 << COM0A1) | (0 << COM0A0) | // Normal operation
	         (1 << WGM01)  | (0 << WGM00);   // Normal mode

	TCCR0B = (0 << WGM02) |                            // No CTC
	         (1 << CS02)  | (0 << CS01) | (0 << CS00); // f_clk/256 prescaler

	// Enable the compare match interrupt for channel A
	TIMSK0 = (1 << OCIE0A) | (0 << TOIE0);
}


ISR(TIMER0_COMPA_vect)
{
	if(GetPin(browse) && browse_debounce < DEBOUNCE_MAX)
	{
		browse_debounce++;
	}

	if(!GetPin(browse) && browse_debounce > 0)
	{
		browse_debounce--;
	}
	
	if(GetPin(confirm) && confirm_debounce < DEBOUNCE_MAX)
	{
		confirm_debounce++;
	}

	if(!GetPin(confirm) && confirm_debounce > 0)
	{
		confirm_debounce--;
	}
}
