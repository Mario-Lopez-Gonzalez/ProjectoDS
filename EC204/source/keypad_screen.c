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

extern int alien_color;
extern int cannon_x;
extern int cannon_y;
extern int ticks;
extern int num_shoots;
int shoot_laer=125;
int shoot_present=0;
t_shoot shoot_pos;
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
	 * NO FUNCIONA TOCANDO DOS O MAS TECLAS
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
		case 0xF3:
			return 10;
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
	switch(pressed_key_value())
	{

            	case 1:
			if(state==2){
                	iprintf("\x1b[18;00H 03FD Tecla <B> INTERRUPCION");
			if(shoot_present==0){
			shoot_pos.x=cannon_x;
			shoot_pos.y=cannon_y-1;
			shoot_pos.anim=1;
			shoot_present=1;}}
               		break;
		case 3:
			if(state==0){
                	iprintf("\x1b[18;00H 03F7 Tecla <START>INTERRUPCION ");
			state=1;}
			else
                	break;
		case 6:
			if(state==0){
                	iprintf("\x1b[18;00H 03CF Tecla <UP>INTERRUPCION ");
			state=12;}
                	break;
		case 7:
			if(state==0){
                	iprintf("\x1b[18;00H 037F Tecla <DOWN> INTERRUPCION ");
			state=12;}
                	break;
		case 9:
			if(state==3)
			state=1;
            	default:
                	break;
	};
} // keypad_handler()

