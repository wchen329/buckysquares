// Name: buckysquares.h
// Author: Winor Chen
// Description:	Library pertaining to general functions involved in
//							maintenence, operation, or general UX elements in the
//							Buckysquares game.

/* Starts up a tetris session
 * 
 * Parameters:
 *			int is_online - 0 game is singleplayer, 1 game is multiplayer
 *			int difficulty - dictates drop speed
 *			int board_size - dictates how large the tetris board is drawn
 *			int sudden_death - dictates whether game ends when one player dies or when both die
 *			int allow_bombarding - allow sending other players rows
 *
 */
void launch_tetris_game(int is_online, int difficulty, int board_size, int sudden_death, int allow_bombarding);
