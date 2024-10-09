/********************************************************** 
 * main.c
 *
 * Este codigo se ha implementado basandose en el ejemplo 
 * "Simple sprite demo" de dovoto y otro de Jaeden Amero
 **********************************************************/

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>	    // srand, rand,...
#include <unistd.h>
#include <time.h>       // time 
#include <maxmod9.h>    // Maxmod definitions for ARM9
#include "soundbank.h"  // Soundbank definitions

#include "backgrounds.h"
#include "controllers.h"
#include "defines.h"
#include "keypad_screen.h"
#include "sprites.h"
#include "timers.h"

/* 
 * Variables globales
 **/

int state=0;
int timer;
int ticks=0;
t_crab crab_pos[crabs]={0};
int cannon_x;
int cannon_y=179;
int fresh;
int crabs_alive;
int iterator=0;
extern t_shoot shoot_pos;
extern int dif;
extern int score;
int once=20;
/* 
 * main()
 **/
int main() {
    /* 
 	 * Poner en marcha el motor grafico 2D.
 	 **/
    powerOn(POWER_ALL_2D); // <nds.h>

    /* 
     * Establecer la pantalla inferior como principal, inicializar 
     * el sistema grafico y configurar el sistema de fondos. 
     **/
    lcdMainOnBottom(); // <nds.h>
    init_video();
    init_background();

    /* 
 	 * Inicializar memoria de sprites y guardar en ella los sprites.
 	 **/
    init_sprite_memory();
    alloc_sprites_in_memory();

    /* 
 	 * Establecer las paletas para los sprites.
 	 **/
    set_main_palette();
    set_secondary_palette();

    /* Inicializa la consola (superior) de texto. 
     * Nota.- Para borrar la pantalla existe la funcion consoleClear() 
     **/
    consoleDemoInit(); // <nds.h>

    /* 
     * Para inicializar el generador de numeros aleatorios en funcion de una semilla,
	 * en este caso time(NULL). srand() solo se suele activar una vez por ejecucion y
	 * no devuelve ningun valor. 
	 * La funcion para generar valores aleatorios en el resto del programa es rand() 
	 **/
    srand(time(NULL));

    /* 
     * Incluimos la siguiente cabecera para que cada grupo la modifique con
     * su numero de grupo "xxx" en "ECxxx". 
     **/
//  iprintf("\x1b[00;00H.123456789.123456789.123456789.1");
    iprintf("\x1b[00;00H  +--------------------------+  ");
    iprintf("\x1b[01;00H  : EC 20/21      EC204      :  ");
    iprintf("\x1b[02;00H  +--------------------------+  ");

    iprintf("\x1b[04;00H  +--------------------------+  ");
    iprintf("\x1b[05;00H  : Lopez, Mario             :  ");
    iprintf("\x1b[06;00H  : Morate, Joseba           :  ");
    iprintf("\x1b[07;00H  : Romero, I*aki            :  ");
    iprintf("\x1b[08;00H  +--------------------------+  ");
    interrupts_setting();
while(1){
	switch(state){
case 0:
	iprintf("\x1b[12;00H PRESS START TO PLAY THE GAME! ");
	break;
case 1:
    iprintf("\x1b[12;00H SCORE: 0                          ");
    display_back02();
    cannon_x=126;
    display_laser_cannon(cannon_x,cannon_y);
    int i=0;
    int found=false;
    while(i<crabs)
    {
     int x=((rand()%12)+2)*16;//72 espacios
     int y=(rand()%6)*16;
     int a=0;
     for(a;a<i;a++)
     {
	if(x-15<=crab_pos[a].x&&crab_pos[a].x<=x+15&&y-15<=crab_pos[a].y&&crab_pos[a].y<=y+15)
	 found=true;
     }
     if(!found)
     {
      crab_pos[i].hits=0;
      crab_pos[i].sprite=1;
      crab_pos[i].x=x;
      crab_pos[i].y=y;
      crab_pos[i].anim=1;
      display_crab_alien(i,x,y);
      i++;
     }
    found=false;
    }
    timer=0;
    state=2;
    fresh=1;
    crabs_alive=crabs;
    break;
case 2:
    	switch(pressed_key_value())
	{
		case 0:
			if(ticks%3==0&&fresh)
			{
                	iprintf("\x1b[18;00H 03FE Tecla <A> ENCUESTA        ");
			fresh=false;
			}
                	break;
		case 2:
			if(ticks%3==0&&fresh)
			{
                	iprintf("\x1b[18;00H 03FB Tecla <SELECT> ENCUESTA   ");
			fresh=false;
			state=3;//forzar gameover
			}
                	break;
		case 4:
			if(ticks%3==0&&fresh)
			{
                	iprintf("\x1b[18;00H 03EF Tecla <RIGHT> ENCUESTA    ");
			fresh=false;
			move_ship_left();
			}
                	break;
		case 5:
			if(ticks%3==0&&fresh)
			{
			iprintf("\x1b[18;00H 03DF Tecla <LEFT> ENCUESTA    ");
			fresh=false;
			move_ship_right();
			}
			break;
            	default:
			if(ticks%3==0&&fresh)
			{
			iprintf("\x1b[19;00H TIMER: %d                 ",timer);
			fresh=false;
			}
                	break;
	};
	if(ticks%3==1)
	fresh=1;
	break;
case 3:
	remove_laser_cannon(cannon_x,cannon_y);
	for(iterator=0;iterator<crabs;iterator++)
	{
	if(crab_pos[iterator].anim==1)
	remove_crab_alien(iterator,crab_pos[iterator].x,crab_pos[iterator].y);
	else
	remove_crab_alien_2(iterator,crab_pos[iterator].x,crab_pos[iterator].y);
	}
	if(shoot_pos.anim==1)
	remove_projectile(125,shoot_pos.x,shoot_pos.y);
	else
	if(shoot_pos.anim==2)
	remove_projectile_2(125,shoot_pos.x,shoot_pos.y);
	if(once){
	iprintf("\x1b[10;00H PRESS L TO PLAY AGAIN           ");
	once--;}
	dif=0;
	score=0;
	break;
case 12:
break;
default:
	iprintf("\x1b[19;00H state error handler, main");
	break;
    }
}
} // main()

void move_ship_right(){
if(cannon_x>0)
{
remove_laser_cannon(cannon_x,cannon_y);
cannon_x-=4;
display_laser_cannon(cannon_x,cannon_y);
}
}

void move_ship_left(){
if(cannon_x<240)
{
remove_laser_cannon(cannon_x,cannon_y);
cannon_x+=4;
display_laser_cannon(cannon_x,cannon_y);
}
}
