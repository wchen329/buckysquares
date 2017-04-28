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
 *			int sudden_death - dictates whether game ends when one player dies or when both die (multiplayer only)
 *			int allow_bombarding - allow sending other players rows (multiplayer only)
 *			int local_id - specifies the multiplayer id of the player, autos to 0 if singleplayer
 *			int pp - flag whether or not power plays are allowed or not (singleplayer only)
 */
void launch_tetris_game(int is_online, int difficulty, int board_size, int sudden_death, int allow_bombarding, int pp);
