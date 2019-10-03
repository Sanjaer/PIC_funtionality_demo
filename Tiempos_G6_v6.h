/*
Proyecto: Proyecto_final_G6_v6
Fichero: Tiempor_G6_v6.h

Grupo: G6    Autores: Pablo San Jose Burgos
                      Jose Angel Castan
v1.0	Fecha: 2017-XI-15
v6.0	Last Revision: 2017-XII-10
*/

#include "p24HJ256GP610A.h"

#define Timer_mili 8 // Define el nº Timer a usar

#if (Timer_mili == 1)
#define TMR_Timer_mili  TMR1
#define PR_Timer_mili   PR1
#define TCON_Timer_mili T1CON

 #define _Timer_mili_Interrupt _T1Interrupt
 #define _Timer_mili_IF _T1IF
 #define _Timer_mili_IP _T1IP
 #define _Timer_mili_IE _T1IE

#elif(Timer_mili==2)
#define TMR_Timer_mili  TMR2
#define PR_Timer_mili   PR2
#define TCON_Timer_mili T2CON

 #define _Timer_mili_Interrupt _T2Interrupt
 #define _Timer_mili_IF _T2IF
 #define _Timer_mili_IP _T2IP
 #define _Timer_mili_IE _T2IE

#elif (Timer_mili == 3)
#define TMR_Timer_mili  TMR3
#define PR_Timer_mili   PR3
#define TCON_Timer_mili T3CON

 #define _Timer_mili_Interrupt _T3Interrupt
 #define _Timer_mili_IF _T3IF
 #define _Timer_mili_IP _T3IP
 #define _Timer_mili_IE _T3IE

 #elif (Timer_mili == 4)
#define TMR_Timer_mili  TMR4
#define PR_Timer_mili   PR4
#define TCON_Timer_mili T4CON

 #define _Timer_mili_Interrupt _T4Interrupt
 #define _Timer_mili_IF _T4IF
 #define _Timer_mili_IP _T4IP
 #define _Timer_mili_IE _T4IE

#elif (Timer_mili == 5)
#define TMR_Timer_mili  TMR5
#define PR_Timer_mili   PR5
#define TCON_Timer_mili T5CON

 #define _Timer_mili_Interrupt _T5Interrupt
 #define _Timer_mili_IF _T5IF
 #define _Timer_mili_IP _T5IP
 #define _Timer_mili_IE _T5IE

#elif (Timer_mili == 6)
#define TMR_Timer_mili  TMR6
#define PR_Timer_mili   PR6
#define TCON_Timer_mili T6CON

 #define _Timer_mili_Interrupt _T6Interrupt
 #define _Timer_mili_IF _T6IF
 #define _Timer_mili_IP _T6IP
 #define _Timer_mili_IE _T6IE

#elif (Timer_mili == 7)
#define TMR_Timer_mili  TMR7
#define PR_Timer_mili   PR7
#define TCON_Timer_mili T7CON

 #define _Timer_mili_Interrupt _T7Interrupt
 #define _Timer_mili_IF _T7IF
 #define _Timer_mili_IP _T7IP
 #define _Timer_mili_IE _T7IE

#elif(Timer_mili==8)
 #define TMR_Timer_mili  TMR8
#define PR_Timer_mili   PR8
#define TCON_Timer_mili T8CON

 #define _Timer_mili_Interrupt _T8Interrupt
 #define _Timer_mili_IF _T8IF
 #define _Timer_mili_IP _T8IP
 #define _Timer_mili_IE _T8IE

#elif (Timer_mili == 9)
#define TMR_Timer_mili  TMR9
#define PR_Timer_mili   PR9
#define TCON_Timer_mili T9CON

 #define _Timer_mili_Interrupt _T9Interrupt
 #define _Timer_mili_IF _T9IF
 #define _Timer_mili_IP _T9IP
 #define _Timer_mili_IE _T9IE

#elif(Timer_mili==0||Timer_mili>=9)
#error ("Timer_mili NO DEFINIDO")
#endif


// Usamos timer2+3 para un timer de 32 bits

#define TMR_Timer32L_mili  TMR2
#define PR_Timer32L_mili   PR2
#define TCON_Timer32L_mili T2CON

 #define _Timer32L_mili_Interrupt _T2Interrupt
 #define _Timer32L_mili_IF _T2IF
 #define _Timer32L_mili_IP _T2IP
 #define _Timer32L_mili_IE _T2IE

