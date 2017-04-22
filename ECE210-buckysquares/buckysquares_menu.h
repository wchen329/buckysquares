// Name: buckysquares_menu.h
// Author: Winor Chen
// Description:	Library pertaining to general functions involved in
//							maintenence, operation, or general UX elements in the
//							Buckysquares game.

/* Resets the state of the screen by settings all pixels to black.
 */
void lcd_clear(void);

/* Opens the main menu of Buckysquares where players can choose
 * which game mode (singleplayer or multiplayer) to play.
 *
 * Returns: integer flag corresponding to success (0) or failure (-1).
 */
int prompt_menu(void);

/* Polls to see if input for the menu was received and/or updates the
 * color of the text on the menu
 *
 * Returns: choice selected.
 *					0 - none, stay at menu
 *					1 - singleplayer
 *					2 - multiplayer
 */
int update_menu(void);

/* Test to see if the board is currently connected to another player.
 *
 * Returns: integer flag corresponding to success (0) or failure (-1).
 */
int is_connected(int id);

/* Launches the singleplayer menu where the player can choose Difficulty settings
 * or Board Size and then start a game.
 */
void singleplayer_menu(void);

/* Launches the multiplayer menu where the local player can specify the remote ID of the player
 * that they wish to connect to and toggle other settings.
 */
void multiplayer_menu(void);
