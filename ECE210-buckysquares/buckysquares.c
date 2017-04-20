// Name: buckysquares.c
// Author: Winor Chen
// Description:	Implementation of library pertaining to general functions involved in
//							maintenence, operation of the Buckysquares game.


#include "ece210_api.h"
#include "lab_buttons.h"
#include "game_board.h"

tetris_block current_state;

/* Starts up a singleplayer tetris game.
 *
 */
void launch_singleplayer()
{
	int game_is_on = 1;
	init_board();
	draw_walls();
	tetris_block_generate(&current_state, 5, 0);
	int counter;
	unsigned score = 0;
	
	while(game_is_on){
		
		counter = 0;
		
		while(counter < 6)
		{		
			if(AlertButtons)
			{
				AlertButtons = 0;
				if(btn_up_pressed()) tetris_block_rotate(&current_state, 1);
				if(btn_down_pressed()) tetris_block_rotate(&current_state, 0);
				if(btn_left_pressed()) tetris_block_move(&current_state, 1);
				if(btn_right_pressed()) tetris_block_move(&current_state, 2);
			}
			
			if(ece210_ps2_read_position() == PS2_DOWN) tetris_block_move(&current_state, 0);
			if(ece210_ps2_read_position() == PS2_LEFT) tetris_block_move(&current_state, 1);
			if(ece210_ps2_read_position() == PS2_RIGHT) tetris_block_move(&current_state, 2);
				
			ece210_wait_mSec(50);
			counter++;
		}
		
		if(tetris_block_move(&current_state, 0) != 0)
		{
			if(current_state.blocks[0].x == 5 && current_state.blocks[0].y == 0)
			{
				game_is_on = 0;
			}
			
			if(game_is_on)
			{
				tetris_block_place(&current_state);
				score += clear_completed_rows();
				tetris_block_generate(&current_state, 5, 0);
			}
		}
	}
	
	char * score_str = unsigned_to_string(score);
	ece210_lcd_add_msg("", TERMINAL_ALIGN_CENTER, LCD_COLOR_WHITE);
	ece210_lcd_add_msg("GAME OVER.", TERMINAL_ALIGN_CENTER, LCD_COLOR_WHITE);
	ece210_lcd_add_msg("SCORE: ", TERMINAL_ALIGN_CENTER, LCD_COLOR_WHITE);
	ece210_lcd_add_msg(score_str, TERMINAL_ALIGN_CENTER, LCD_COLOR_WHITE);
	ece210_lcd_add_msg("(Tap) Return to Menu.", TERMINAL_ALIGN_CENTER, LCD_COLOR_WHITE);
	delete_string(score_str);
	
	while(true);
}