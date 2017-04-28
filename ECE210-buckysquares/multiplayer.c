// Name: buckysquares_menu.c
// Author: Winor Chen
// Description:	Implementation pertaining to PvP multiplayer specific
//							functions of Buckysquares.

#include "lab_buttons.h"
#include "multiplayer.h"
#include "ece210_api.h"

status_flags flags;
unsigned char local_id_wireless;
unsigned char remote_id_wireless;

/* Sends important data to another player in the form of a 32
 * bit integer. What the 32 bit flags mean (from low endian).
 * Returns 0 on failure, non-zero value on successful transmission
 *
 * bits 0-7 : the ID of the player sending (range: 1 - 255)
 * bits 8-10: the amount of rows the player is trying to send
 * bits 11-12: has the player sending lost the game? win = 1, lost = 2
 * bit 13: player is available and can connect
 * bits 14-31 UNUSED
 */
int send_status(int id, int rows_bombard, int cleared, int has_won)
{
	int flags = 8192;
	flags += (has_won << 11);
	flags += (rows_bombard << 8);
	flags += id;
	
	return ece210_wireless_send(flags);
}

/* Sends the score with the valid bit flag to the other player.
 * bit 31 - 1 means is a score value, 0 means is not
 *
 * Returns - 1 if sent, 0 if not
 */
int send_score(long score)
{
	return ece210_wireless_send(2147483648 | score);
}

/* Returns whether or not the integer sent in represents
 * a score or not.
 * bit 31 - 1 means is a score value, 0 means is not
 *
 * Returns - 1 if data is a score, 0 if not
 */
int verify_score(long score)
{
	if(2147483648 & score)
	{
		return 1; 
	}
		
	return 0;
}

/* Commits the score to be received by the board as 
 * valid.
 * bit 31 - 1 means is a score value, 0 means is not 
 *
 * Returns - the actual value of the score
 */
int receive_score(long score)
{
	return (2147483647 & score);
}

/* Initializes the wireless multiplayer board with the local player's id as well as the opponent.
 * Verifies that a connection was made with the other player.
 *
 * Returns - 0 if connection is not made, 1 if connection is made.
 */
int multiplayer_init(unsigned char local_id, unsigned char remote_id, int bombard, int sudden_death)
{
	local_id_wireless = local_id;
	remote_id_wireless = remote_id;
	ece210_wireless_init(local_id_wireless, remote_id_wireless);
	ece210_lcd_print_string("Sending test...", 220, 240, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	
	int send_success = 0;																							 
	
	while(!send_success)
	{
		send_success = send_status(local_id, 0, 0, 0);
		ece210_lcd_print_string("Waiting for other player...", 220, 240, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
		
		if(btn_left_pressed())
		{
			AlertButtons = 0;
			return 0;
		}
	}
	
	return (send_success);
}
