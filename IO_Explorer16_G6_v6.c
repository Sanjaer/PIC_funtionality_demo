/*
Proyecto: Proyecto_final_G6_v6
Fichero: IO_Explorer16_G6_v6.c

Grupo: G6    Autores: Pablo San Jose Burgos
                      Jose Angel Castan
v1.0    Fecha: 2017-XI-12
v6.0    Last Revision: 2017-XII-10
*/

#include "IO_Explorer16_G6_v0.h"

unsigned int Pulsado_S3;
unsigned int Pulsado_S4;
unsigned int Pulsado_S5;
unsigned int Pulsado_S6;

unsigned int contador32Mili;

// Inicializa las patas de los leds de salida y el valor inicial
void Inic_Leds (void) {

   TRIS_LED_D3 = 0; // _TRISA0= 0;  // Led_3 -> A0,  '0' -> Salida (Output) / '1' -> Entrada (Input) 
   TRIS_LED_D4 = 0; // _TRISA1= 0;  // Led_4 -> A1
   TRIS_LED_D5 = 0; // _TRISA2= 0;  // Led_5 -> A2
   TRIS_LED_D6 = 0; // _TRISA3= 0;  // Led_6 -> A3
   TRIS_LED_D7 = 0; // _TRISA4= 0;  // Led_7 -> A4
   TRIS_LED_D8 = 0; // _TRISA5= 0;  // Led_8 -> A5
   TRIS_LED_D9 = 0; // _TRISA6= 0;  // Led_9 -> A6
   TRIS_LED_D10 = 0; // _TRISA7= 0;  // Led_10 -> A7
 
// Los leds están conectados a tierra:
// -> Un '1' en la salida del PIC lo enciende
// -> Un '0' lo Apaga
    LED_D3= 0;  // Valor de inicio LED_3 -> Apagado
    LED_D4= 0;  // Valor de inicio LED_4 -> Apagado
    LED_D5= 0;  // Valor de inicio LED_5 -> Apagado
    LED_D6= 0;  // Valor de inicio LED_6 -> Apagado
    LED_D7= 0;  // Valor de inicio LED_7 -> Apagado
    LED_D8= 0;  // Valor de inicio LED_8 -> Apagado
    LED_D9= 0;  // Valor de inicio LED_9 -> Apagado
    LED_D10= 0;  // Valor de inicio LED_10 -> Apagado

} // Fin Inic_Leds


//   PULSADORES
void Inic_Pulsadores (void){
//  TRISDbits.TRISD6 = 1;	//1= IN (entrada) 0= Out (salida)
    TRIS_PULSADOR_S3 = 1;   //1= IN (entrada) 0= Out (salida)
    TRIS_PULSADOR_S4 = 1;
    TRIS_PULSADOR_S6 = 1;
    
    Pulsado_S3 = 0; // Estado despulsado
    Pulsado_S4 = 0;
    Pulsado_S6 = 0;
    
    IE_PULSADOR_S3 = 1;     //Habilita interrupción de S3 -> RD6
    IE_PULSADOR_S4 = 1;     //Habilita interrupción de S3 -> RD13
    IE_PULSADOR_S6 = 1;     //Habilita interrupción de S3 -> RD7

    _CNIP = 2;  // Determina Prioridad, 1-> minima, 2 ..., 6, 7 -> maxima
    _CNIF = 0;	// Borra Flag de todas la CN
    _CNIE = 1;  // Habilita interrupcion general de CN

}   //FIN Inic_Pulsadores_Interrupcion

// Rutina atencion interrupciones pulsadores
void _ISR_NO_PSV _CNInterrupt (void){
    
Nop();
Nop();
    if (PULSADOR_S3 == 0){
        Pulsado_S3 = 1;
        Pulsado_S4 = 0;
        Pulsado_S6 = 0;
    }else if(PULSADOR_S4 == 0){     // No se permiten pulsaciones simultáneas para
        Pulsado_S3 = 0;             // aligerar la interrupción
        Pulsado_S4 = 1;
        Pulsado_S6 = 0;
    } else if (PULSADOR_S6  == 0){
        Pulsado_S3 = 0;
        Pulsado_S4 = 0;
        Pulsado_S6 = 1;
    }else{
        Pulsado_S3 = 0;
        Pulsado_S4 = 0;
        Pulsado_S6 = 0;
    }

    _CNIF = 0;	//Borra flag de interrupción general
} // Fin _CNInterrupt


//========================================================
// Lectura del pulsador cada 50 ms
void _ISR_NO_PSV _Timer32M_mili_Interrupt(void){
    
    contador32Mili++;
    
    if(contador32Mili>=clockType){
        int estadoD10 = _LATA7;    

        TRIS_PULSADOR_S5 = 1;  //1 = entrada

        Nop(); Nop(); Nop(); Nop(); Nop();
        Nop(); Nop(); Nop(); Nop(); Nop();
        Nop(); Nop(); Nop(); Nop(); Nop();
        Nop(); Nop(); Nop(); Nop(); Nop();

        // Actualiza el valor del mensaje para LCD y UART
        if(PULSADOR_S5 == 1){
            LED_D5 = led_apagado;
            LED_D4 = led_apagado;
            Ventana_Pulsadores[4+18] = 'F';
            Ventana_Pulsadores[5+18] = 'F';
        } else {
            LED_D5 = led_encendido;
            LED_D4 = led_encendido;
            Ventana_Pulsadores[4+18] = 'N';
            Ventana_Pulsadores[5+18] = ' ';
        }

        LED_D10 = estadoD10;

        TRIS_PULSADOR_S5 = 0;  //0 = salida
        
        contador32Mili=0;
    }
    
    _Timer32M_mili_IF = 0;	// Borra flag de interrpción
} // Fin T1Interrupt