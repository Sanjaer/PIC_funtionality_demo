/*
Proyecto: Proyecto_final_G6_v6
Fichero: UART_G6_v6.c

Grupo: G6    Autores: Pablo San Jose Burgos
                      Jose Angel Castan
v1.0    Fecha: 2017-XI-12
v6.0    Last Revision: 2017-XII-10
*/

#include "UART_G6_v0.h"


unsigned int col;           // Variable contador para recorrer los vectores de datos
unsigned char nxt_char;     // Variable para almacenar un char del vector de datos
unsigned int cont;
unsigned char uart2TxBuffA[n_col_CAD] __attribute__((space(dma)));  // Buffer A DMA de transmisión
unsigned char uart2TxBuffB[n_col_CAD] __attribute__((space(dma)));  // Buffer A DMA de transmisión

void inic_RS232_2_DMA(void){
    inic_DMA_RS232();
    inic_RS232_2();
}

void inic_DMA_RS232(void){
    
// === Configuracion DMA asociado a UART 2 ==== 
// Requiere desactivar interrupciones UART 2 
    DMA0CON = 0; 
    // CHEN CANAL habilitado / deshabilitado 
    DMA0CONbits.SIZE = 1;       // 1=Byte / 0=Word 
    DMA0CONbits.DIR = 1;        // 1= lee de DPSRAM y escribe en periférico 
                                    // 0= lee de periférico y escribe en DPSRAM 
    DMA0CONbits.HALF =0;        // 1= interrupcion a  mitad / 0= al final 
    DMA0CONbits.NULLW =0;       // 1= Escribe nulos / 0= operacion normal 
    DMA0CONbits.AMODE =0b00;    // 10: Direc.Indirect,Perif 
                                    // 01 Indir.Reg sin Post-incr 
                                    // 00 Indir.Reg con Post-Incr -->  modo normal
    DMA0CONbits.MODE = 0b11;    // 11: Un bloque + PingPong 
                                    // 10: Continuo + PingPong --> modo ping pong
                                    // 01: Un bloque 
                                    // 00: Continuo -->  modo normal
//   DMA0REQ Selecciona nº IRQ Periferico 
    DMA0REQbits.FORCE = 0; // 1= manual / 0= automático 
    // IRQSEL Selecciona nº IRQ Periferico 
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
        // 0x0D ADC1 
        // 0x15 ADC2 
        // 0x1E UART2RX 
    DMA0REQbits.IRQSEL = 0x1F; // UART2TX 
        // 0x21 SPI2 
        // 0x22 ECAN1-RX 
        // 0x37 ECAN2-RX 
        // 0x46 ECAN1-TX 
        // 0x47 ECAN2-TX 

    //Modo ping pong
    DMA0STA = __builtin_dmaoffset(uart2TxBuffA);  //0; // Inicio dir. offset 
    DMA0STB = __builtin_dmaoffset(uart2TxBuffB);  //0x0020;// Inicio dir. offset 

    //modo normal
    //DMA0STA = __builtin_dmaoffset(Ventana_DATOS);    //0;    // Inicio dir. offset 

    DMA0PAD = (volatile unsigned int)&U2TXREG;      // Dirección del periférico 
    DMA0CNT = 64-1;     // Nº de trasnsferencias -1 
    DMACS0 = 0;         // Borra flags de Colisiones 
//    INTCON1bits.DMACERR = 0;    // Borraa Flag de interrupción de colisiones 
    IFS0bits.DMA0IF = 0; 
    IEC0bits.DMA0IE = 1;        // Habilita interrupciones DMA 0 
    DMA0CONbits.CHEN = 1;   // Enable canal 0 DMA 
}

