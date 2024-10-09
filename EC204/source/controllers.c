/**********************************************************
 * controllers.c
 **********************************************************/

/* 
 * Añadir los includes que sean necesarios
 **/
#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "keypad_screen.h"
#include "timers.h"


/* 
 * Habilitar las interrupciones. En el Controlador de Interrupciones
 **/
void enable_interrupts() { 

  /* 
   * Primero se inhiben todas las interrupciones
   **/
  IME=0;


  /* 
   * Escribir un 1 en el bit correspondiente
   **/
	
	IE=IE|0x1008; //BITS 12 y 3
		

  /* 
   * Se vuelven a habilitar todas las interrupciones
   **/
	IME=1;


} // enable_interrupts()


/* 
 * Programar los registros de control. Aquí es donde se configuran los 
 * registros de control de los periféricos.
 **/
void configure_control_registers() { 

  /* 
   * Registro de Control del Teclado
   **/
  KEYS_CNT=0x42CA; // BITS 1 , 3, , 6, 7, 9 y 14 B START

  /* 
   * Registro de Control de los Temporizadores
   *   TIMER0_CNT 
   *     El temporizador se activa poniendo un 1 en el bit 7.
   *     El temporizador interrumpirá al desbordarse el contador, 
   *        si hay un 1 en el bit 6.
   *     Los dos bits de menos peso indican lo siguiente:
   *        00 frecuencia 33554432 hz 
   *        01 frecuencia 33554432/64 hz
   *        10 frecuencia 33554432/256 hz
   *        11 frecuencia 33554432/1024 hz
   *   TIMER0_DAT 
   *     Se utiliza para indicar a partir de que valor tiene que empezar 
   *        a contar (latch)
   **/

TIMER0_DAT=0xDDDE; //LATCH a 56798
TIMER0_CNT=0xC1; //BITS 7 6 y 1 , ciclo de 60 ticks/seg

} // configure_control_registers()



/* 
 * Este procedimiento inicializa el vector de interrupciones para que 
 * el gestor de interrupciones sepa que rutina de atencion tiene que 
 * ejecutar cuando le llega una peticion de interrupcion.
 **/
void define_interrupt_vector_table() { 

  /* 
   * Rutina de Atencion al Teclado
   **/
  irqSet(IRQ_KEYS,keypad_handler);

  /* 
   * Rutinas de Atencion a los Temporizadores
   **/
  irqSet(IRQ_TIMER0,timer_handler);

} // DefinirVectorInterrupciones()


/* 
 * Inhibe las interrupciones. En el Controlador de Interrupciones
 **/
void disable_interrupts() { 

  /* 
   * Primero se inhiben todas las interrupciones
   **/
  IME=0;


  /* 
   * Escribir un 0 en el bit correspondiente
   **/
  IE&=0; //Poner a 0


  /* 
   * Se vuelven a habilitar todas las interrupciones
   **/
  IME=1;
  

} // disable_interrupts()



void interrupts_setting() {

  enable_interrupts();
  configure_control_registers();
  define_interrupt_vector_table();
 
}  // interrupts_setting()



