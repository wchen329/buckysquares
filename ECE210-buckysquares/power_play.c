// Name: buckysquares_menu.c
// Author: Michael Montross, Jason Yang, and Winor Chen
// Description:	Implementation of Library used for implementing
//							PowerPlays in Singleplayer.

#include "ece210_api.h"
#include "game_board.h"

#define WHITE_INTENSITY 150

int current_led = 0;


/* Gives a flashing alternate array of lights if a power play
 * is ready to be used.
 */
void pp_show_ready()
{
	ece210_ws2812b_write(0, 0, 0, 0);
	ece210_ws2812b_write(1, 0, 0, 0);
	ece210_ws2812b_write(2, 0, 0, 0);
	ece210_ws2812b_write(3, 0, 0, 0);
	ece210_ws2812b_write(4, 0, 0, 0);
	ece210_ws2812b_write(5, 0, 0, 0);
	ece210_ws2812b_write(6, 0, 0, 0);
	ece210_ws2812b_write(7, 0, 0, 0);
	
	ece210_ws2812b_write(current_led, 255, 255, 255);
	
	current_led++;
	if(current_led == 7)
		current_led = 0;
}

/* Updates the LED array corresponding to how close the player
 * is to achieving a power play.
 *
 * Accepts Arguments: int pp_count - the amount out of 80 that a player has towards
 *																	 their next power play
 */
void pp_update_led(int pp_count)
{
	if(pp_count == 0)
	{
		ece210_ws2812b_write(current_led, 0, 0, 0);
		current_led = 0;
	}
	if(pp_count == 1) ece210_ws2812b_write(0, WHITE_INTENSITY, WHITE_INTENSITY, WHITE_INTENSITY);
	if(pp_count == 2) ece210_ws2812b_write(1, WHITE_INTENSITY, WHITE_INTENSITY, WHITE_INTENSITY);
	if(pp_count == 3) ece210_ws2812b_write(2, WHITE_INTENSITY, WHITE_INTENSITY, WHITE_INTENSITY);
	if(pp_count == 4) ece210_ws2812b_write(3, WHITE_INTENSITY, WHITE_INTENSITY, WHITE_INTENSITY);
	if(pp_count == 5) ece210_ws2812b_write(4, WHITE_INTENSITY, WHITE_INTENSITY, WHITE_INTENSITY);
	if(pp_count == 6) ece210_ws2812b_write(5, WHITE_INTENSITY, WHITE_INTENSITY, WHITE_INTENSITY);
	if(pp_count == 7) ece210_ws2812b_write(6, WHITE_INTENSITY, WHITE_INTENSITY, WHITE_INTENSITY);
	if(pp_count >= 8) pp_show_ready();
}

/* Attempts to use a power play to clear the tetris board.
 *
 * Accepts Arguments: int pp_count - the amount out of 80 that a player has towards
 *																	 their next power play
 */
int attempt_pp_clear(int pp_count, tetris_block * current_state)
{
	int verification = ece210_audio_comparator_above_threshold();
	if(pp_count >= 8 && verification)
	{
			clear_board();
			tetris_block_generate(current_state, block_start_x, 0);
			return 0;
	}
		
	return pp_count;
}
