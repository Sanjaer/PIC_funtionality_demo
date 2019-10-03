/*
Proyecto: Proyecto_final_G6_v6
Fichero: CAD_G6_v6.c

Grupo: G6    Autores: Pablo San Jose Burgos
                      Jose Angel Castan
v1.0	Fecha: 2017-XI-15
v6.0	Last Revision: 2017-XII-10
*/


#include "p24HJ256GP610A.h"

#define _ISR_NO_PSV __attribute__((interrupt, no_auto_psv))

// Direcciones registros perifericos
#define SenTemp 0b0100
#define Potenci 0b0101
#define JysticX 0b1000
#define JysticY 0b1001

#define n_col_CAD   64
#define n_col_puls   36

extern unsigned int secuenciaCAD; // Contador para saltar entre perifericos

extern unsigned char Ventana_Pulsadores[n_col_puls];
extern unsigned char Ventana_CAD[n_col_CAD];

extern unsigned int adc1buf0[32] __attribute__((space(dma)));
extern unsigned int adc1buf1[32] __attribute__((space(dma)));

// Definicion funciones
void Inic_CAD_DMA (void);
void Inic_CAD (void);
void Inic_DMA_CAD(void);
void _ISR_NO_PSV _ADC1Interrupt (void);
void _ISR_NO_PSV _DMA0Interrupt(void);
extern void actualiza_Ventana_CAD();
extern void conversionASCII(unsigned int convertir);

// Variables externas
extern unsigned int primerDig, segundoDig;
