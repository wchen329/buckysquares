// Name: buckysquares_menu.h
// Author: Jason Yang and Michael Montross
// Description:	Library used for implementing PowerPlays in Singleplayer.

#include "game_board.h"

/* Updates the LED array corresponding to how close the player
 * is to achieving a power play.
 *
 * Accepts Arguments: int pp_count - the amount out of 80 that a player has towards
 *																	 their next power play
 */
void pp_update_led(int pp_count);

/* Attempts to use a power play to clear the tetris board.
 *
 * Accepts Arguments: int pp_count - the amount out of 80 that a player has towards
 *																	 their next power play
 */
int attempt_pp_clear(int pp_count, tetris_block * current_state);
