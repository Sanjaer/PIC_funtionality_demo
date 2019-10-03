/*
Proyecto: Proyecto_final_G6_v6
Fichero: UART_G6_v6.c

Grupo: G6    Autores: Pablo San Jose Burgos
                      Jose Angel Castan
v1.0	Fecha: 2017-XI-12
v6.0	Last Revision: 2017-XII-10
*/

//======================================================================

#include "p24HJ256GP610A.h"

// timing and baud rate calculations
#define Fosc8 8000000 //Frecuencia reloj CPU
#define Fcy8 Fosc8/2
#define BAUDRATE2 19200 // baudios (bits/sg) de transmision
#define BAUD_RATE8REG_2_BRGH1 ((Fcy8/BAUDRATE2)/4)-1 // Para BRGH = 1
#define BAUD_RATE8REG_2_BRGH0 ((Fcy8/BAUDRATE2)/16)-1 // Para BRGH = 0

// timing and baud rate calculations for 80MHz
#define Fosc80 80000000 //Frecuencia reloj CPU
#define Fcy80 Fosc80/2
#define BAUD_RATE80REG_2_BRGH1 ((Fcy80/BAUDRATE2)/4)-1 // Para BRGH = 1
#define BAUD_RATE80REG_2_BRGH0 ((Fcy80/BAUDRATE2)/16)-1 // Para BRGH = 0
// Reg/bits UART2 serial port
// U2MODE no definido en P24FJ12GA010A.h
#define _STSEL_U2 U2MODEbits.STSEL
#define _PDSEL0_U2 U2MODEbits.PDSEL0
#define _PDSEL1_U2 U2MODEbits.PDSEL1
#define _BRGH_U2 U2MODEbits.BRGH
#define _RXINV_U2 U2MODEbits.RXINV
#define _ABAUD_U2 U2MODEbits.ABAUD
#define _LPBACK_U2 U2MODEbits.LPBACK
#define _WAKE_U2 U2MODEbits.WAKE
#define _UEN0_U2 U2MODEbits.UEN0
#define _UEN1_U2 U2MODEbits.UEN1
#define _RTSMD_U2 U2MODEbits.RTSMD
#define _IREN_U2 U2MODEbits.IREN
#define _USIDL_U2 U2MODEbits.USIDL
#define _UARTEN_U2 U2MODEbits.UARTEN
#define _PDSEL_U2 U2MODEbits.PDSEL
#define _UEN_U2 U2MODEbits.UEN
// U2STA
#define _URXDA_U2 U2STAbits.URXDA
#define _OERR_U2 U2STAbits.OERR
#define _FERR_U2 U2STAbits.FERR
#define _PERR_U2 U2STAbits.PERR
#define _RIDLE_U2 U2STAbits.RIDLE
#define _ADDEN_U2 U2STAbits.ADDEN
#define _URXISEL0_U2 U2STAbits.URXISEL0
#define _URXISEL1_U2 U2STAbits.URXISEL1
#define _TRMT_U2 U2STAbits.TRMT
#define _UTXBF_U2 U2STAbits.UTXBF
#define _UTXEN_U2 U2STAbits.UTXEN
#define _UTXBRK_U2 U2STAbits.UTXBRK
#define _UTXISEL0_U2 U2STAbits.UTXISEL0
#define _UTXINV_U2 U2STAbits.UTXINV
#define _UTXISEL1_U2 U2STAbits.UTXISEL1
#define _URXISEL_U2 U2STAbits.URXISEL
#define UART2_TX_TRIS TRISFbits.TRISF5
#define UART2_RX_TRIS TRISFbits.TRISF4
#define UART2_TX_LAT LATFbits.LATF5
#define UART2_RX_LAT LATFbits.LATF4
// I/O definitions
#define CR 0x0D
#define LF 0x0A
#define BACKSPACE 0x8 // ASCII backspace character code

#define _ISR_NO_PSV __attribute__((interrupt, no_auto_psv))

#define n_col_puls   36
#define n_col_CAD   64

#define lowClock 1
#define highClock 10
#define SenTemp 0b0100

//======================================================================

extern unsigned char uart2TxBuffA[n_col_CAD] __attribute__((space(dma))); 
extern unsigned char uart2TxBuffB[n_col_CAD] __attribute__((space(dma))); 

extern unsigned char Ventana_Pulsadores[n_col_puls];
extern unsigned char Ventana_CAD[n_col_CAD];

extern unsigned char valor_leido;
extern unsigned int contador_errores;
extern unsigned int contador_transmisiones;
extern unsigned int estado_comm;

extern unsigned int cambioReloj;
extern unsigned int clockType;

extern unsigned int secuenciaCAD;

//======================================================================

void inic_RS232_2_DMA(void);
void inic_DMA_RS232(void);
void inic_RS232_2( void);
void _ISR_NO_PSV _U2RXInterrupt(void);
void _ISR_NO_PSV _DMA0Interrupt(void);