#define TMR_Timer32M_mili  TMR3
#define PR_Timer32M_mili   PR3
#define TCON_Timer32M_mili T3CON

 #define _Timer32M_mili_Interrupt _T3Interrupt
 #define _Timer32M_mili_IF _T3IF
 #define _Timer32M_mili_IP _T3IP
 #define _Timer32M_mili_IE _T3IE

#define Timer_LCD 7 // Define el nº Timer a usar

#if (Timer_LCD == 1)
#define TMR_Timer_LCD  TMR1
#define PR_Timer_LCD   PR1
#define TCON_Timer_LCD T1CON

 #define _Timer_LCD_Interrupt _T1Interrupt
 #define _Timer_LCD_IF _T1IF
 #define _Timer_LCD_IP _T1IP
 #define _Timer_LCD_IE _T1IE

#elif(Timer_LCD==2)
#define TMR_Timer_LCD  TMR2
#define PR_Timer_LCD   PR2
#define TCON_Timer_LCD T2CON

 #define _Timer_LCD_Interrupt _T2Interrupt
 #define _Timer_LCD_IF _T2IF
 #define _Timer_LCD_IP _T2IP
 #define _Timer_LCD_IE _T2IE

#elif (Timer_LCD == 3)
#define TMR_Timer_LCD  TMR3
#define PR_Timer_LCD   PR3
#define TCON_Timer_LCD T3CON

 #define _Timer_LCD_Interrupt _T3Interrupt
 #define _Timer_LCD_IF _T3IF
 #define _Timer_LCD_IP _T3IP
 #define _Timer_LCD_IE _T3IE

 #elif (Timer_LCD == 4)
#define TMR_Timer_LCD  TMR4
#define PR_Timer_LCD   PR4
#define TCON_Timer_LCD T4CON

 #define _Timer_LCD_Interrupt _T4Interrupt
 #define _Timer_LCD_IF _T4IF
 #define _Timer_LCD_IP _T4IP
 #define _Timer_LCD_IE _T4IE

#elif (Timer_LCD == 5)
#define TMR_Timer_LCD  TMR5
#define PR_Timer_LCD   PR5
#define TCON_Timer_LCD T5CON

 #define _Timer_LCD_Interrupt _T5Interrupt
 #define _Timer_LCD_IF _T5IF
 #define _Timer_LCD_IP _T5IP
 #define _Timer_LCD_IE _T5IE

#elif (Timer_LCD == 6)
#define TMR_Timer_LCD  TMR6
#define PR_Timer_LCD   PR6
#define TCON_Timer_LCD T6CON

 #define _Timer_LCD_Interrupt _T6Interrupt
 #define _Timer_LCD_IF _T6IF
 #define _Timer_LCD_IP _T6IP
 #define _Timer_LCD_IE _T6IE

#elif (Timer_LCD == 7)
#define TMR_Timer_LCD  TMR7
#define PR_Timer_LCD   PR7
#define TCON_Timer_LCD T7CON

 #define _Timer_LCD_Interrupt _T7Interrupt
 #define _Timer_LCD_IF _T7IF
 #define _Timer_LCD_IP _T7IP
 #define _Timer_LCD_IE _T7IE

#elif(Timer_LCD==8)
 #define TMR_Timer_LCD  TMR8
#define PR_Timer_LCD   PR8
#define TCON_Timer_LCD T8CON

 #define _Timer_LCD_Interrupt _T8Interrupt
 #define _Timer_LCD_IF _T8IF
 #define _Timer_LCD_IP _T8IP
 #define _Timer_LCD_IE _T8IE

#elif (Timer_LCD == 9)
#define TMR_Timer_LCD  TMR9
#define PR_Timer_LCD   PR9
#define TCON_Timer_LCD T9CON

 #define _Timer_LCD_Interrupt _T9Interrupt
 #define _Timer_LCD_IF _T9IF
 #define _Timer_LCD_IP _T9IP
 #define _Timer_LCD_IE _T9IE

#elif(Timer_LCD==0||Timer_LCD>=9)
#error ("Timer_LCD NO DEFINIDO")
#endif

#define Timer_RENDIMIENTO 4 // Define el nº Timer a usar

#if (Timer_RENDIMIENTO == 1)
#define TMR_Timer_RENDIMIENTO  TMR1
#define PR_Timer_RENDIMIENTO   PR1
#define TCON_Timer_RENDIMIENTO T1CON

 #define _Timer_RENDIMIENTO_Interrupt _T1Interrupt
 #define _Timer_RENDIMIENTO_IF _T1IF
 #define _Timer_RENDIMIENTO_IP _T1IP
 #define _Timer_RENDIMIENTO_IE _T1IE

