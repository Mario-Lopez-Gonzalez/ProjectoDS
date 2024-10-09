/**********************************************************
 * keypad_screen.c
 **********************************************************/

/* 
 * Añadir los includes que sean necesarios
 **/
#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "sprites.h"

/* 
 * Esta función consulta si se ha tocado la pantalla táctil
 **/
int is_the_screen_touched() {
touchPosition screen_pos;
	touchRead(&screen_pos);
  	return !(screen_pos.px==0 && screen_pos.py==0);
} // is_the_screen_touched()


/*
 * Custom code to read touchscreen horizontal (x) position
 **/
int screen_pos_x()
{
touchPosition screen_pos;
	touchRead(&screen_pos);
  	return screen_pos.px;
}

/*
 * Custom code to read touchscreen vertical (y) position
 **/
int screen_pos_y()
{
touchPosition screen_pos;
	touchRead(&screen_pos);
  	return screen_pos.py;
}
/* 
 * Esta función tiene que devolver el valor de la tecla pulsada
 **/
int pressed_key_value() {
    /* 
 	 * Devuelve el valor asociado a la tecla pulsada:
 	 * A=0;    B=1;  SELECT=2; START=3; RIGHT=4; 
 	 * LEFT=5; UP=6; DOWN=7;   R=8;     L=9
 	 * -1 en otros casos
 	 **/
	switch(KEYS_DAT)
	{
		case 0x03FE:
                	return 0;
                	break;
            	case 0x03FD:
                	return 1;
                	break;
		case 0x03FB:
                	return 2;
                	break;
		case 0x03F7:
                	return 3;
                	break;
		case 0x03EF:
                	return 4;
                	break;
		case 0x03DF:
                	return 5;
                	break;
		case 0x03BF:
                	return 6;
                	break;
		case 0x037F:
                	return 7;
                	break;
		case 0x02FF:
                	return 8;
                	break;
		case 0x01FF:
                	return 9;
                	break;
            	default:
			return -1;
                	break;
	};
       
} // pressed_key_value()


/* 
 * Rutina de atención a la interrupción del teclado
 **/
void keypad_handler() {

	// De momento no hay nada
	
} // keypad_handler()

