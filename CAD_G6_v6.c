/*
Proyecto: Proyecto_final_G6_v6
Fichero: CAD_G6_v6.c

Grupo: G6    Autores: Pablo San Jose Burgos
                      Jose Angel Castan
v1.0    Fecha: 2017-XI-15
v6.0    Last Revision: 2017-XII-10
*/
#include "CAD_G6_v0.h"

unsigned int secuenciaCAD;
unsigned int valorPotenciometro;
unsigned int valorTemperatura;
unsigned int valorJoystickX;
unsigned int valorJoystickY;

unsigned int adc1buf0[32] __attribute__((space(dma)));
unsigned int adc1buf1[32] __attribute__((space(dma)));

/* Funcion para la inicializacion de:
- AD1
- DMA2 								*/
void Inic_CAD_DMA(void){
    //ORDER MODE 
    //************************** 
    //CONFIGURAMOS EL ADC1 PARA MUESTREAR AN4,AN5, por canal CH2 
    AD1CON1 = 0;
    // 0x00E0 
    //_ADON= 0;  
    // CAD OFF 
    //_ADSIDL = 0;   
    //1=Se para en modo Idle / 0=Continua en modo Idle 
    //_AD12B = 0;     
        //1=Modo operacion de 12 bits / 0=Modo operacion de 10 bits  
    //_FORM = 0;      
        //Formato datos salida: 00=Integer (0000 00dd dddd dddd) 
                               // 01=Signed integer (ssss sssd dddd dddd) 
    _SSRC = 0b111;
    //Termina muestreo y comienca conversion del CAD 
    //111=Auto-coonvert            
    //      010=TMR3            ADC1      y      TMR5      ADC2      
    // 001=INT0 / 000= hay que borrar SAMP 
    //_SIMSAM = 0;  
    //1=Muestrea simultaneamente 
    // 0=Muestrea canales individuales sequencialmente 
    _ASAM = 1;
    //1=Muestreo comienza seguido de la conversion 
    // 0=comienza cuando SAMP=1 
    //_SAMP    
    //_DONE 
    AD1CON2 = 0; // 0x00E0 
    //_VCFG = 0;  
    //Vref+- 000=ACdd y AVss / 001=Vref+ y AVss 
    // 010=AVdd y Vref- / 011=Vref+ y Vref- 
    _CSCNA = 1;
    //1=Escaneo canal cero / 0= no escaneo 
    //_CHPS = 0;   
    //Canales utilizados:00=CH0 /01=CH0 y CH1 /1x= CH0,CH1,CH2 y CH3 
    //_BUFS   es solo de lectura: con BUFM=1-> 1=activa 2º mitad de buffer 
    // 0= activa 1ª mitad 
    //Incrementos dir DMA +1 o 
    //_SMPI = 0;   
    //Incrementos dir DMA +1 o 
    // sin DMA genera una interrupción cada cada SMPI+1 
    //_BUFM = 0;     //1= 2 medios Buffers de 8 / 0= 1 buffer de 16 
    //_ALTS = 0;  
    //Modo de muestreo: 1= Alternado / 0= Siempre canal A 
    AD1CON3 = 0;
    //_ADRC = 0;      //1= reloj RC / 0= Reloj CPU 
    _SAMC = 31;
    //Tiempo auto muestreo0 nºde Tad (de 0 a 31Tad) 
    _ADCS = 3;
    //Tad= >75ns = Tcy(ADCS+1) -> a 80MHz Tcy= 25ns 
    // Tad = (3+1)Tcy 
    AD1CON4 = 0;
    AD1CHS123 = 0;
    // reg. seleccion de entrada canal 1,2 y 3  
    //_CH123NA= 0;  
    //Selección entrada negativa     Canales 1, 2, y 3 pata Sample A  
    //0x=      CH1=CH2=CH3->      Vref-      
    // 10= CH1=AN6,CH2=AN7,CH3=AN8 
    // 11= CH1=AN9,CH2=AN10,CH3=AN11 
    //_CH123SA= 0;       //Selección entrada positiva Canales 1, 2, y 3 para Sample A 
    //1=      AN3-AN4-AN5      /      0=      AN0-AN1-AN2      
    //_CH123NB = 0; 
    //_CH123SB = 0; 
    AD1CHS0 = 0; // Seleccion de entrada canal 0 
    //_CH0NA = 0;   //Entrada negativa 1=  AN1 / 0 = Vref- 
    //_CH0SA = 5;    //Entrada positiva = canal(CH0SA) 
    _CH0SA = Potenci; 
    //_CH0SB = 3; 
    // _CH0NB = 0;
    AD1CSSH = 0x0000; //Selección entradas escaneo de la 16 a la 31 
    AD1CSSL = 0b1100110000; //Selección entradas escaneo de 0 a 15. 
    AD1PCFGH = 0xFFFF; //Configura entradas: 1= digital 
    // 0= Analog 
    AD1PCFGL = 0xFFFF;
    // AN0 
    _PCFG4 = 0;
    // AN4 -> RB4 -> Sensor Temperatura 
    _PCFG5 = 0;
    // AN5 -> RB5 -> Potenciómetro 
    _PCFG8 = 0;
    // AN8 -> RB8 -> Joystick_X 
    _PCFG9 = 0;
    // AN9 -> RB9 -> Joystick_Y 
    //IFS0 
    _AD1IF = 0;     //Flag a cero del A/D interrrupt. 
    //IEC0 
    _AD1IE = 0;     // Deshabilita la interrupcion A/D. 
    //------------------------------------------------------------------ 
    DMA2CON = 0;
    // CHEN CANAL habilitado / deshabilitado 
    DMA2CONbits.SIZE = 0; // 1=Byte / 0=Word 
    DMA2CONbits.DIR = 0; // 1=lee de RAM y escribe a periférico 
    // 0=lee de periférico y escribe en RAM 
    // HALF interrupcion a  mitad / al final 
    // NULLW Escribe nulos / operacion normal 
    
    //   DMA0REQ 
    DMA2REQbits.FORCE = 0; // 1= manual / 0= automático 
    // IRQSEL 
    // 0x00 INT0 
    // 0x01 IC1 
    // 0x02 OC1 
    // 0x05 IC2 
    // 0x06 OC2 
    // 0x07 TMR2 
    // 0x08 TMR3 
    // 0x0A SPI1 
    // 0x0B UART1RX 
    // 0x0C UART1TX 
    DMA2REQbits.IRQSEL = 0x0D; // 0x0D ADC1  //DMA_IRQ_ADC1 
    // 0x15 ADC2 
    // 0x1E UART2RX 
    //    DMA2REQbits.IRQSEL = 0x1F; // UART2TX 
    // 0x21 SPI2 
    // 0x22 ECAN1-RX 
    // 0x37 ECAN2-RX 
    // 0x46 ECAN1-TX 
    // 0x47 ECAN2-TX 
    DMA2STA = __builtin_dmaoffset(adc1buf0);
    DMA2STB = __builtin_dmaoffset(adc1buf1);
    // Inicio dir. offset 
    //DMA2STB = __builtin_dmaoffset(CAD_BuffB);     
    // Inicio dir. offset 
    //    DMA2STA = __builtin_dmaoffset(Ventana_LCD);     
    // Inicio dir. offset 
    //  DMA2STB = __builtin_dmaoffset(Ventana_LCD);     
    // Inicio dir. offset 
    DMA2PAD = (volatile unsigned int) &ADC1BUF0;
    
    
    // Bits para configuracion de DMA
    DMA2CNT = 8-1;   // Nº de trasnsferencias -1 
    DMA2CONbits.AMODE = 0b10; // 10: Direc.Indirect,Perif 
                                // 01 Indir.Reg sin Post-incr 
                                // 00 Indir.Reg con Post-Incr -->  modo normal
    DMA2CONbits.MODE = 0b10;   // 11:One PP / 10:Continuo + PP 
                            // 01: One / 00: Continuo 
    
    _ADDMABM = 0; //1=bufer DMA en orden de conversión 
                  // 0=bufer DMA en modo Scatter/Gather 
        
    _SMPI = 4-1;  //nº patas a realizar conversion-1
    
    _DMABL = 1;  //Cada buffer contiene 2^DMABL palabras  
    
    
    DMACS0 = 0;      // Borra Colisiones 
    
    //IPC6bits.DMA2IP = 4;
    IFS1bits.DMA2IF = 0;
    IEC1bits.DMA2IE = 1;  // Habilita interrupciones DMA 2 
    DMA2CONbits.CHEN = 1; // Activa canal 2 DMA 
    
    //AD1CON1bits 
    _ADON = 1;   //Habilita convertidor 
    _SAMP = 1;   //Lanza conversion
    
} // Fin Inic_CAD DMA 

