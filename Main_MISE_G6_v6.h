/*
Proyecto: Proyecto_final_G6_v6
Fichero: Main_MISE_G6_v0.h

Grupo: G6    Autores: Pablo San Jose Burgos
                      Jose Angel Castan
v1.0	Fecha: 2017-XI-12
v6.0	Last Revision: 2017-XII-10
*/
  
#include "p24HJ256GP610A.h"
#include "CAD_G6_v0.h"
#include "IO_Explorer16_G6_v0.h"
#include "Tiempos.h"
#include "LCD_Explorer16_G6_v0.h"
#include "UART_G6_v0.h"

#define _ISR_NO_PSV __attribute__((interrupt, no_auto_psv))

#define n_col_puls  36
#define n_col_CAD   64
#define n_col_cons  100

#define cicloRendimientoms 1

extern unsigned char Ventana_Resultado[14];

extern unsigned char Ventana_Pulsadores[n_col_puls];
extern unsigned char Ventana_CAD[n_col_CAD];
extern unsigned char Ventana_Consola[n_col_cons];

const unsigned char Texto_Pulsadores[]=  {"S3:OX     S4:OX \n\r"  // 20 caracteres Fila 1 
                                          "S5:OX     S6:OX \n\r"}; // 20 caracteres Fila 2

const unsigned char Texto_CAD[]=  {"Temp: 0xXX  Built-in Pot: 0xXX\n\r"  // 34 caracteres Fila 1 
                                   "X-Axis:0xXX Y-Axis:0xXX       \n\r"}; // 34 caracteres Fila 2 

unsigned char valor_leido;

unsigned int contador_errores;

unsigned int contador_transmisiones;

extern unsigned int primerDig, segundoDig;

extern unsigned int adc1buf0[32] __attribute__((space(dma))); 

extern unsigned short stop_flag;

extern unsigned short cont_ms;

extern unsigned int cambioReloj;
extern unsigned int clockType;
#define lowClock 1
#define highClock 10
extern void Inic_Oscilador (void);
extern void espera_LCD_ms( unsigned int n_miliseg );
void cambiarFrequencia(void);

extern unsigned int contador32Mili;
//==============================================================================

void Copia_FLASH_RAM();
void check_pulsadores();
void refreshLCD (void);

void Copia_RAM_DMA_A(const unsigned char *texto);
void Copia_RAM_DMA_B(const unsigned char *texto);
void actualiza_Ventana_CAD(void);
void conversionASCII (unsigned int convertir);
void limpia_DMA_A_B(void);
