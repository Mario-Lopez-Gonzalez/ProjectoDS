#ifndef _defines
#define _defines
/**********************************************************
 * defines.h
 **********************************************************/

#include <nds.h>
#include <stdio.h>

/* 
 * Aquí se definen los registros del gestor de interrupciones
 **/
#define IME		(*(vuint16*)0x04000208) //Interrupt Master Enable - Habilita o deshabilita todas las interrupciones
#define IE		(*(vuint32*)0x04000210) //Interrupt Enable - Activa o desactiva las interrupciones una a una
#define IF		(*(vuint32*)0x04000214) //Interrupt Flag - Guarda las peticiones de interrupcion

/* 
 * Aquí se definen algunas funciones para el tratamiento de las interrupciones
 **/
#define enable_ints() 	IME=1 //Habilita todas las interrupciones
#define disable_ints() 	IME=0 //Inhibe todas las interrupciones

/* 
 * Aquí se definen los registros del teclado
 **/
#define KEYS_DAT	(*(vuint16*)0x4000130) //Registro de datos del teclado
#define KEYS_CNT	(*(vuint16*)0x4000132) //Registro de control del teclado

/* 
 * Aquí se definen los registros del temporizador
 **/
#define TIMER0_CNT  (*(vuint16*)0x04000102) //Registro de control del temporizador
    /* 
     * El temporizador se activa poniendo un 1 en el bit 7.
     * El temporizador interrumpirá al desbordarse el contador, si hay un 1 en el bit 6.
     * Los dos bits de menos peso indican lo siguiente:
     *		00 frecuencia 33554432 hz 
     *		01 frecuencia 33554432/64 hz
     *		10 frecuencia 33554432/256 hz
     *		11 frecuencia 33554432/1024 hz
     **/
#define TIMER0_DAT  (*(vuint16*)0x04000100) //Registro de datos del temporizador
    /* 
     * Se utiliza para indicar a partir de qué valor tiene que empezar a contar
     **/

/* 
 * Asignar un identificador a cada tecla
 **/
#define A		0 
#define B		1
#define SELECT	2 
#define START	3
#define RIGHT	4 
#define LEFT	5
#define UP		6 
#define DOWN	7
#define R		8 
#define L		9
#define crabs 30

/* 
 * Asignar un identificador a cada estado
 **/
#define BEGIN	0


/* 
 * Variables globales
 **/

extern int state;

typedef struct t_crab {
int hits;
int sprite;//1 is crab, 2 is squid, 3 is octo
int x;
int y;
int anim; // 0 muerto
} t_crab;

typedef struct t_shoot {
int x;
int y;
int anim;
} t_shoot;

#endif