#elif(Timer_RENDIMIENTO==2)
#define TMR_Timer_RENDIMIENTO  TMR2
#define PR_Timer_RENDIMIENTO   PR2
#define TCON_Timer_RENDIMIENTO T2CON

 #define _Timer_RENDIMIENTO_Interrupt _T2Interrupt
 #define _Timer_RENDIMIENTO_IF _T2IF
 #define _Timer_RENDIMIENTO_IP _T2IP
 #define _Timer_RENDIMIENTO_IE _T2IE

#elif (Timer_RENDIMIENTO == 3)
#define TMR_Timer_RENDIMIENTO  TMR3
#define PR_Timer_RENDIMIENTO   PR3
#define TCON_Timer_RENDIMIENTO T3CON

 #define _Timer_RENDIMIENTO_Interrupt _T3Interrupt
 #define _Timer_RENDIMIENTO_IF _T3IF
 #define _Timer_RENDIMIENTO_IP _T3IP
 #define _Timer_RENDIMIENTO_IE _T3IE

 #elif (Timer_RENDIMIENTO == 4)
#define TMR_Timer_RENDIMIENTO  TMR4
#define PR_Timer_RENDIMIENTO   PR4
#define TCON_Timer_RENDIMIENTO T4CON

 #define _Timer_RENDIMIENTO_Interrupt _T4Interrupt
 #define _Timer_RENDIMIENTO_IF _T4IF
 #define _Timer_RENDIMIENTO_IP _T4IP
 #define _Timer_RENDIMIENTO_IE _T4IE

#elif (Timer_RENDIMIENTO == 5)
#define TMR_Timer_RENDIMIENTO  TMR5
#define PR_Timer_RENDIMIENTO   PR5
#define TCON_Timer_RENDIMIENTO T5CON

 #define _Timer_RENDIMIENTO_Interrupt _T5Interrupt
 #define _Timer_RENDIMIENTO_IF _T5IF
 #define _Timer_RENDIMIENTO_IP _T5IP
 #define _Timer_RENDIMIENTO_IE _T5IE

#elif (Timer_RENDIMIENTO == 6)
#define TMR_Timer_RENDIMIENTO  TMR6
#define PR_Timer_RENDIMIENTO   PR6
#define TCON_Timer_RENDIMIENTO T6CON

 #define _Timer_RENDIMIENTO_Interrupt _T6Interrupt
 #define _Timer_RENDIMIENTO_IF _T6IF
 #define _Timer_RENDIMIENTO_IP _T6IP
 #define _Timer_RENDIMIENTO_IE _T6IE

#elif (Timer_RENDIMIENTO == 7)
#define TMR_Timer_RENDIMIENTO  TMR7
#define PR_Timer_RENDIMIENTO   PR7
#define TCON_Timer_RENDIMIENTO T7CON

 #define _Timer_RENDIMIENTO_Interrupt _T7Interrupt
 #define _Timer_RENDIMIENTO_IF _T7IF
 #define _Timer_RENDIMIENTO_IP _T7IP
 #define _Timer_RENDIMIENTO_IE _T7IE

#elif(Timer_RENDIMIENTO==8)
 #define TMR_Timer_RENDIMIENTO  TMR8
#define PR_Timer_RENDIMIENTO   PR8
#define TCON_Timer_RENDIMIENTO T8CON

 #define _Timer_RENDIMIENTO_Interrupt _T8Interrupt
 #define _Timer_RENDIMIENTO_IF _T8IF
 #define _Timer_RENDIMIENTO_IP _T8IP
 #define _Timer_RENDIMIENTO_IE _T8IE

#elif (Timer_RENDIMIENTO == 9)
#define TMR_Timer_RENDIMIENTO  TMR9
#define PR_Timer_RENDIMIENTO   PR9
#define TCON_Timer_RENDIMIENTO T9CON

 #define _Timer_RENDIMIENTO_Interrupt _T9Interrupt
 #define _Timer_RENDIMIENTO_IF _T9IF
 #define _Timer_RENDIMIENTO_IP _T9IP
 #define _Timer_RENDIMIENTO_IE _T9IE

#elif(Timer_RENDIMIENTO==0||Timer_RENDIMIENTO>=9)
#error ("Timer_RENDIMIENTO NO DEFINIDO")
#endif

#define Timer_ESTADOS 6 // Define el nº Timer a usar

