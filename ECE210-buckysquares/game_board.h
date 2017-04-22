// Name: gameboard.h
// Author: Winor Chen
// Description:	Library for functions pertaining to the representation
//							of the tetris game board.

extern int block_height;		// height of single tetris block in pixels
extern int block_length;		// length of single tetris block in pixels
extern int block_start_x;		// the starting x position of a tetris block
extern int board_height;		// the height of the board in BLOCKS not pixels
extern int board_length;		// the length of the board in BLOCKS not pixels
extern int board_offset_x;	// x offset used for centering of the tetris board

/* unit_block Struct
 * Represents a single unit block with an x and y coord
 */ 
typedef struct
{
	int x;
	int y;
} unit_block;

/* tetris_block Struct
 * Represents a tetris block which is simply a combinations of four
 * unit blocks.
 */
typedef struct
{
	unit_block blocks[4];
	unsigned char type;
	unsigned char version;
	int color;
} tetris_block;

/* Renders a single unit block on position(x,y) the screen.
 *
 * Accepts arguments:
 *	int x - the x co-ordinate of the block to write
 *	int y - the y co-ordinate of the block to write
 *	int erase - flag 1 write black (or erase the block from the LCD) or 0 write a block of random color 
 *	int block_color - the color of the block to render. 0x0 is a random color unless erase is asserted then black is the color
 */
int block_render(int x, int y, int erase, int block_color);

/* Initializes the tetris board to be empty
 * (all zero values).
 *
 * Accepts arguments:
 *	int board_size - a flag indicating how big the tetris board should be
 */
int ** init_board(int board_size);

/* Renders a given tetris block on the screen.
 * Renders the block in a random ROYGBV color.
 *
 * Accepts arguments:
 *	tetris_block * block - pointer to block desired to write.
 *	int erase - flag 1 write black (or erase the block from the LCD) or 0 write a block of random color
 *
 * Returns - the color the tetris block was rendered in
 */
int tetris_block_render(tetris_block * block, int erase);

/* Generates a new tetris block based off of a
 * base point by modifying "block" which is passed in
 * through struct pointer
 */
void tetris_block_generate(tetris_block * block, int xpos, int ypos);

/* Attempts to move the block in the indicated direction. If there is a collision
 * with pre-existing blocks or the wall, do not move the blocks
 *
 * Accepts arguments:
 *		tetris_block * block - pointer to block desired to be moved
 * 		char direction - 0 down, 1 left, 2 right
 *
 * Returns: integer flag 0 if move successful 1 if collision occurred no move 
 */
int tetris_block_move(tetris_block * block, unsigned char direction);

/* Attempts to rotate a tetris block in the specified direction.
 *
 * Accepts arguments:
 *			tetris_block * block - block to rotate
 *			unsigned char direction - 1 means CW and 0 means CCW
 *
 * Returns: whether rotation was successful or not.
 */
int tetris_block_rotate(tetris_block * block, unsigned char clockwise);

/* Commits a location on the board to place a tetris block.
 *
 * Accepts arguments:
 *		tetris_block * block - pointer to block desired to be moved
 */
void tetris_block_place(tetris_block * block);

/* Checks the whole tetris board to see if there are any 
 * Completed rows and clears it.
 *
 * Returns - score gained n*10 where n is the number of rows completed
 */
int clear_completed_rows(void);

/* Draws the boundaries of the tetris game.
 *
 */
void draw_walls(void);


/* Converts an unsigned integer type into a char* cstring
 *
 *	Accepts argument: int i - the integer to turn into a char
 *
 *  Returns - a pointer to a dynamically allocated cstring
 *						which represents that integer
 */
char * unsigned_to_string(unsigned int i);
	
/* Frees up any memory used by the specified cstring
 *
 * Accepts arguments: char * string - the string to delete
 */
void delete_string(char * string);

/* Frees up any memory used for the given tetris board.
 */
void free_board(int ** board);

/* Sends a specified amount of rows to the local players screen.
 *
 * Arguments accepted: rows_to_bombard - the number of rows to bombard the other player with
 */
void bombard_rows(int rows_to_bombard);
