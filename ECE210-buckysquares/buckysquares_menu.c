// Name: buckysquares_menu.c
// Author: Winor Chen
// Description:	Implementation of library pertaining to general functions involved in
//							the user interface of Buckysquares.

#include "ece210_api.h"
#include "lab_buttons.h"
#include "multiplayer.h"
#include "buckysquares.h"

/* Resets the state of the screen by settings all pixels to black.
 */
void lcd_clear()
{
	ece210_lcd_draw_rectangle(0, 240, 0, 320, LCD_COLOR_BLACK);
}

/* Polls to see if input for the menu was received.
 *
 * Returns: choice selected.
 *					0 - none, stay at menu
 *					1 - singleplayer
 *					2 - multiplayer
 */
int update_menu(int choice)
{
	
	if(choice == 0 && ece210_ps2_read_position() == PS2_DOWN)
	{
		ece210_lcd_print_string("PLAY SINGLEPLAYER", 220, 200, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
		ece210_lcd_print_string("PLAY MULTIPLAYER", 220, 230, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
		choice = 1;
	}
	
	if(choice == 1 && ece210_ps2_read_position() == PS2_UP)
	{
		ece210_lcd_print_string("PLAY SINGLEPLAYER", 220, 200, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
		ece210_lcd_print_string("PLAY MULTIPLAYER", 220, 230, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
		choice = 0;
	}
	
	return choice;
}

/* Launches the singleplayer menu where the player can choose Difficulty settings
 * or Board Size and then start a game.
 */
void singleplayer_menu()
{
	int next = -1;
	int choice = 0;
	int difficulty = 1;
	int old_difficulty = 1;
	int board_size = 0;
	int old_board_size = 0;
	int power_plays = 0;
	int old_power_plays = 0;
	char has_used_ps2 = 0;
	
	char * text_difficulty = "Difficulty: Normal";
	char * text_board_size = "Board Size: Normal";
	char * text_power_plays = "Power Plays: Off";
	
	lcd_clear();
	ece210_lcd_print_string("Singleplayer Setup...", 230, 20, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	ece210_lcd_print_string(text_difficulty, 220, 80, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
	ece210_lcd_print_string(text_board_size, 220, 100, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	ece210_lcd_print_string(text_power_plays, 220, 120, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	ece210_lcd_print_string("(R) Play", 75, 300, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	ece210_lcd_print_string("(L) Back", 230, 300, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	
	while(next < 0)
	{
		has_used_ps2 = 0;
		
		if(choice == 0 && ece210_ps2_read_position() == PS2_LEFT) {difficulty--; has_used_ps2 = 1;}
		if(choice == 0 && ece210_ps2_read_position() == PS2_RIGHT && !has_used_ps2) {difficulty++; has_used_ps2 = 1;}
		if(difficulty < 0) difficulty = 4; if(difficulty > 4) {difficulty = 0;}
		if(choice == 1 && ece210_ps2_read_position() == PS2_LEFT && !has_used_ps2) {board_size--; has_used_ps2 = 1;}
		if(choice == 1 && ece210_ps2_read_position() == PS2_RIGHT && !has_used_ps2) {board_size++; has_used_ps2 = 1;}
		if(board_size < 0) board_size = 2; if(board_size > 2) {board_size = 0;}
		if(choice == 2 && ece210_ps2_read_position() == PS2_LEFT && !has_used_ps2) {power_plays--; has_used_ps2 = 1;}
		if(choice == 2 && ece210_ps2_read_position() == PS2_RIGHT && !has_used_ps2) {power_plays++; has_used_ps2 = 1;}
		if(power_plays < 0) power_plays = 1; if(power_plays > 1) {power_plays = 0;}
		
		switch(difficulty)
		{
			case 0:
				text_difficulty = "Difficulty: Easy";
				break;
			case 1:
				text_difficulty = "Difficulty: Normal";
				break;
			case 2:
				text_difficulty = "Difficulty: Hard";
				break;
			case 3:
				text_difficulty = "Difficulty: Very Hard";
				break;
			case 4:
				text_difficulty = "Difficulty: Divine";
				break;
		}
		
		switch(board_size)
		{
			case 0:
				text_board_size = "Board Size: Normal";
				break;
			case 1:
				text_board_size = "Board Size: Large";
				break;
			case 2:
				text_board_size = "Board Size: Small";
				break;
		}
		
		switch(power_plays)
		{
			case 0:
				text_power_plays = "Power Plays: Off";
				break;
			
			case 1:
				text_power_plays = "Power Plays: On";
				break;
		}
		
		if(old_difficulty != difficulty)
		{
			ece210_lcd_draw_rectangle(0, 240, 80, 20, LCD_COLOR_BLACK);
			ece210_lcd_print_string(text_difficulty, 220, 80, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
			old_difficulty = difficulty;
		}
		
		if(old_board_size != board_size)
		{
			ece210_lcd_draw_rectangle(0, 240, 100, 20, LCD_COLOR_BLACK);
			ece210_lcd_print_string(text_board_size, 220, 100, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
			old_board_size = board_size;
		}
		
		if(old_power_plays != power_plays)
		{
			ece210_lcd_draw_rectangle(0, 240, 120, 20, LCD_COLOR_BLACK);
			ece210_lcd_print_string(text_power_plays, 220, 120, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
			old_power_plays = power_plays;
		}
		
		if(choice == 0 && ece210_ps2_read_position() == PS2_DOWN && !has_used_ps2)
		{
			ece210_lcd_print_string(text_difficulty, 220, 80, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
			ece210_lcd_print_string(text_board_size, 220, 100, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
			choice = 1;
			has_used_ps2 = 1;
		}
	
		if(choice == 1 && ece210_ps2_read_position() == PS2_UP && !has_used_ps2)
		{
			ece210_lcd_print_string(text_difficulty, 220, 80, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
			ece210_lcd_print_string(text_board_size, 220, 100, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
			choice = 0;
			has_used_ps2 = 1;
		}
		
		if(choice == 1 && ece210_ps2_read_position() == PS2_DOWN && !has_used_ps2)
		{
			ece210_lcd_print_string(text_board_size, 220, 100, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
			ece210_lcd_print_string(text_power_plays, 220, 120, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
			choice = 2;
			has_used_ps2 = 1;
		}
		
		if(choice == 2 && ece210_ps2_read_position() == PS2_UP && !has_used_ps2)
		{
			ece210_lcd_print_string(text_board_size, 220, 100, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
			ece210_lcd_print_string(text_power_plays, 220, 120, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
			choice = 1;
			has_used_ps2 = 1;
		}
		
		while(ece210_ps2_read_position() != PS2_CENTER && has_used_ps2);
		
		if(AlertButtons)
		{
			AlertButtons = 0;
			if(btn_right_pressed())
			{
				next = 1;
				launch_tetris_game(0, difficulty, board_size, 1, 1, power_plays);
			}
		
			else if(btn_left_pressed())
			{
				next = 0;
			}
		}
		
		
	}
}

/* Launches the multiplayer menu where the local player can specify the remote ID of the player
 * that they wish to connect to and toggle other settings.
 */
void multiplayer_menu()
{
	
	char local_id[3] = {'0', '0', '1'};
	char remote_id[3] = {'0', '0', '1'};
	int allow_bombard = 1;
	int sudden_death = 1;
	int unique = 1;
	int menu_active = 1;
	char choice = 0;
	char ps2_inactive = 0;
	char * text_bombard = "Allow Bombarding: On";
	char * text_sudden_death = "Sudden Death: On";
	
	lcd_clear();
	ece210_lcd_print_string("Multiplayer Setup...", 230, 20, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	ece210_lcd_print_string("Local ID:", 220, 80, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
	ece210_lcd_print_string(local_id, 200, 100, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	ece210_lcd_print_string("Remote ID:", 220, 120, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	ece210_lcd_print_string(remote_id, 200, 140, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	ece210_lcd_print_string(text_bombard, 220, 160, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	ece210_lcd_print_string(text_sudden_death, 220, 180, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	ece210_lcd_print_string("(R) Start", 75, 300, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	ece210_lcd_print_string("(L) Back", 230, 300, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	
	while(menu_active){
	
		if(choice == 0 && ece210_ps2_read_position() == PS2_DOWN && !ps2_inactive)
		{
			ece210_lcd_print_string("Local ID:", 220, 80, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
			ece210_lcd_print_string("Remote ID:", 220, 120, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
			choice = 1;
			ps2_inactive = 1;
		}
		
		if(choice == 1 && !ps2_inactive)
		{
				switch(ece210_ps2_read_position())
				{
					case PS2_UP:
						ece210_lcd_print_string("Local ID:", 220, 80, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
						ece210_lcd_print_string("Remote ID:", 220, 120, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
						choice = 0;
						ps2_inactive = 1;
						break;
				
					case PS2_DOWN:
						ece210_lcd_print_string("Remote ID:", 220, 120, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
						ece210_lcd_print_string(text_bombard, 220, 160, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
						choice = 2;
						ps2_inactive = 1;
						break;
				}
		}
	
		if(choice == 2 && !ps2_inactive)
		{
				switch(ece210_ps2_read_position())
				{
					case PS2_UP:
						ece210_lcd_print_string("Remote ID:", 220, 120, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
						ece210_lcd_print_string(text_bombard, 220, 160, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
						choice = 1;
						ps2_inactive = 1;
						break;
				
					case PS2_DOWN:
						ece210_lcd_print_string(text_bombard, 220, 160, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
						ece210_lcd_print_string(text_sudden_death, 220, 180, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
						choice = 3;
						ps2_inactive = 1;
						break;
				}
		}
	
		if(choice == 3 && ece210_ps2_read_position() == PS2_UP && !ps2_inactive)
		{
			ece210_lcd_print_string(text_bombard, 220, 160, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
			ece210_lcd_print_string(text_sudden_death, 220, 180, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
			choice = 2;
			ps2_inactive = 1;
		}
		
		//LOCAL ID
		if(choice == 0 && ece210_ps2_read_position() == PS2_RIGHT && !ps2_inactive)
		{
		
			local_id[2]++;
			if(local_id[2] > '9'){ local_id[1]++; local_id[2] = '0';	}
			if(local_id[1] > '9'){ local_id[0]++; local_id[1] = '0'; }
			if(local_id[0] == '2' && local_id[1] == '5' && local_id[2] > '5')
			{
				local_id[0] = '0'; local_id[1] = '0'; local_id[2] = '1';
			}
		
		ece210_lcd_print_string(local_id, 200, 100, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
			
		}
	
		if(choice == 0 && ece210_ps2_read_position() == PS2_LEFT && !ps2_inactive)
		{
			local_id[2]--;
			if(local_id[0] == '0' && local_id[1] == '0' && local_id[2] == '0')
			{
				local_id[0] = '2'; local_id[1] = '5'; local_id[2] = '5';
			}
			
			else
			{
				if(local_id[2] < '0'){ local_id[1]--; local_id[2] = '9';	}
				if(local_id[1] < '0'){ local_id[0]--; local_id[1] = '9'; }
			}
			
			ece210_lcd_print_string(local_id, 200, 100, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
		}
		
		//REMOTE ID
		if(choice == 1 && ece210_ps2_read_position() == PS2_RIGHT && !ps2_inactive)
		{
		
			remote_id[2]++;
			if(remote_id[2] > '9'){ remote_id[1]++; remote_id[2] = '0';	}
			if(remote_id[1] > '9'){ remote_id[0]++; remote_id[1] = '0'; }
			if(remote_id[0] == '2' && remote_id[1] == '5' && remote_id[2] > '5')
			{
				remote_id[0] = '0'; remote_id[1] = '0'; remote_id[2] = '1';
			}
		
		ece210_lcd_print_string(remote_id, 200, 140, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
			
		}
	
		if(choice == 1 && ece210_ps2_read_position() == PS2_LEFT && !ps2_inactive)
		{
			remote_id[2]--;
			if(remote_id[0] == '0' && remote_id[1] == '0' && remote_id[2] == '0')
			{
				remote_id[0] = '2'; remote_id[1] = '5'; remote_id[2] = '5';
			}
			
			else
			{
				if(remote_id[2] < '0'){ remote_id[1]--; remote_id[2] = '9';	}
				if(remote_id[1] < '0'){ remote_id[0]--; remote_id[1] = '9'; }
			}
			
			ece210_lcd_print_string(remote_id, 200, 140, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
		}
		
		//ALLOW BOMBARDING
		if(choice == 2 && (ece210_ps2_read_position() == PS2_LEFT || ece210_ps2_read_position() == PS2_RIGHT) && !ps2_inactive)
		{
			switch(allow_bombard)
			{
				case 0:
					text_bombard = "Allow Bombarding: On";
					allow_bombard = 1;
					ece210_lcd_draw_rectangle(0, 240, 160, 20, LCD_COLOR_BLACK);
					ece210_lcd_print_string(text_bombard, 220, 160, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
					break;
				
				case 1:
					text_bombard = "Allow Bombarding: Off";
					allow_bombard = 0;
					ece210_lcd_draw_rectangle(0, 240, 160, 20, LCD_COLOR_BLACK);
					ece210_lcd_print_string(text_bombard, 220, 160, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
					break;
			}
		}
		
		//SUDDEN DEATH
		if(choice == 3 && (ece210_ps2_read_position() == PS2_LEFT || ece210_ps2_read_position() == PS2_RIGHT) && !ps2_inactive)
		{
			switch(sudden_death)
			{
				case 0:
					text_sudden_death = "Sudden Death: On";
					sudden_death = 1;
					ece210_lcd_draw_rectangle(0, 240, 180, 20, LCD_COLOR_BLACK);
					ece210_lcd_print_string(text_sudden_death, 220, 180, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
					break;
				
				case 1:
					text_sudden_death = "Sudden Death: Off";
					sudden_death = 0;
					ece210_lcd_draw_rectangle(0, 240, 180, 20, LCD_COLOR_BLACK);
					ece210_lcd_print_string(text_sudden_death, 220, 180, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
					break;
			}
		}
		
		while(ece210_ps2_read_position() != PS2_CENTER);
		ps2_inactive = 0;
		
		if(btn_left_pressed() && AlertButtons)
		{
				menu_active = 0;
		}
		
		if(btn_right_pressed() && AlertButtons)
		{
			AlertButtons = 0;
			char remote_id_num = remote_id[2]-'0' + (remote_id[1] - '0')*10 + (remote_id[0] - '0') * 100;
			char local_id_num = local_id[2] - '0' + (local_id[1] - '0') * 10 + (local_id[0] - '0') * 100;
			
			if(remote_id_num == local_id_num)
			{
				ece210_lcd_print_string("XXXXXXXXXXXXXXXXXXXX.", 220, 240, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
				ece210_lcd_print_string("IDs must be unique.", 220, 240, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
				unique = 0;
			}
			
			else unique = 1;
			
			if(!unique)
			{
				ece210_wireless_init(0,0);
			}
			
			if(unique)
			{
			
				if(!multiplayer_init(local_id_num, remote_id_num, allow_bombard, sudden_death))
				{
					ece210_lcd_print_string("XXXXXXXXXXXXXXXXXXXX.", 220, 240, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
					ece210_lcd_print_string("Could not connect.", 220, 240, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
					ece210_wireless_init(0,0);
				}
			
				else
				{
						launch_tetris_game(1, 1, 0, sudden_death, allow_bombard, 0);
						while(!btn_right_pressed());
						return;
				}
			}
		}
	}
}

/* Opens the main menu of Buckysquares where players can choose
 * which game mode (singleplayer or multiplayer) to play.
 *
 * Returns: integer flag corresponding to success (0) or failure (-1).
 */
int prompt_menu()
{
	ece210_lcd_print_string("Welcome to...", 220, 40, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
	ece210_lcd_print_string("BUCKYSQUARES", 210, 60, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	ece210_lcd_print_string("PLAY SINGLEPLAYER", 220, 200, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
	ece210_lcd_print_string("PLAY MULTIPLAYER", 220, 230, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	ece210_lcd_print_string("(R) Next", 75, 300, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	int chosen = -1;
	int choice = 0;
	ece210_wireless_init(0,0);
	while(chosen < 0)
	{
		if(btn_right_pressed())
		{
			AlertButtons = 0;
			chosen = 1;
		}
		choice = update_menu(choice);
	}
	return choice;
}

/* Tests to see if the board is currently connected to another player.
 *
 * Returns: integer flag corresponding to success (0) or failure (-1).
 */
int is_connected(int id)
{
	return -1;
}
