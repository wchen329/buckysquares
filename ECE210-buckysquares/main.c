//*****************************************************************************
// main.c
// Authors: Austin Maschott, Jason Yang, Michael Montross, Winor Chen
//*****************************************************************************

/******************************************************************************
 * Included Libraries
 *****************************************************************************/
#include "buckysquares.h"
#include "buckysquares_menu.h"
#include "game_board.h"
#include "lab_buttons.h"

void (* menu_selection[2])();

/* Main routine.
 */
int main()
{
	ece210_initialize_board();
	menu_selection[0] = singleplayer_menu;
	menu_selection[1] = multiplayer_menu;
	
	while(1)
	{
		menu_selection[prompt_menu()]();
		lcd_clear();
	}	
}
