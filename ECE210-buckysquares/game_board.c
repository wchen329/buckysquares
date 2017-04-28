// Name: gameboard.c
// Author: Winor Chen
// Description:	Holds data and functions pertaining to the representation
//							of the tetris game board.

#include "ece210_api.h"
#include "game_board.h"
#include <stdlib.h>
#include <string.h>

/* The Tetris Board represented as an array of flags
 * 1 at a position represents occupied by block 0 represents not occupied
 */
int ** block_array;
int block_height = 0;
int block_length = 0;
int block_start_x = 0;
int board_height = 0;
int board_length = 0;
int board_offset_x = 0;

/* Renders a single unit block on position(x,y) the screen.
 *
 * Accepts arguments:
 *	int x - the x co-ordinate of the block to write
 *	int y - the y co-ordinate of the block to write
 *	int erase - flag 1 write black (or erase the block from the LCD) or 0 write a block of random color 
 *	int block_color - the color of the block to render. 0x0 is a random color unless erase is asserted then black is the color
 */
int block_render(int x, int y, int erase, int block_color)
{
	int color;
	
	if(erase)
	{ 
		color = LCD_COLOR_BLACK;
	}	
	
	else
	{
		color = block_color;
	}
		
	if(!color && !erase)
	{
		unsigned char color_choose = rand() % 8;
	
		switch(color_choose)
		{
			case 1:
				color = LCD_COLOR_GREEN;
				break;
		
			case 2:
				color = LCD_COLOR_CYAN;
				break;
		
			case 3:
				color = LCD_COLOR_RED;
				break;
		
			case 4:
				color = LCD_COLOR_YELLOW;
				break;
		
			case 5:	
				color = LCD_COLOR_MAGENTA;
				break;
		
			case 6:
				color = LCD_COLOR_BLUE2;
				break;
		
			case 7:
				color = LCD_COLOR_GREEN2;
				break;
		
			default:
				color = LCD_COLOR_BROWN;
				break;
		}
	}
	
	//Write one block on to the LCD
	ece210_lcd_draw_rectangle(x * block_length + board_offset_x, block_length, y * block_height, block_height, color);
	return color;
}

/* Initializes the tetris board to be empty
 * (all zero values).
 * Return a pointer to the block array.
 */
int ** init_board(int board_size)
{
	switch(board_size)
	{
		
		case 0:
			block_height = 16;
			block_length = 16;
			board_height = 18;
			board_length = 10;
			break;
		case 1:
			block_height = 10;
			block_length = 10;
			board_height = 30;
			board_length = 20;
			break;
		case 2:
			block_height = 20;
			block_length = 20;
			board_height = 14;
			board_length = 8;
			
			break;
	}
	
	board_offset_x = (240 - (block_length * board_length))/2;
	block_start_x = board_length / 2;
	block_array = malloc(board_height * sizeof(int*));
	
	for(int dec_itr = 0; dec_itr < board_height; dec_itr++)
	{
		*(block_array + dec_itr) = malloc(board_length * sizeof(int));
	}
	
	for(int i = 0; i < board_height; i++)
	{
		for(int j = 0; j < board_length; j++)
		{
			block_array[i][j] = 0;
			block_render(j, i, 1, 0);
		}
	}	

	return ((int**)(&block_array));
}

/* Clears the tetris board without reinitializing
 * another board in memory.
 */
void clear_board()
{
	for(int i = 0; i < board_height; i++)
	{
		for(int j = 0; j < board_length; j++)
		{
			block_array[i][j] = 0;
			block_render(j, i, 1, 0);
		}
	}
}

/* Renders a given tetris block on the screen.
 * Renders the block in a random ROYGBV color.
 *
 * Accepts arguments:
 *	tetris_block * block - pointer to block desired to write.
 *	int erase - flag 1 write black (or erase the block from the LCD) or 0 write a block of random color
 *
 * Returns - the color the tetris block was rendered in
 */
