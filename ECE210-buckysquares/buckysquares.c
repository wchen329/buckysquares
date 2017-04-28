// Name: buckysquares.c
// Author: Winor Chen
// Description:	Implementation of library pertaining to general functions involved in
//							maintenence, operation of the Buckysquares game.


#include "ece210_api.h"
#include "lab_buttons.h"
#include "game_board.h"
#include "multiplayer.h"
#include "buckysquares_menu.h"
#include "power_play.h"

#define EASY_DELAY 16
#define NORMAL_DELAY 8
#define HARD_DELAY 4
#define VERY_HARD_DELAY 2
#define DIVINE_DELAY 1

tetris_block current_state;


int multiplayer_process_data()
{
	int rows_to_bombard = NULL;
	int multiplayer_flags = NULL;
	
	if(ece210_wireless_data_avaiable())
		multiplayer_flags = ece210_wireless_get();
				
	else return 0;
	
	//If lost, stop game declare winner
	if((multiplayer_flags & (6144)) >> 11 == 2)
	{
				return 1;
	}
				
	rows_to_bombard = (multiplayer_flags >> 8) & 7;
	bombard_rows(rows_to_bombard); 
	
	return 0;
}

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
void launch_tetris_game(int is_online, int difficulty, int board_size, int sudden_death, int allow_bombarding, int pp)
{
	//Singleplayer Only
	int pp_count = 0;
	
	if(pp)
	{
		ece210_audio_init(200);
		ece210_audio_set_comparator_threshold(20);
	}
		
	//Multiplayer only
	int has_won = 0;
	int rows_to_bombard = 0;
	
	//Singleplayer and Multiplayer
	int game_is_on = 1;
	int** current_board = init_board(board_size);
	draw_walls();
	tetris_block_generate(&current_state, block_start_x, 0);
	int counter;
	int max_counter = 6;
	int rows_cleared;
	unsigned score = 0;
	
	switch(difficulty)
	{
		case 0:
			max_counter = EASY_DELAY;
			break;
		case 1:
			max_counter = NORMAL_DELAY;
			break;
		case 2:
			max_counter = HARD_DELAY;
			break;
		case 3:
			max_counter = VERY_HARD_DELAY;
			break;
		case 4:
			max_counter = DIVINE_DELAY;
			break;
	}
	
	while(game_is_on){
		
		counter = 0;
		
		while(counter < max_counter)
		{
			if(is_online && has_won != 2)
			{
				if(has_won != 1)
					has_won = multiplayer_process_data();
			}
			
			if(pp)
			{
				pp_count = attempt_pp_clear(pp_count, &current_state);
			}
			
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
					if(is_online)
					{
						if(has_won == 0)
							while(ece210_wireless_data_avaiable())
								has_won = multiplayer_process_data();
						if(has_won != 1)
						{
							has_won = 2;
							ece210_lcd_print_string("Sending information", 200, 100, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
							ece210_lcd_print_string("to opponent...", 170, 120, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
							while(!send_status(local_id_wireless, rows_to_bombard, 0, has_won))
							{
								ece210_wait_mSec(1000);
							}
						}
					}
			}
			
			if(game_is_on)
			{
				tetris_block_place(&current_state);
				rows_cleared = clear_completed_rows() / 10;
				rows_to_bombard += rows_cleared;
				score += (rows_cleared * 10);
				
				if(pp)
				{
					pp_count++;
					pp_update_led(pp_count);
				}
				
				tetris_block_generate(&current_state, block_start_x, 0);
				
				if(has_won == 1 && sudden_death)
				{
					game_is_on = 0;
				}
					
				// Bombard, if needed
				if(is_online){
			
					if(!allow_bombarding) rows_to_bombard = 0;
					if(rows_to_bombard != 0)
					{
						if(send_status(local_id_wireless, rows_to_bombard, 0, has_won))
							rows_to_bombard = 0;
					}
				}
			}
		}
	}
	
	char * score_str = unsigned_to_string(score);
	
	lcd_clear();
	if(!is_online)
	{
		ece210_lcd_print_string("GAME OVER!", 200, 20, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
		ece210_lcd_print_string("YOUR SCORE: ", 200, 60, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
		ece210_lcd_print_string(score_str, 200, 80, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
		ece210_lcd_print_string("(R) Exit", 75, 300, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	}
	
	else
	{
		lcd_clear();
		ece210_lcd_print_string("Waiting for", 190, 60, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
		ece210_lcd_print_string("opponent...", 170, 80, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
		int opp_score = 0;
		
		while(!verify_score(opp_score))
		{
			send_score(score);
			ece210_wait_mSec(1000);
			
			if(ece210_wireless_data_avaiable())
				opp_score = ece210_wireless_get();
		}
		
		while(!send_score(score))
		{
			ece210_wait_mSec(1000);
			send_score(score);
		}
		send_score(score);
		
		char * opp_score_str = unsigned_to_string(receive_score(opp_score));
		lcd_clear();
		
		if(has_won == 1) ece210_lcd_print_string("YOU WON!", 200, 20, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
		else ece210_lcd_print_string("YOU LOST!", 200, 20, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
		ece210_lcd_print_string("YOUR SCORE: ", 200, 60, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
		ece210_lcd_print_string(score_str, 200, 80, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
		ece210_lcd_print_string("OPPONENT'S SCORE: ", 200, 100, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
		ece210_lcd_print_string(opp_score_str, 200, 120, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
		ece210_lcd_print_string("(R) Exit", 75, 300, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	}
	
	delete_string(score_str);
	free_board(current_board);
	current_board = NULL;
	while(!btn_right_pressed());
}
