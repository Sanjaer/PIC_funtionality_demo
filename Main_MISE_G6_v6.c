/*
Proyecto: Proyecto_final_G6_v6
Fichero: Main_MISE_G6_v6.c

Grupo: G6    Autores: Pablo San Jose Burgos
                      Jose Angel Castan
	Fecha: 2017-X-15
    Last Revision: 2017-XII-10
v0: 
Descripción:
 * Usa EXPLORER16 con PIC24HJ256GP610A
 * Ejemplo de manejo de leds 
 * Ejemplo de manejo pulsado con interrupción
 * 
 * ENTRADAS:
 *  Pulsdores ...
 * 
 * SALIDAS
 *  Leds ...
 */

#include "Main_MISE_G6_v0.h"

unsigned char Ventana_Resultado[14];

unsigned char Ventana_Pulsadores[n_col_puls];
unsigned char Ventana_CAD[n_col_CAD];
unsigned char Ventana_Consola[n_col_cons];

unsigned int primerDig, segundoDig;

unsigned int ADCValue;
unsigned int estado_comm;

unsigned int instrucciones_espera;
unsigned short stop_flag;
unsigned short cont_ms;
unsigned short check_perf;

unsigned int clockType;
unsigned int cambioReloj;

//==============================================================================
int main (void){
    
Nop();
Nop();

    // Inicializaciones 
    AD1PCFGL= 0xFFFF;   // Pone todas las patas analógicas de I/O digital
    AD1PCFGH= 0xFFFF;   // Por defecto las patas analógicas están habilitadas
    
Nop();
Nop();
    cambioReloj=0;
    clockType=lowClock;
    
    contador32Mili=0;
    
    Inic_Tiempo_Miliseg ();
    
    Inic_Leds ();
    Inic_Pulsadores ();
    Init_LCD ();
    
Nop();
Nop();

    // Copiamos los datos a mostrar en pantalla
    Copia_FLASH_RAM();
    limpia_DMA_A_B();

Nop();
Nop();

    //Iniciamos la maquinadeestados
    estado=0;
    inic_timer_ESTADOS();
    
Nop();
Nop();

    inic_RS232_2_DMA();
    Inic_CAD_DMA();
    
Nop();
Nop(); 
    
    // Rendimiento del bucle principal
    inic_timer_rendimiento();
    //Mostrar por la UART
    Ventana_Resultado[0]= 'E';
    Ventana_Resultado[1]= 'x';
    Ventana_Resultado[2]= 't';
    Ventana_Resultado[3]= 'r';
    Ventana_Resultado[4]= 'a';
    Ventana_Resultado[5]= ':';
    Ventana_Resultado[6]= ' ';
    Ventana_Resultado[7]= ' ';
    // Worst-case scenario
    //enable = 1;
    //estado_comm = 1;

    int tablanum =0;
    
Nop();
Nop();
    
    // Bucle Principal
    while(1){
        
        // Rendimiento del bucle principal
        stop_flag = 0;
        cont_ms = 0;
        
        if(cambioReloj){
            cambiarFrequencia();
        }
        
        if(enable){
            refreshLCD();
            enable = 0;
            Nop(); 
        }
        
        check_pulsadores();
        
        if (estado_comm == 1){
            //Imprime_resultados
            actualiza_Ventana_CAD();
            Copia_RAM_DMA_A(Ventana_Pulsadores);
            Copia_RAM_DMA_B(Ventana_CAD);
            estado_comm = 0;
        }
        
    
        instrucciones_espera = 0;
        while(stop_flag == 0){
            instrucciones_espera++;
        }
        
        //Mostrar por la UART
        Ventana_Resultado[8]= ((instrucciones_espera/1000)%10)+48;
        Ventana_Resultado[9]=((instrucciones_espera/100)%10)+48;
        Ventana_Resultado[10]=((instrucciones_espera/10)%10)+48;
        Ventana_Resultado[11]=(instrucciones_espera%10)+48;
        Ventana_Resultado[12]='\n';
        Ventana_Resultado[13]='\r';
        //Copia_RAM_DMA_A(Ventana_Resultado);
        tablanum++;
        if(tablanum>10000){
            Nop();
        }
Nop();
Nop();
	} // Fin while(1)

} //Fin main



// Check por encuesta de la pulsación de S3, S4 y S6
void check_pulsadores(){
    
    if (Pulsado_S3 == 1){
        LED_D10 = led_encendido;
        LED_D9 = led_encendido;
        LED_D8 = led_encendido;
        Ventana_Pulsadores[4] = 'N';
        Ventana_Pulsadores[5] = ' ';
    } else if (Pulsado_S3 == 0){
        LED_D10 = led_apagado;
        LED_D9 = led_apagado;
        LED_D8 = led_apagado;
        Ventana_Pulsadores[4] = 'F';
        Ventana_Pulsadores[5] = 'F';
    }
Nop();
Nop();

    if (Pulsado_S6 == 1){
        LED_D7 = led_encendido;
        LED_D6 = led_encendido;
        Ventana_Pulsadores[14+18] = 'N';
        Ventana_Pulsadores[15+18] = ' ';
    } else if (Pulsado_S6 == 0){
        LED_D7 = led_apagado;
        LED_D6 = led_apagado;
        Ventana_Pulsadores[14+18] = 'F';
        Ventana_Pulsadores[15+18] = 'F';
    }
  
Nop();
Nop();

    if (Pulsado_S4 == 1){
        LED_D3 = led_encendido;
        Ventana_Pulsadores[14] = 'N';
        Ventana_Pulsadores[15] = ' ';
    } else if (Pulsado_S4 == 0){
        LED_D3 = led_apagado;
        Ventana_Pulsadores[14] = 'F';
        Ventana_Pulsadores[15] = 'F';
    }

Nop();
Nop();

}