int tetris_block_render(tetris_block * block, int erase)
{
	int color = LCD_COLOR_BLACK;
	
	if(!erase)
	{
		unsigned char color_choose = rand() % 8;
	
		switch(color_choose)
		{
			case 1:
				color = LCD_COLOR_GREEN;
				break;
		
			case 2:
				color = LCD_COLOR_CYAN;
				break;
		
			case 3:
				color = LCD_COLOR_RED;
				break;
		
			case 4:
				color = LCD_COLOR_YELLOW;
				break;
		
			case 5:	
				color = LCD_COLOR_MAGENTA;
				break;
		
			case 6:
				color = LCD_COLOR_BLUE2;
				break;
		
			case 7:
				color = LCD_COLOR_GREEN2;
				break;
		
			default:
				color = LCD_COLOR_BROWN;
				break;
		}
	}
	
	//Write each block on to the LCD
	for(int i = 0; i < 4; i++)
	{
		ece210_lcd_draw_rectangle(block->blocks[i].x * block_length + board_offset_x,
				block_length,block->blocks[i].y * block_height, block_height, color);
	}
	
	return color;
}

/* Generates a new tetris block based off of a
 * base point by modifying "block" which is passed in
 * through struct pointer
 */
void tetris_block_generate(tetris_block * block, int xpos, int ypos)
{
	
	char random_number = rand() % 6;
	char block_type = random_number;
	
	switch(block_type)
	{
		
		// 0 is a straight
		case 0:
			block -> blocks[0].x = xpos; block -> blocks[0].y = ypos;
			block -> blocks[1].x = xpos - 1; block -> blocks[1].y = ypos;
			block -> blocks[2].x = xpos + 1; block -> blocks[2].y = ypos;
			block -> blocks[3].x = xpos - 2; block -> blocks[3].y = ypos;
			break;	
		
		// 1 is a square
		case 1:
			block -> blocks[0].x = xpos; block -> blocks[0].y = ypos;
			block -> blocks[1].x = xpos - 1; block -> blocks[1].y = ypos;
			block -> blocks[2].x = xpos; block -> blocks[2].y = ypos + 1;
			block -> blocks[3].x = xpos - 1; block -> blocks[3].y = ypos + 1;
			break;
		
		// 2 is a T shape
		case 2:
			block -> blocks[0].x = xpos; block -> blocks[0].y = ypos;
			block -> blocks[1].x = xpos - 1; block -> blocks[1].y = ypos;
			block -> blocks[2].x = xpos + 1; block -> blocks[2].y = ypos;
			block -> blocks[3].x = xpos; block -> blocks[3].y = ypos + 1;
			break;
		
		// 3 is a L shape (Right Handed)
		case 3:
			block -> blocks[0].x = xpos; block -> blocks[0].y = ypos;
			block -> blocks[1].x = xpos - 1; block -> blocks[1].y = ypos;
			block -> blocks[2].x = xpos - 2; block -> blocks[2].y = ypos;
			block -> blocks[3].x = xpos; block -> blocks[3].y = ypos + 1;
			break;
		
		// 4 is a S shape
		case 4:
			block -> blocks[0].x = xpos; block -> blocks[0].y = ypos;
			block -> blocks[1].x = xpos + 1; block -> blocks[1].y = ypos;
			block -> blocks[2].x = xpos; block -> blocks[2].y = ypos + 1;
			block -> blocks[3].x = xpos - 1; block -> blocks[3].y = ypos + 1;
			break;
	
		// 5 is a L shape (Left Handed)
		case 5:
			block -> blocks[0].x = xpos; block -> blocks[0].y = ypos;
			block -> blocks[1].x = xpos - 1; block -> blocks[1].y = ypos;
			block -> blocks[2].x = xpos - 2; block -> blocks[2].y = ypos;
			block -> blocks[3].x = xpos - 2; block -> blocks[3].y = ypos + 1;
			break;
	}
	
	//Used when rotating
	block -> version = 0;
	block -> type = block_type;
	
	//Write the block to the LCD
	block -> color = tetris_block_render(block, 0);
}

