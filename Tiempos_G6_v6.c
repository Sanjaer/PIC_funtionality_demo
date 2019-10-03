/*
Proyecto: Proyecto_final_G6_v6
Fichero: Tiempos_G6_v6.c

Grupo: G6    Autores: Pablo San Jose Burgos
                      Jose Angel Castan
	Fecha: 2017-X-15
    Last Revision: 2017-XII-10

Descripción:
 * Programa un Timer para que actualice una variable y/o 
 * genere una interrupción cada cierto tiempo
 * Hay que darle la frecuencia de reloj y el Nº de timer
 *
 * Entrada: Frecuencia, Timer
 * Salida: int microsegundos

 */
#include "Tiempos.h"

/* Funcion inicializacion timer 32 bits */
void Inic_Tiempo_Miliseg (){
    
/*	TMR_Timer_mili = 0;		// Borra valor del timer
    PR_Timer_mili = 4000-1;	// Define periodo. El reloj son 8MHz, 
                            // asi que el periodo es 4MHz, asi que 
                            // necesitara 4000 desbordes para cada milisegundo
	TCON_Timer_mili = 0x8000;	// Habilitado, prescaler 1:1, CK interno
//  TCON_Timer_mili = 0b1000000000000000;	// Equivalente a la linea anterior
	
// Inicializa interrupción Timer 2
    _Timer_mili_IP = 4;  // Prioridad por defecto (1 minima - 6 máxima)
    _Timer_mili_IF = 0;  // Borra flag de interrupción
    _Timer_mili_IE = 1;  // Habilita Interrupción del Timer 2
*/
    // timer 32bits
    
    TMR_Timer32L_mili = 0;    // Borra valor del timer
    TMR_Timer32M_mili = 0;    // Borra valor del timer
    
    TCON_Timer32L_mili = 0x8008;  //habilitamos timer como 32 bits con el bit 4
    
    PR_Timer32M_mili = 0x3;   // Dividimos el periodo entre ambos timers, 
    PR_Timer32L_mili = 0x0D3F; // que queremos que sea cada 200000 desborder 
                            // para conseguir 50 milisegundos
    
    //PR_Timer32M_mili = 0x1E;   // Dividimos el periodo entre ambos timers, 
    //PR_Timer32L_mili = 0x847F; // que queremos que sea cada 2000000 desborder 
                            // para conseguir 50 milisegundos a 80MHz, y a 8MHz 
                            // esperara 500 milisegundos
    
    _Timer32M_mili_IP = 4;  // Prioridad por defecto (1 minima - 6 máxima)
    _Timer32M_mili_IF = 0;  // Borra flag de interrupción
    _Timer32M_mili_IE = 1;  // Habilita Interrupción del Timer 
    
}

/* Funcion inicializacion timer para medir el rendimiento */
void inic_timer_rendimiento(void){
    TMR_Timer_RENDIMIENTO = 0;      // Borra el valor del Timer
    PR_Timer_RENDIMIENTO = 4000-1;  // Define el periodo. Para 1ms será
                                    // 0.001*4000000 = 4000
    TCON_Timer_RENDIMIENTO = 0x8000;	// Habilitado, prescaler 1:1, CK interno
    
    // Inicializar la interrupción
    _Timer_RENDIMIENTO_IP = 3;      // Prioridad media
    _Timer_RENDIMIENTO_IF = 0;      // Borrado del Flag
    _Timer_RENDIMIENTO_IE = 1;      // Habilitado de la interrupción
    
}

/* Funcion interrupcion timer de rendimiento */
void _ISR_NO_PSV _Timer_RENDIMIENTO_Interrupt(void){
    cont_ms ++;
    //En el caso de que estemos a 80MHz, habra que esperar 10 veces mas
    if (cont_ms==1*clockType){
        stop_flag = 1;
    }
    _Timer_RENDIMIENTO_IF = 0;
}








