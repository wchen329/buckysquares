// Name: buckysquares_menu.c
// Author: Winor Chen
// Description:	Implementation of library pertaining to general functions involved in
//							the user interface of Buckysquares.

/* Opens the main menu of Buckysquares where players can choose
 * which game mode (singleplayer or multiplayer) to play.
 *
 * Returns: integer flag corresponding to success (0) or failure (-1).
 */

#include "ece210_api.h"

char * welcome = "WELCOME TO BUCKYSQUARES";
char * singleplayer = "-> PLAY SINGLEPLAYER <-";
char * multiplayer = "-> PLAY MULTIPLAYER	<-";

int prompt_menu()
{
	ece210_lcd_add_msg(singleplayer, TERMINAL_ALIGN_CENTER, 0xFF);
	ece210_lcd_add_msg(multiplayer, TERMINAL_ALIGN_CENTER, 0xFF);
	return 0;
}

/* Polls to see if input for the menu was received.
 *
 * Returns: choice selected.
 *					0 - none, stay at menu
 *					1 - singleplayer
 *					2 - multiplayer
 */
int update_menu()
{
	return 0;
}

/* Tests to see if the board is currently connected to another player.
 *
 * Returns: integer flag corresponding to success (0) or failure (-1).
 */
int is_connected(int id)
{
	return -1;
}