/* Attempts to move the block in the indicated direction. If there is a collision
 * with pre-existing blocks or the wall, do not move the blocks
 *
 * Accepts arguments:
 *		tetris_block * block - pointer to block desired to be moved
 * 		char direction - 0 down, 1 left, 2 right
 *
 * Returns: integer flag 0 if move successful 1 if collision occurred no move 
 */
int tetris_block_move(tetris_block * block, unsigned char direction)
{
	
	switch(direction)
	{
		case 0:
			
		
			//Special Case: check for out of bounds
			for(int i = 0; i < 4; i++)
			{
				if((block -> blocks[i].y + 1) >= board_height)
				{
				return 1;
				}
			}
				
			//General Case
			for(int i = 0; i < 4; i++)
			{
				if(block_array[block -> blocks[i].y + 1][block -> blocks[i].x] != 0)
				{
					return 1;
				}
			}
			
			//Erase former position / state of the block
			tetris_block_render(block, 1);
			
			// Update new position and write to the LCD
			block -> blocks[0].y++;
			block -> blocks[1].y++;
			block -> blocks[2].y++;
			block -> blocks[3].y++;
			block -> color = tetris_block_render(block, 0);
			
			break;
		
		case 1:
			
			// Special Case: check for out of bounds
			for(int i = 0; i < 4; i++)
			{
				if((block -> blocks[i].x - 1) < 0)
				{
				return 1;
				}
			}
		
			// General Case
			for(int i = 0; i < 4; i++)
			{
				if(block_array[block -> blocks[i].y][block -> blocks[i].x - 1] != 0)
				{
					return 1;
				}
			}
			
			tetris_block_render(block, 1);
			
			block -> blocks[0].x--;
			block -> blocks[1].x--;
			block -> blocks[2].x--;
			block -> blocks[3].x--;
			
			tetris_block_render(block, 0);
			
			break;
		
		case 2:
		
			//Special Case: check for out of bounds
			for(int i = 0; i < 4; i++)
			{
				if((block -> blocks[i].x + 1) >= board_length)
				{
				return 1;
				}
			}		
		
			// General Case
			for(int i = 0; i < 4; i++)
			{
				if(block_array[block -> blocks[i].y][block -> blocks[i].x + 1] != 0)
	
				{
					return 1;
				}
			}
			
			tetris_block_render(block, 1);
			
			block -> blocks[0].x++;
			block -> blocks[1].x++;
			block -> blocks[2].x++;
			block -> blocks[3].x++;
			
			tetris_block_render(block, 0);
			
			break;
	}
	
	return 0;
}

/* Attempts to rotate a tetris block in the specified direction.
 *
 * Accepts arguments:
 *			tetris_block * block - block to rotate
 *			unsigned char clockwise - 1 means CW and 0 means CCW
 *
 * Returns: whether rotation was successful or not.
 */
