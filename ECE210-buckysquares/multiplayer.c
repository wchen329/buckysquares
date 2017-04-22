// Name: buckysquares_menu.c
// Author: Winor Chen
// Description:	Implementation pertaining to PvP multiplayer specific
//							functions of Buckysquares.

#include "multiplayer.h"
#include "ece210_api.h"

/* Sends important data to another player in the form of a 32
 * bit integer. What the 32 bit flags mean (from low endian).
 *
 * bits 0-7 : the ID of the player sending (range: 0 - 256)
 * bits 8-10: the amount of rows the player is trying to send
 * bit 11: the remote player has cleared 
 * bit 12: has the player sending lost the game? active high yes is 1
 * bit 13: player is available and can connect
 * bits 14-31 UNUSED
 */
int send_status(status_flags flags)
{
	return ece210_wireless_send(flags);
}

int send_score(long score)
{
	return ece210_wireless_send(score);
}

int set_local_id(status_flags flags, int local_id)
{
	int new_flags = (flags & -256);
	new_flags = (flags + local_id);
	return new_flags;
}

int verify_connect()
{
	
	return 0;
}
