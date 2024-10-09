#ifndef _keypad
#define _keypad
/**********************************************************
 * keypad_screen.h
 **********************************************************/

int is_the_screen_touched();

int pressed_key_value();

int screen_pos_x();
int screen_pos_y();

void keypad_handler();

#endif