int tetris_block_rotate(tetris_block * block, unsigned char clockwise)
{
	int new_x1; int new_y1;
	int new_x2; int new_y2;
	int new_x3; int new_y3;
	int current_version = block -> version;
	int new_version;
	
	if(clockwise) new_version = current_version + 1;
	else new_version = current_version - 1;
	if(new_version < 0) new_version = 3;
	if(new_version > 3) new_version = 0;
	
	//Straight Block
	if(block->type == 0)
	{
		switch(current_version)
		{
					
			//Horizontal
			case 0:
						
				new_x1 = block->blocks[0].x; new_y1 = block->blocks[0].y + 1;
				new_x2 = block->blocks[0].x; new_y2 = block->blocks[0].y + 2;
				new_x3 = block->blocks[0].x; new_y3 = block->blocks[0].y - 1;
				new_version = 1;
			
			break;
					
			//Vertical
			case 1:
			
				new_x1 = block->blocks[0].x + 1; new_y1 = block->blocks[0].y;
				new_x2 = block->blocks[0].x - 1; new_y2 = block->blocks[0].y;
				new_x3 = block->blocks[0].x - 2; new_y3 = block->blocks[0].y;
				new_version = 0;
			
			break;
		}
	}
	
	//Square
	else if(block->type == 1)
	{
		//Square will always rotate upon itself.
		tetris_block_render(block, 0);
		return 1;
	}
	
	// T - Shape
	else if(block->type == 2)
	{
			switch(new_version)
			{
				case 0:
						new_x1 = block->blocks[0].x - 1; new_y1 = block->blocks[0].y;
						new_x2 = block->blocks[0].x + 1; new_y2 = block->blocks[0].y;
						new_x3 = block->blocks[0].x; new_y3 = block->blocks[0].y + 1;
					break;
				
				case 1:
						new_x1 = block->blocks[0].x; new_y1 = block->blocks[0].y + 1;
						new_x2 = block->blocks[0].x; new_y2 = block->blocks[0].y - 1;
						new_x3 = block->blocks[0].x - 1; new_y3 = block->blocks[0].y;
					break;
				
				case 2:
						new_x1 = block->blocks[0].x + 1; new_y1 = block->blocks[0].y;
						new_x2 = block->blocks[0].x - 1; new_y2 = block->blocks[0].y;
						new_x3 = block->blocks[0].x; new_y3 = block->blocks[0].y - 1;
					break;
				
				case 3:
						new_x1 = block->blocks[0].x; new_y1 = block->blocks[0].y - 1;
						new_x2 = block->blocks[0].x; new_y2 = block->blocks[0].y + 1;
						new_x3 = block->blocks[0].x + 1; new_y3 = block->blocks[0].y;
					break;
			}
	}
	
	// L - Shape (Right Handed)
	else if(block->type == 3)
	{
		switch(new_version)
		{
			case 0:
					new_x1 = block->blocks[0].x - 1; new_y1 = block->blocks[0].y;
					new_x2 = block->blocks[0].x - 2; new_y2 = block->blocks[0].y;
					new_x3 = block->blocks[0].x; new_y3 = block->blocks[0].y + 1;
				break;
			
			case 1:
					new_x1 = block->blocks[0].x; new_y1 = block->blocks[0].y + 1;
					new_x2 = block->blocks[0].x; new_y2 = block->blocks[0].y + 2;
					new_x3 = block->blocks[0].x - 1; new_y3 = block->blocks[0].y + 2;
				break;
			
			case 2:
					new_x1 = block->blocks[0].x - 1; new_y1 = block->blocks[0].y;
					new_x2 = block->blocks[0].x - 2; new_y2 = block->blocks[0].y;
					new_x3 = block->blocks[0].x - 2; new_y3 = block->blocks[0].y - 1;
				break;
				
			case 3:
					new_x1 = block->blocks[0].x; new_y1 = block->blocks[0].y + 1;
					new_x2 = block->blocks[0].x; new_y2 = block->blocks[0].y + 2;
					new_x3 = block->blocks[0].x + 1; new_y3 = block->blocks[0].y;
				break;
		}
	}
			
	// S - Shape
	else if(block->type == 4)
	{
		switch(new_version)
		{
			case 0:
					new_x1 = block->blocks[0].x + 1; new_y1 = block->blocks[0].y;
					new_x2 = block->blocks[0].x; new_y2 = block->blocks[0].y + 1;
					new_x3 = block->blocks[0].x - 1; new_y3 = block->blocks[0].y + 1;
				break;
			
			case 1:
					new_x1 = block->blocks[0].x; new_y1 = block->blocks[0].y + 1;
					new_x2 = block->blocks[0].x - 1; new_y2 = block->blocks[0].y + 1;
					new_x3 = block->blocks[0].x - 1; new_y3 = block->blocks[0].y + 2;
				break;
			
			case 2:
					new_x1 = block->blocks[0].x - 1; new_y1 = block->blocks[0].y;
					new_x2 = block->blocks[0].x; new_y2 = block->blocks[0].y + 1;
					new_x3 = block->blocks[0].x + 1; new_y3 = block->blocks[0].y + 1;
				break;
				
			case 3:
					new_x1 = block->blocks[0].x; new_y1 = block->blocks[0].y + 1;
					new_x2 = block->blocks[0].x + 1; new_y2 = block->blocks[0].y + 1;
					new_x3 = block->blocks[0].x + 1; new_y3 = block->blocks[0].y + 2;
				break;
		}
	}

	// L - Shape (Left Handed)
	else if(block->type == 5)
	{
		switch(new_version)
		{
			case 0:
					new_x1 = block->blocks[0].x - 1; new_y1 = block->blocks[0].y;
					new_x2 = block->blocks[0].x - 2; new_y2 = block->blocks[0].y;
					new_x3 = block->blocks[0].x - 2; new_y3 = block->blocks[0].y + 1;
				break;
			
			case 1:
					new_x1 = block->blocks[0].x; new_y1 = block->blocks[0].y + 1;
					new_x2 = block->blocks[0].x; new_y2 = block->blocks[0].y + 2;
					new_x3 = block->blocks[0].x - 1; new_y3 = block->blocks[0].y;
				break;
			
			case 2:
					new_x1 = block->blocks[0].x - 1; new_y1 = block->blocks[0].y;
					new_x2 = block->blocks[0].x - 2; new_y2 = block->blocks[0].y;
					new_x3 = block->blocks[0].x; new_y3 = block->blocks[0].y - 1;
				break;
				
			case 3:
					new_x1 = block->blocks[0].x; new_y1 = block->blocks[0].y + 1;
					new_x2 = block->blocks[0].x; new_y2 = block->blocks[0].y + 2;
					new_x3 = block->blocks[0].x + 1; new_y3 = block->blocks[0].y + 2;
				break;
		}
	}
	
	//Invalid Block
	else
	{
		return 0;
	}
	
	// Test if out of bounds
	if((new_y1 >= 0) && (new_y1 < board_height) && (new_x1 >= 0) && (new_x1 < board_length) &&
		 (new_y2 >= 0) && (new_y2 < board_height) && (new_x2 >= 0) && (new_x2 < board_length) &&
		 (new_y3 >= 0) && (new_y3 < board_height) && (new_x3 >= 0) && (new_x3 < board_length)
		)
	{
	
		//If any blocks in path of rotation are in use don't rotate.
		if(block_array[new_y1][new_x1] || block_array[new_y2][new_x2] || block_array[new_y3][new_x3])
		{
			return 0;
		}
	
		//Otherwise rotate and render new rotated block
		tetris_block_render(block, 1);
		block -> blocks[1].x = new_x1; block -> blocks[1].y = new_y1;
		block -> blocks[2].x = new_x2; block -> blocks[2].y = new_y2;
		block -> blocks[3].x = new_x3; block -> blocks[3].y = new_y3;
		tetris_block_render(block, 0);
		block -> version = new_version;
		return 1;
	}
	
	else
	{
		return 0;
	}
}

