// Name: buckysquares_menu.c
// Author: Winor Chen
// Description:	Library pertaining to PvP multiplayer specific
//							functions of Buckysquares.

#include <stdint.h>

typedef long status_flags;
extern unsigned char local_id_wireless;
extern unsigned char remote_id_wireless;

/* Sends important data to another player in the form of a 32
 * bit integer. What the 32 bit flags mean (from low endian).
 *
 * bits 0-7 : the ID of the player sending (range: 0 - 255)
 * bits 8-10: the amount of rows the player is trying to send
 * bits 11-12: has the player sending lost the game? win = 1, lost = 2
 * bit 13: player is available and can connect
 * bits 14-31 UNUSED
 */
int send_status(int ID, int rows_bombard, int cleared, int has_won);

/* Sends the score with the valid bit flag to the other player.
 * bit 31 - 1 means is a score value, 0 means is not
 *
 * Returns - 1 if sent, 0 if not
 */
int send_score(long score);

/* Returns whether or not the integer sent in represents
 * a score or not.
 * bit 31 - 1 means is a score value, 0 means is not
 *
 * Returns - 1 if data is a score, 0 if not
 */
int verify_score(long score);

/* Commits the score to be received by the board as 
 * valid.
 * bit 31 - 1 means is a score value, 0 means is not 
 *
 * Returns - the actual value of the score
 */
int receive_score(long score);

/* Initializes the wireless multiplayer board with the local player's id as well as the opponent.
 * Verifies that a connection was made with the other player.
 *
 * Returns - 0 if connection is not made, 1 if connection is made.
 */
int multiplayer_init(unsigned char local_id, unsigned char remote_id, int bombard, int sudden_death);