/* ISR para el AD1 					*/
void _ISR_NO_PSV _ADC1Interrupt (void) {
    
    if (secuenciaCAD >3) secuenciaCAD= 0; 
    switch (secuenciaCAD) {
        
    // Lectura sensor temperatura
    case 0:

        valorTemperatura= ADC1BUF0; // Lee el valor de la conversión 
        conversionASCII(valorTemperatura);

        Ventana_CAD[8]=segundoDig;
        Ventana_CAD[9]=primerDig;

       break;
        
    // Lectura potenciometro placa
    case 1:
        valorPotenciometro= ADC1BUF0; // Lee el valor de la conversión 
        conversionASCII(valorPotenciometro);

        Ventana_CAD[28]=segundoDig;
        Ventana_CAD[29]=primerDig;

       break; 
          
    // Lectura Joystick eje X
    case 2:
        valorJoystickX= ADC1BUF0; // Lee el valor de la conversión 
        conversionASCII(valorJoystickX);

        Ventana_CAD[9+32]=segundoDig;
        Ventana_CAD[10+32]=primerDig;

        break;

    // Lectura Joystick eje Y 
    case 3:
        valorJoystickY= ADC1BUF0; // Lee el valor de la conversión 
        conversionASCII(valorJoystickY);

        Ventana_CAD[21+32]=segundoDig;
        Ventana_CAD[22+32]=primerDig;

       break;   
    }
    
    secuenciaCAD++; 
    _SAMP= 1;    		//Comienzo de conversion 
    _AD1IF = 0;     	//Flag a cero del A/D interrrupt.
    
} // FIN ADC1Interrupt

/* ISR DMA2 						*/
void _ISR_NO_PSV _DMA2Interrupt(void) {
    Nop();
    Nop();
    Nop();
    actualiza_Ventana_CAD();
    IFS1bits.DMA2IF = 0;
}

