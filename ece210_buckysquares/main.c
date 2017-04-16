//*****************************************************************************
// main.c
// Authors: Austin Maschott, Jason Yang, Michael Montross, Winor Chen
//*****************************************************************************

/******************************************************************************
 * Included Libraries
 *****************************************************************************/
#include "buckysquares.h"
#include "lab_buttons.h"

/******************************************************************************
 * Global Constants and Variables
 *****************************************************************************/
#define MOVE_PIXELS   	1							// Number of Pixels to move each time.
#define LCD_SIZE_X			240						// X Size of LCD screen in pixels
#define LCD_SIZE_Y			320						// Y Size of LCD screen in pixels
#define LCD_MAX_DRAW_X	LCD_SIZE_X-1	// 0 to LCD_MAX_DRAW_X is = LCD_SIZE_X
#define LCD_MAX_DRAW_Y	LCD_SIZE_Y-1	// 0 to LCD_MAX_DRAW_Y is = LCD_SIZE_Y
#define LCD_HALF_SIZE_X	LCD_SIZE_X/2	// X center of screen in pixels
#define LCD_HALF_SIZE_Y	LCD_SIZE_Y/2	// Y center of screen in pixels

int main()
{
	ece210_initialize_board();
	prompt_menu();
	
	while(1)
	{
		update_menu();
	}
}