/* Called after a row is completed. Make all blocks above a completed row
 * fall down one space y on the grid.
 */
void block_trickle_down(int start_row)
{
	for(int curr_row = start_row; curr_row > 0; curr_row--)
	{
		for(int curr_col = 0; curr_col < board_length; curr_col++)
		{
			
			if(block_array[curr_row - 1][curr_col])
			{
				block_array[curr_row][curr_col] = block_array[curr_row - 1][curr_col];
				block_render(curr_col, curr_row, 0, block_array[curr_row - 1][curr_col]);
			}
			
			else
			{
				block_array[curr_row][curr_col] = 0;
				block_render(curr_col, curr_row, 1, 0);
			}
		}
	}
}

/* Commits a location on the board to place a tetris block.
 *
 * Accepts arguments:
 *		tetris_block * block - pointer to block desired to be moved
 */
void tetris_block_place(tetris_block * block)
{
	block_array[block->blocks[0].y][block->blocks[0].x] = block -> color;
	block_array[block->blocks[1].y][block->blocks[1].x] = block -> color;
	block_array[block->blocks[2].y][block->blocks[2].x] = block -> color;
	block_array[block->blocks[3].y][block->blocks[3].x] = block -> color;
	
}

/* Checks the whole tetris board to see if there are any 
 * Completed rows and clears it.
 *
 * Returns - score gained n*10 where n is the number of rows completed
 */
