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

#include "backgrounds.h"
#include "controllers.h"
#include "defines.h"
#include "keypad_screen.h"
#include "sprites.h"
#include "timers.h"

/* 
 * Variables globales
 **/

int state;

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
     * Mostrar fondos en pantalla.
     **/
    display_back01();

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

    while(1) {
	
	//set_main_palette();
	//set_secondary_palette();
	//alloc_sprites_in_memory();
	//display_play_button_release(int 126, int 90, int 10);
    	switch(pressed_key_value())
	{
		case 0:
                	iprintf("\x1b[18;00H  03FE Tecla <A>     ");
                	break;
            	case 1:
                	iprintf("\x1b[18;00H  03FD Tecla <B>     ");
                	break;
		case 2:
                	iprintf("\x1b[18;00H  03FB Tecla <SELECT>");
                	break;
		case 3:
                	iprintf("\x1b[18;00H  03F7 Tecla <START> ");
                	break;
		case 4:
                	iprintf("\x1b[18;00H  03EF Tecla <RIGHT> ");
                	break;
		case 5:
                	iprintf("\x1b[18;00H  03DF Tecla <LEFT>  ");
                	break;
		case 6:
                	iprintf("\x1b[18;00H  03BF Tecla <UP>    ");
                	break;
		case 7:
                	iprintf("\x1b[18;00H  037F Tecla <DOWN>  ");
                	break;
		case 8:
                	iprintf("\x1b[18;00H  02FF Tecla <R>     ");
                	break;
		case 9:
                	iprintf("\x1b[18;00H  02FF Tecla <L>     ");
                	break;
            	default:
			iprintf("\x1b[18;00H                     ");
                	break;
	};

			iprintf("\x1b[16;00H Touchscreen x= %d   ",screen_pos_x());
			iprintf("\x1b[17;00H Touchscreen y= %d   ",screen_pos_y());
    } // while

} // main()
