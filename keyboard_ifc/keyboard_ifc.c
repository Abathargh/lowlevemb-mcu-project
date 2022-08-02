/**
 * keyboard_ifc.c
 *
 * This module implements the keyboard interface logic.
 *
 * Author: mar
 */

/************************************************************************/
/* Includes                                                             */
/************************************************************************/

#include "keyboard_ifc.h"

#include "delay.h"
#include "pinout.h"
#include "pin_config.h"

#include <avr/interrupt.h>

/************************************************************************/
/* Defines                                                              */
/************************************************************************/

#define ROW_NUM 4
#define COL_NUM 3

#define COL_MASK 0x07 // 3 cols => 00000111
#define ROW_MASK 0x0F // 4 rows => 00001111

#define ROW(n) keyboard_out,n


/************************************************************************/
/* Function implementations                                             */
/************************************************************************/

/**
 * Initializes the keyboard matrix peripheral
 * 
 */
void keyboard_init(void)
{
	InitOrPort(keyboard_out, ROW_MASK);
	InitAndPort(keyboard_in, ~COL_MASK);
	
	SetPort(keyboard_out, ROW_MASK);
	SetLoPort(keyboard_in, COL_MASK);
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
		*mask = cur_mask;
		return true;
	}
	return false;
}
