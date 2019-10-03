/**********************************************************************
* © 2013 LG
*
* Proyecto: Proyecto_final_G6_v6
* Fichero: LCD_Explorer16_24H_v2.C

Grupo: G6    Autores: Pablo San Jose Burgos
                      Jose Angel Castan
	Fecha: 2017-X-15
 *
* Dependencies:    none
* Processor:       PIC24H
* Compiler:        
*
*
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author            Date      Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Luis   2014-X-15  LCD 2x16 Explorer 16
* Pablo/Angel 2017-XII-10 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES: Modificacioes a partir de lcd.c y 24H_LCD_Int.c
*
**********************************************************************/

#include "LCD_Explorer16_G6_v0.h"

unsigned int tiempos;
unsigned int estado;
unsigned int enable;

/* Patas utilizadas por el LCD en la Explorer 16
   RS -> R--
   E  -> R--
   RW -> R--
   DATA -> RE-- - RE--   
*/

/*****	LCD  *****/
//========= Envio de COMANDO =========
// Es bloqueante, espera a que termine el tiempor de TMR4 lo reprograma y
// al salir recupera la configuracion anterior de TMR4 y la interrupcion
void lcd_cmd( char cmd ){          // subrutina para comandos

    RW = 0; // Selecciona Escritura 
    RS = 0; // 0= Selecciona Registro (direccion) de comando 
    DATA &= 0xFF00; // Prepara los 8 bits del dato (RE7-RE0) 
    DATA |= cmd; // Copia comando en los 8 bits de menos peso de PORT E 
    // Entre el cambio en RS y/o RW y E= 1, hay que espera tas >60ns 
    E = 1;   // Inicio de operación, "E=1" debe permanecer un tiempo mímimo 
    Nop();  // Tiempo de espera para respetar el parámetro-> PWeh > 230ns 
    Nop();
    Nop(); 
    Nop(); 
    Nop();
    
    E = 0;  // Fin de operación 
    RW = 1; // Desactiva escritura por seguridad por si se producen glitches 
}

//======= Envio de DATO ===============
void lcd_data( char data ){        // subroutine for lcd data

    RW = 0;       				 // ensure RW is 0
    RS = 1;                       // assert register select to 1
    DATA &= 0xFF00;               // prepare RD0 - RD7
    DATA |= data;                 // data byte to lcd
    E = 1;
    
    Nop();
    Nop(); 
    Nop(); 
    Nop();
    Nop();
   
    E = 0;                       // toggle E signal
    RW = 1;
    //    RS = 0;                      // negate register select to 0
}

// Genera sa secuencia de comandos de inicialización del LCD display
void Init_LCD(void){ 
    
    inic_timer_LCD();
    inic_pines_LCD();
    espera_LCD_ms(15*clockType);
    function_set();
    espera_LCD_ms(5*clockType);
    function_set();
    espera_LCD_ms(5*clockType);
    function_set();
    espera_LCD_ms(5*clockType);
    display_on();
    espera_LCD_ms(5*clockType);
    entry_mode();
    espera_LCD_ms(5*clockType);
    
Nop();
Nop();  
} //FIN Init_LCD

//================================================
// Inicialización del timer de la LCD para las esperas 
//     bloqueantes de la inicialización
void inic_timer_LCD (void){
    
    TMR_Timer_LCD = 0;		// Borra valor del timer
    PR_Timer_LCD = 0xFF;	// Define periodo. El reloj son 8MHz
	TCON_Timer_LCD = 0;	// Deshabilitado, prescaler 1:1, CK interno
	
    // Inicializa interrupción 
    _Timer_LCD_IP = 4;  // Prioridad por defecto (1 minima - 6 máxima)
    _Timer_LCD_IF = 0;  // Borra flag de interrupción
    _Timer_LCD_IE = 1;  // Habilita Interrupción 
}

