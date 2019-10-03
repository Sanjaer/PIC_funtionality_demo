/*
Proyecto: Proyecto_final_G6_v6
Fichero: IO_Explorer16_G6_v6.h

Grupo: G6    Autores: Pablo San Jose Burgos
                      Jose Angel Castan
v1.0	Fecha: 2017-XI-12
v6.0	Last Revision: 2017-XII-10
*/

// Los leds están conectados a tierra ->
// -> Un '1' en la salida del PIC lo enciende
// -> Un '0' lo Apaga

#include "Tiempos.h"
#include "p24HJ256GP610A.h"

//==============================================================================
#define _ISR_NO_PSV __attribute__((interrupt, no_auto_psv))

#define LED_D3           _LATA0  // LATAbits.LATA0
#define LED_D4           _LATA1
#define LED_D5           _LATA2
#define LED_D6           _LATA3
#define LED_D7           _LATA4
#define LED_D8           _LATA5
#define LED_D9           _LATA6
#define LED_D10          _LATA7

#define TRIS_LED_D3     _TRISA0 // TRISAbits.TRISA0
#define TRIS_LED_D4     _TRISA1
#define TRIS_LED_D5     _TRISA2
#define TRIS_LED_D6     _TRISA3
#define TRIS_LED_D7     _TRISA4
#define TRIS_LED_D8     _TRISA5
#define TRIS_LED_D9     _TRISA6
#define TRIS_LED_D10    _TRISA7 // Coincide con un botón

#define led_encendido   1
#define led_apagado     0


#define PULSADOR_S3         _RD6    // PORTD6bits.PORTD6
#define PULSADOR_S4         _RD13
#define PULSADOR_S5         _RA7    // Coincide con un LED
#define PULSADOR_S6         _RD7

#define TRIS_PULSADOR_S3    _TRISD6 // CN15
#define TRIS_PULSADOR_S4    _TRISD13 // CN19
#define TRIS_PULSADOR_S5    _TRISA7 // Coincide con un LED
#define TRIS_PULSADOR_S6    _TRISD7 // CN16

#define IE_PULSADOR_S3      _CN15IE
#define IE_PULSADOR_S4      _CN19IE
#define IE_PULSADOR_S6      _CN16IE

#define n_col_puls   36

extern unsigned char Ventana_Pulsadores[n_col_puls];

//==============================================================================
extern unsigned int Pulsado_S3;
extern unsigned int Pulsado_S4;
extern unsigned int Pulsado_S5;
extern unsigned int Pulsado_S6;

extern unsigned int contador32Mili;

//==============================================================================
void Inic_Leds (void);
void Inic_Pulsadores(void);
void _ISR_NO_PSV _CNInterrupt(void);
void _ISR_NO_PSV _Timer32M_mili_Interrupt(void);

extern void espera_LCD_ms( unsigned int n_miliseg );

