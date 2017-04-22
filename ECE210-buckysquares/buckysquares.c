// Name: buckysquares.c
// Author: Winor Chen
// Description:	Implementation of library pertaining to general functions involved in
//							maintenence, operation of the Buckysquares game.


#include "ece210_api.h"
#include "lab_buttons.h"
#include "game_board.h"
#include "multiplayer.h"
#include "buckysquares_menu.h"

tetris_block current_state;

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
void launch_tetris_game(int is_online, int difficulty, int board_size, int sudden_death, int allow_bombarding)
{
	int game_is_on = 1;
	int** current_board = init_board(board_size);
	draw_walls();
	tetris_block_generate(&current_state, block_start_x, 0);
	int counter;
	int max_counter = 6;
	unsigned score = 0;
	
	switch(difficulty)
	{
		case 0:
			max_counter = 10;
			break;
		case 1:
			max_counter = 6;
			break;
		case 2:
			max_counter = 4;
			break;
		case 3:
			max_counter = 2;
			break;
		case 4:
			max_counter = 1;
			break;
	}
	
	while(game_is_on){
		
		counter = 0;
		
		while(counter < max_counter)
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
			if(current_state.blocks[0].x == block_start_x && current_state.blocks[0].y == 0)
			{
				game_is_on = 0;
			}
			
			if(game_is_on)
			{
				tetris_block_place(&current_state);
				score += clear_completed_rows();
				tetris_block_generate(&current_state, block_start_x, 0);
			}
		}
	}
	
	char * score_str = unsigned_to_string(score);
	lcd_clear();
	ece210_lcd_print_string("GAME OVER!", 200, 20, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	ece210_lcd_print_string("YOUR SCORE: ", 200, 60, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	ece210_lcd_print_string(score_str, 200, 80, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	ece210_lcd_print_string("(R) Exit", 75, 300, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	delete_string(score_str);
	free_board(current_board);
	current_board = NULL;
	while(!btn_right_pressed());
}