int clear_completed_rows()
{
	//check for matches
	int is_completed_row;
	int score_returnable = 0;
	for(int i = 0; i < board_height; i++)
	{
		is_completed_row = 1;
		
		// iterate through a row see if it is completed
		for(int j = 0; j < board_length; j++)
		{
			if(block_array[i][j] == 0)
			{
				is_completed_row = 0;
			}
		}
		
		// if row is complete have all blocks above "fall down" one on the grid
		if(is_completed_row)
		{
			block_trickle_down(i);
			score_returnable += 10;
		}
	}
	
	return score_returnable;
}

/* Draws the boundaries of the tetris game.
 *
 */
void draw_walls()
{
	ece210_lcd_draw_rectangle(0, board_offset_x, 0, 320, LCD_COLOR_GRAY);
	ece210_lcd_draw_rectangle(240 - board_offset_x, board_offset_x, 0, 320, LCD_COLOR_GRAY);
	ece210_lcd_draw_rectangle(board_offset_x, 240 - 2*board_offset_x, 320 - 2 * block_height, 2*block_height, LCD_COLOR_GRAY);
}

/* Converts an unsigned integer type into a char* cstring
 *
 *	Accepts argument: int i - the integer to turn into a char
 *
 *  Returns - a pointer to a dynamically allocated cstring
 *						which represents that integer
 */
char * unsigned_to_string(unsigned int i)
{
	char * reversable = malloc(15*sizeof(char));
	int remainder = i;
	int position = 0;
	while(remainder != 0 || position <= 9)
	{
		*(reversable + position) = remainder % 10 + '0';
		remainder = remainder / 10;
		++position;
	}
	
	//append null terminator
	*(reversable + position) = NULL;
	
	char * returnable = malloc((position+1) * sizeof(char));
	int returnable_pos = 0;
	
	for(int i = position - 1; i >= 0; i--)
	{
		*(returnable + returnable_pos) = *(reversable + i);
		returnable_pos++;
	}
	
	*(returnable + returnable_pos) = NULL;
	
	free(reversable);
	return returnable;
}

/* Frees up any memory used by the specified cstring
 *
 * Accepts arguments: char * string - the string to delete
 */
void delete_string(char * string)
{
	free(string);
}

/* Frees up any memory used for the given tetris board.
 */
void free_board(int ** board)
{
	for(int i = 0; i < board_height; i++)
	{
		free(*(block_array + i));
	}
	
	free(block_array);
}

/* Sends a specified amount of rows to the local players screen.
 *
 * Arguments accepted: rows_to_bombard - the number of rows to bombard the other player with
 */
void bombard_rows(int rows_to_bombard)
{
	if(rows_to_bombard == 0)
		return;
	
	for(int curr_row = 0; curr_row < (board_height - rows_to_bombard); curr_row++)
	{
		for(int curr_col = 0; curr_col < board_length; curr_col++)
		{
			
			if(block_array[curr_row + rows_to_bombard][curr_col])
			{
				block_array[curr_row][curr_col] = block_array[curr_row + rows_to_bombard][curr_col];
				block_render(curr_col, curr_row, 0, block_array[curr_row][curr_col]);
			}
			
			else
			{
				block_array[curr_row][curr_col] = 0;
				block_render(curr_col, curr_row, 1, 0);
			}
		}
	}
	
	int empty_seed;
	int random_color;
	
	for(int curr_row = board_height - 1; curr_row > board_height - 1 - rows_to_bombard; curr_row--)
	{
		empty_seed = rand() % board_length;
		
		for(int curr_col = 0; curr_col < board_length; curr_col++)
		{
			
			if(curr_col == empty_seed)
			{
				block_array[curr_row][curr_col] = 0;
				block_render(curr_col, curr_row, 1, 0);
			}
			
			else
			{
				random_color = block_render(curr_col, curr_row, 0, 0);
				block_array[curr_row][curr_col] = random_color;
				
			}
		}
	}
}