// ================ Inicializa la UART2 Serial Port ======================
void inic_RS232_2( void){
    
    // No requerido, lo hace el hardware
    // UART2_TX_TRIS = 0;
    // UART2_RX_TRIS = 1;
    // UART2_TX_LAT = 1;
    // UART2_RX_LAT = 1;
    U2MODE = 0; // 8bits, sin paridad, 1 stop, Uart parada
    // _UARTEN_U2 =; // Habilita UART
    // _USIDL_U2 =; // 0-> continua en modo Idle
    // _IREN_U2 =; // Habilita IrDA
    // _RTSMD_U2 =; // Modo pata U2RTS
    // _UEN_U2 =; // Habilita U2TX, U2RX, U2CTS y U2RTS
    // _WAKE_U2 =; // Habilita Wake-up al detectar Start en Sleep
    // _LPBACK_U2 =; // Habilita modo Loopback
    // _ABAUD_U2 =; // Habilita Auto-Baud
    // _RXINV_U2 =; // Invierte polaridad para recepción
    _BRGH_U2 = 1; // BRGH
    // _PDSEL_U2 =; // Paridad: 00= 8 bits sin paridad
    // _STSEL_U2 =; // Duración bit Stop
    U2BRG = BAUD_RATE8REG_2_BRGH1;
    // U2BRG = 8; // Aplicando la formula da 7 y no va bien
    U2STA = 0;
    // _UTXISEL_U2 =; // Tipo Interrupción Transmisión
    // _UTXINV_U2 =; // Invierte polaridad pata transmisión
    // _UTXBRK_U2 =; // Bit Breal
    // _UTXEN_U2 =; // Habilita Transmisión
    // _UTXBF_U2 =; // Estado Buffer transmisión (solo lectura)
    // _TRMT_U2 =; // Estado Reg.Desplazamiento (solo lectura)
    // _URXISEL_U2 =; // Tipo interrupción en recepción
    // 0x= interrupción con cada dato que llega
    // 10= interrupción a 3/4 del buffer
    // 11= interrupción cuando buffer lleno
    // _ADDEN_U2 =; // Detección bit de dirección en 9 bits
    // _RIDLE_U2 =; // Estado de la recepción (solo lectura)
    // _PERR_U2 =; // Error de paridad /solo lectura)
    // _FERR_U2 =; // Error de trama (solo lectura)
    // _OERR_U2 =; // Error ocerrun (borrable/ solo lectura)
    // _URXDA_U2 =; // 0=buffer vacío, 1= al menos un dato
    _U2RXIF = 0; // Borra flag int. RX
    _U2TXIF = 0; // Borra flag int. TX
    _U2EIF = 0; // Borra flag de Error UART
    _U2TXIE = 0; // Deshabilita int. de transmisión
    U2RXREG = 0;
    _U2RXIE = 1; // Habilita la int. de recepción
    _U2EIE = 1; // Habilita Int_ de Error UART
    _OERR_U2=0; // Según versión corrige bug
    _UARTEN_U2 = 1; // Habilita la UART_2
    _UTXEN_U2 = 1; //Habilita transmisión,
    //Debe activarse después de habilitar UART
    // Inicializamos a cero los contadores de las interrupciones
    contador_errores = 0;
    contador_transmisiones = 0;
    col = 0;    //    de la matriz de datos Ventana_DATOS
} // Fin Inicialización UART 2


// === Atención Interrupcione DMA =================== 
//void __attribute__((__interrupt__)) _DMA0Interrupt(void) 
void _ISR_NO_PSV _DMA0Interrupt(void) { 
    Nop(); 
    Nop(); 
    Nop();
    /*if (cont == 0){
        DMA0REQbits.FORCE = 1;          // Manual mode: Kick-start the 1st transfer
        ++cont;
    } else{
        DMA0CONbits.CHEN = 0;
        cont = 0;
    }*/
    IFS0bits.DMA0IF = 0; 
} 


// ================ Servicio INTERRUPCION TRANSMISION RS232_2 ==============
// Trasmite un dato, si hay, al final de transmisión del anterior
void _ISR_NO_PSV _U2TXInterrupt(void){
    
    if (col < n_col_puls){          // Transm. primer array0
        nxt_char = Ventana_Pulsadores[col];
        ++col;
    } else if (col < n_col_CAD+n_col_puls){    // Salto al siguiente array
        nxt_char = Ventana_CAD[col-n_col_puls];
        ++col;
    } else{                         // Vuelta al inicio
        col = 0;
        nxt_char = Ventana_Pulsadores[col];
        ++col;
    }
    
    U2TXREG = nxt_char;             // Envía datos correspondientes
    _U2TXIF = 0;
} // FIN _U2RXInterrupt


