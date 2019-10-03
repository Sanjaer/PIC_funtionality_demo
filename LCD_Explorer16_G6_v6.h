/**********************************************************************
* © 2017 LG
*
 Proyecto: Proyecto_final_G6_v6
* Fichero: LCD_Explorer16_G6_v6.h

Grupo: G6    Autores: Pablo San Jose Burgos
                      Jose Angel Castan
	Fecha: 2017-XI-15
*
*
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author Jose Angel Castan Sanchez  Date 10/12/2017
* 		 Pablo San Jose Burgos
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
*
**********************************************************************/

#include "Tiempos.h"
#include "p24HJ256GP610A.h"

extern unsigned int estado;
extern unsigned int enable;

extern unsigned int tiempos;

extern unsigned int clockType;

#define n_col_puls   36

extern unsigned char Ventana_Pulsadores[n_col_puls];

#define _ISR_NO_PSV __attribute__((interrupt, no_auto_psv))

// Pines de control LCD
#define  RW  _RD5	// LCD R/W signal
#define  RS  _RB15	// LCD RS signal
#define  E   _RD4	// LCD E signal
//#define  E   LATFbits.LATF1       // LCD E signal

#define  RW_TRIS    _TRISD5
#define  RS_TRIS    _TRISB15
#define  E_TRIS	    _TRISD4
//#define  E_TRIS   TRISFbits.TRISF1

// Pines de datos
#define  DATA      LATE	    // Port for LCD data
#define  DATAPORT  PORTE
#define  TRISDATA  TRISE    // I/O setup for data Port, solo 8 de los 16 bits

/*****	LCD COMMAND FUCNTION PROTOTYPES  *****/
#define cursor_right()  lcd_cmd( 0x14 )     // 40us
#define cursor_left()   lcd_cmd( 0x10 )     // 40us
#define display_shift() lcd_cmd( 0x1C )     // 40us
#define home_clr()      lcd_cmd( 0x01 )     // 1,64ms
#define home_it()       lcd_cmd( 0x02 )     // 1,64ms
#define line_1()        lcd_cmd( 0x80 )     // 40us, DDRAM 0x00
#define line_2()        lcd_cmd( 0xC0 )     // 40us, DDRAM 0x40

#define function_set()  lcd_cmd( 0x38)      // 40us
#define display_on()    lcd_cmd( 0x0C)      // 40us
#define entry_mode()    lcd_cmd( 0x06)      // 40us

/******	LCD FUNCTION PROTOYPES ******/

void Inic_LCD( void );		        // initialize display		
void lcd_cmd( char cmd );	        // write command to lcd
void lcd_data( char data );		    // write data to lcd
void inic_pines_LCD(void);
void inic_timer_LCD (void);
void inic_timer_ESTADOS (void);
void espera_LCD_ms( unsigned int n_miliseg );
void espera_LCD_us( unsigned int n_microseg );
void espera_LCD_ms_no_bloq(unsigned int n_miliseg);
void Init_LCD();

void refreshLCD(void);
//void Visualiza_LCD_Fila_1 (void);
//void Visualiza_LCD_Fila_2 (void);

//#define fila_1	0x02;  // 0x80
//#define fila_2	0xC0;