#if (Timer_ESTADOS == 1)
#define TMR_Timer_ESTADOS  TMR1
#define PR_Timer_ESTADOS   PR1
#define TCON_Timer_ESTADOS T1CON

 #define _Timer_ESTADOS_Interrupt _T1Interrupt
 #define _Timer_ESTADOS_IF _T1IF
 #define _Timer_ESTADOS_IP _T1IP
 #define _Timer_ESTADOS_IE _T1IE

#elif(Timer_ESTADOS==2)
#define TMR_Timer_ESTADOS  TMR2
#define PR_Timer_ESTADOS   PR2
#define TCON_Timer_ESTADOS T2CON

 #define _Timer_ESTADOS_Interrupt _T2Interrupt
 #define _Timer_ESTADOS_IF _T2IF
 #define _Timer_ESTADOS_IP _T2IP
 #define _Timer_ESTADOS_IE _T2IE

#elif (Timer_ESTADOS == 3)
#define TMR_Timer_ESTADOS  TMR3
#define PR_Timer_ESTADOS   PR3
#define TCON_Timer_ESTADOS T3CON

 #define _Timer_ESTADOS_Interrupt _T3Interrupt
 #define _Timer_ESTADOS_IF _T3IF
 #define _Timer_ESTADOS_IP _T3IP
 #define _Timer_ESTADOS_IE _T3IE

 #elif (Timer_ESTADOS == 4)
#define TMR_Timer_ESTADOS  TMR4
#define PR_Timer_ESTADOS   PR4
#define TCON_Timer_ESTADOS T4CON

 #define _Timer_ESTADOS_Interrupt _T4Interrupt
 #define _Timer_ESTADOS_IF _T4IF
 #define _Timer_ESTADOS_IP _T4IP
 #define _Timer_ESTADOS_IE _T4IE

#elif (Timer_ESTADOS == 5)
#define TMR_Timer_ESTADOS  TMR5
#define PR_Timer_ESTADOS   PR5
#define TCON_Timer_ESTADOS T5CON

 #define _Timer_ESTADOS_Interrupt _T5Interrupt
 #define _Timer_ESTADOS_IF _T5IF
 #define _Timer_ESTADOS_IP _T5IP
 #define _Timer_ESTADOS_IE _T5IE

#elif (Timer_ESTADOS == 6)
#define TMR_Timer_ESTADOS  TMR6
#define PR_Timer_ESTADOS   PR6
#define TCON_Timer_ESTADOS T6CON

 #define _Timer_ESTADOS_Interrupt _T6Interrupt
 #define _Timer_ESTADOS_IF _T6IF
 #define _Timer_ESTADOS_IP _T6IP
 #define _Timer_ESTADOS_IE _T6IE

#elif (Timer_ESTADOS == 7)
#define TMR_Timer_ESTADOS  TMR7
#define PR_Timer_ESTADOS   PR7
#define TCON_Timer_ESTADOS T7CON

 #define _Timer_ESTADOS_Interrupt _T7Interrupt
 #define _Timer_ESTADOS_IF _T7IF
 #define _Timer_ESTADOS_IP _T7IP
 #define _Timer_ESTADOS_IE _T7IE

#elif(Timer_ESTADOS==8)
 #define TMR_Timer_ESTADOS  TMR8
#define PR_Timer_ESTADOS   PR8
#define TCON_Timer_ESTADOS T8CON

 #define _Timer_ESTADOS_Interrupt _T8Interrupt
 #define _Timer_ESTADOS_IF _T8IF
 #define _Timer_ESTADOS_IP _T8IP
 #define _Timer_ESTADOS_IE _T8IE

#elif (Timer_ESTADOS == 9)
#define TMR_Timer_ESTADOS  TMR9
#define PR_Timer_ESTADOS   PR9
#define TCON_Timer_ESTADOS T9CON

 #define _Timer_ESTADOS_Interrupt _T9Interrupt
 #define _Timer_ESTADOS_IF _T9IF
 #define _Timer_ESTADOS_IP _T9IP
 #define _Timer_ESTADOS_IE _T9IE

#elif(Timer_ESTADOS==0||Timer_ESTADOS>=9)
#error ("Timer_ESTADOS NO DEFINIDO")
#endif


#define _ISR_NO_PSV __attribute__((interrupt, no_auto_psv))

extern unsigned short stop_flag;
extern unsigned short cont_ms;
extern unsigned int clockType;
//===========================================


void _ISR_NO_PSV _Timer_RENDIMIENTO_Interrupt(void);
void inic_timer_rendimiento (void);
void Inic_Tiempo_Miliseg (void);