// Pasa un texto de FLASH a RAM
void Copia_FLASH_RAM() {
    
    int j;
    const unsigned char *pointer = Texto_Pulsadores;
  
    for (j = 0; j < n_col_puls; j++) {
        Ventana_Pulsadores[j]=*pointer;
        pointer+=1;
    }
    pointer = Texto_CAD;
    for (j = 0; j < n_col_CAD; j++) {
        Ventana_CAD[j]=*pointer;
        pointer+=1;
    }
}  // FIN Copia_FLASH_RAM

// Función que pasa el contenido de un vector
//   al buffer de salida A de la UART 2
void Copia_RAM_DMA_A(const unsigned char *texto) {
    int j;
    for (j = 0; j < n_col_puls; j++) {
        uart2TxBuffA[j]=*texto;
        texto+=1;
    }
}


// Función que pasa el contenido de un vector
//   al buffer de salida B de la UART 2
void Copia_RAM_DMA_B(const unsigned char *texto) {
    
    int j;
    for (j = 0; j < n_col_CAD; j++) {
        uart2TxBuffB[j]=*texto;
        texto+=1;
    }
} 

// Función que vacía el contenido
//   del buffer de salida A y B de la UART 2
void limpia_DMA_A_B(void) {
    int j;
    for (j = 0; j < n_col_puls; j++) {
        uart2TxBuffA[j]='\0';
    }
    for (j = 0; j < n_col_CAD; j++) {
        uart2TxBuffB[j]='\0';
    }
}

// Funcion para actualizar los valores de los
//  datos a mandar por la UART
void actualiza_Ventana_CAD(){
    
    if(_ADDMABM){
        conversionASCII(adc1buf0[0]);
        Ventana_CAD[8]=segundoDig;
        Ventana_CAD[9]=primerDig;
        
        conversionASCII(adc1buf0[1]);
        Ventana_CAD[28]=segundoDig;
        Ventana_CAD[29]=primerDig;

        conversionASCII(adc1buf0[2]);
        Ventana_CAD[9+32]=segundoDig;
        Ventana_CAD[10+32]=primerDig;

        conversionASCII(adc1buf0[3]);
        Ventana_CAD[21+32]=segundoDig;
        Ventana_CAD[22+32]=primerDig;
   } else{
       conversionASCII(adc1buf0[8]);
       Ventana_CAD[8]=segundoDig;
       Ventana_CAD[9]=primerDig;
       
       conversionASCII(adc1buf0[10]);
       Ventana_CAD[28]=segundoDig;
       Ventana_CAD[29]=primerDig;
               
       conversionASCII(adc1buf0[16]);
       Ventana_CAD[9+32]=segundoDig;
       Ventana_CAD[10+32]=primerDig;
               
       conversionASCII(adc1buf0[18]);
       Ventana_CAD[21+32]=segundoDig;
       Ventana_CAD[22+32]=primerDig;
   }
}

// Funcion para convertir un valor hexadecimal 
//      a su representacion en caracteres ASCII
//      que muestren su valor 0x00 - 0xFF
void conversionASCII(unsigned int convertir) {
    convertir = convertir >> 2;
    primerDig = convertir & 0xF; // Mascara para quedarnos con el primer digito
    if (primerDig < 10) {       
        primerDig += 48;      // 48 decimal = '0' ASCII
    } else {
        primerDig = (primerDig - 10) + 65;  // 65 decimal = 'A' ASCII
    }
    
    segundoDig = (convertir >> 4)&0xF; // Mascara para el segundo digito
    if (segundoDig < 10) {
        segundoDig += 48;
    } else {
        segundoDig = (segundoDig - 10) + 65;
    }
    
}

// Funcion para el cambio de frecuencia del reloj
//  de 8MHz a 80MHz de manera controlada
void cambiarFrequencia(void){
    unsigned char tempD = IEC0bits.DMA0IE;
    unsigned char tempI = _U2TXIE;
    IEC0bits.DMA0IE = 0;            // Deshabilitamos interrupciones DMA
    _U2TXIE = 0;                    // Deshabilita int. de transmisión
    U2BRG = BAUD_RATE80REG_2_BRGH1; // Ajustamos frecuencia de UART
    clockType=highClock;            // Cambiamos la configuracion de los timers
    espera_LCD_ms(10);               // esperamos a que se ajusten 
                                    // las configuraciones antes de cambiar el oscilador
    Inic_Oscilador();               // Cambiamos el reloj a 80 MHz
    IEC0bits.DMA0IE = tempD;            // Habilitamos interrupciones DMA
    _U2TXIE = tempI;                    // Habilita int. de transmisión
    cambioReloj=0;
}