// Inicialización del timer de la LCD para la máquina de estados
//     para refrescar la pantalla de la LCD
void inic_timer_ESTADOS (void){
    
    TMR_Timer_ESTADOS = 0;		// Borra valor del timer
    PR_Timer_ESTADOS = 60000-1;	// Define periodo. El reloj son 8MHz, asi que
                                // necesita 60000 desbordes para 150 milisegundos,
                                // y cuando el reloj sea 80MHz seran 15 segundos
	TCON_Timer_ESTADOS = 0x8000;	// Habilitado, prescaler 1:1, CK interno
	
    // Inicializa interrupción 
    _Timer_ESTADOS_IP = 3;  // Prioridad por defecto (1 minima - 6 máxima)
    _Timer_ESTADOS_IF = 0;  // Borra flag de interrupción
    _Timer_ESTADOS_IE = 1;  // Habilita Interrupción
}

// Inicialización de los pines de control de la LCD
void inic_pines_LCD(){
    //1= IN (entrada) 0= Out (salida)
    RW_TRIS=0;  // Read/write
    RS_TRIS=0;  // Register select
    E_TRIS=0;   // Enable
    
    TRISE &= 0xFF00; // RE7-RE0 deben ser de salida (pines de datos)
}


// Espera a que pasen n milisegundos (bloqueante). Inicialización LCD.
void espera_LCD_ms( unsigned int n_miliseg ){
    
	TCON_Timer_LCD = 0x8000;	// Habilitado, prescaler 1:1, CK interno
    PR_Timer_LCD = 4000-1;	// Define periodo. El reloj son 8MHz, asi que 
                            // necesitara 4000 desbordes para cada milisegundo
    
    tiempos=0;
    
    //multiplicamos por el tipo de reloj
    while(tiempos<(n_miliseg*clockType));
    
	TCON_Timer_LCD = 0;	// Deshabilitado, prescaler 1:1, CK interno
    
Nop();
Nop();
}

// Espera a que pasen n microsegundos (bloqueante). Inicialización LCD.
void espera_LCD_us( unsigned int n_microseg ){
    
	TCON_Timer_LCD = 0x8000;	// Habilitado, prescaler 1:1, CK interno
    PR_Timer_LCD = 4-1;         // Define periodo. El reloj son 8MHz, asi que 
                                // necesitara 4 desbordes para cada microsegundo
    
    tiempos=0;
    
    while(tiempos<n_microseg);
    
	TCON_Timer_LCD = 0;	// Deshabilitado, prescaler 1:1, CK interno
    
Nop();
Nop();

}
// Espera a que pasen n milisegundos no bloqueante. Inicialización LCD.
void espera_LCD_ms_no_bloq( unsigned int n_miliseg ){
    
	TCON_Timer_LCD = 0x8000;	// Habilitado, prescaler 1:1, CK interno
    PR_Timer_LCD = 4000-1;	// Define periodo. El reloj son 8MHz, asi que 
                            // necesitara 4000 desbordes para cada milisegundo
    
    tiempos=0;
    
	TCON_Timer_LCD = 0;	// Deshabilitado, prescaler 1:1, CK interno
    
Nop();
Nop();
}

// Cuenta miliseguntos y microsegundos
void _ISR_NO_PSV _Timer_LCD_Interrupt( void){
    
    tiempos++;
    
    _Timer_LCD_IF = 0;	// Borra flag de interrpción
}


void _ISR_NO_PSV _Timer_ESTADOS_Interrupt( void){
    
    enable=1; // Habilita el refresh de la LCD en el MAIN
    
    // Avanza el estado [0:33]
    if(estado<34){
        estado++;
    }
    else{
        estado=0;
    }
    

    _Timer_ESTADOS_IF = 0;	// Borra flag de interrpción
    
}

// Máquina de estados para la escritura en la LCD
void refreshLCD(void){
    
    if (estado == 0){ // Saltamos a la linea 1
        line_1();
    } else if(estado < 17){ // Escribe la primera linea
        lcd_data(Ventana_Pulsadores[estado-1]); // estado [1:16]
    } else if (estado == 17){ // Saltamos a la linea 2
        line_2();
    } else{                 // Escribe al segunda linea
        lcd_data(Ventana_Pulsadores[estado]); // estado [18:33]
    }
    
}