// Recibe un dato por la interrupción de la UART
void _ISR_NO_PSV _U2RXInterrupt(void){
    contador_transmisiones++;
    valor_leido = U2RXREG;
    if (valor_leido == 's'){            // ADC por Scatter-gatther
        _ADDMABM = 0;
    } else if(valor_leido == 'n'){      // ADC por modo continuo
        _ADDMABM = 1;
    }else if(valor_leido == 'l'){       // Bajar el reloj a 8MHz
        //8MHz
    }else if(valor_leido == 'h'){       // Subir el reloj a 80MHz
        cambioReloj=1;
        
    } else if(valor_leido == 'r'){      // Actualizar la lista de resultados y transmitir 
        estado_comm = 1;                // Flag para actualizar los valores en el main)()
        DMA0CONbits.CHEN = 1;           // Habilita el canal de comunicación
        DMA0REQbits.FORCE = 1;          // Manual mode: Kick-start the 1st transfer
        
    } else if(valor_leido == 'i'){      // Transmitir UART por interrupción
        IFS0bits.DMA0IF = 0;            // Borra el flag de la interrupción DMA0
        IEC0bits.DMA0IE = 0;            // Deshabilita interrupciones DMA0 
        DMA0CONbits.CHEN = 0;           // Enable canal 0 DMA0
        _U2TXIF = 0;                    // Borra flag de Error UART
        _U2TXIE = 1;                    // Habilita int. de transmisión
        col = 0;                        
        
    }else if (valor_leido == 'd'){      // Transmitir UART por DMA
        _U2TXIF = 0;                    // Borra flag de Error UART
        _U2TXIE = 0;                    // Deshabilita int. de transmisión
        col = 0;
        IFS0bits.DMA0IF = 0;            // Borra el flag de la interrupción DMA 
        IEC0bits.DMA0IE = 1;            // Habilita interrupciones DMA0 
        DMA0CONbits.CHEN = 1;           // Enable canal 0 DMA
        
    } else if(valor_leido == 'm'){      // ADC en modo interrupción
        IFS1bits.DMA2IF = 0;
        IEC1bits.DMA2IE = 0;            // Deshabilita interrupciones DMA 2 
        DMA2CONbits.CHEN = 0;           // Desactiva canal 2 DMA 
        secuenciaCAD=0;
        _AD1IF = 0;                     //Flag a cero del A/D interrrupt. 
        _AD1IE = 1;                     // Habilita la interrupcion A/D.
        
    } else if(valor_leido == 'a'){      // ADC por DMA
        _AD1IF = 0;
        _AD1IE = 0;                     // Deshabilita la interrupcion A/D. 
        IFS1bits.DMA2IF = 0;
        _CH0SA = SenTemp;
        IEC1bits.DMA2IE = 1;            // Habilita interrupciones DMA 2 
        DMA2CONbits.CHEN = 1;           // Activa canal 2 DMA 
    } else if(valor_leido == 'p'){      // PingPong, forzar 1 bit 1  
        DMA0CONbits.MODE |= 0b10;
    } else if(valor_leido == 'o'){      // No PingPong forzar 0 bit 1
        DMA0CONbits.MODE &= 0b01; 
    } else if(valor_leido == 'c'){      // Continuo forzar 0 bit 0
        DMA0CONbits.MODE &= 0b10;
    } else if(valor_leido == 'b'){      // Un bloque forzar 1 bit 0
        DMA0CONbits.MODE |= 0b01;
    } else{
        //Error
    }
    valor_leido = '-';
    _U2RXIF = 0;
} // FIN _U2RXInterrupt

// Interrupcion de error de la UART
void _ISR_NO_PSV _U2ErrInterrupt (void){
    contador_errores++;
    Nop();
    Nop();
    _U2EIF = 0;
}
