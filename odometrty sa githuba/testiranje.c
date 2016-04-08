/*
 * testiranje.c
 *
 * Created: 16/11/15 14:36:10
 *  Author: miros
 */ 

#include <avr/io.h>
#include "testiranje.h"
#include "avr_compiler.h"
#include "usart_driver.h"
#include "port_driver.h"
#include "adc_driver.h"
#include "math.h"
#include "globals.h"
#include "mechanism.h"
#include "hardware.h"


volatile signed long
X_pos,
Y_pos,
X_cilj,
Y_cilj,
teta,
teta_cilj,
teta_cilj_final;



void postavi_koordinatni_sistem(signed long x, signed long y, signed long teta_des)
{
	X_pos = X_cilj = x;
	Y_pos = Y_cilj = y;
	teta = teta_cilj = teta_cilj_final = teta_des;
	TCD0.CNT = 0;			//Desni enkoder
	TCD1.CNT = 0;			//erLevi enkod
}

void nuliraj_poziciju_robota(void)
{
	X_pos = X_cilj = 0;
	Y_pos = Y_cilj = 0;
	teta = teta_cilj = teta_cilj_final = 0;
	smer_zadati = smer_trenutni = 1;
	TCD0.CNT = 0;			//Desni enkoder
	TCD1.CNT = 0;			//Levi enkoder
}

void zadaj_X_Y_teta(signed long x, signed long y, signed long teta_des, unsigned char dir)
{
	X_cilj = x * scale_factor_for_mm;
	Y_cilj = y * scale_factor_for_mm;
	teta_cilj_final = (teta_des * krug360) / 360;
	smer_zadati = dir;
}

void zadaj_X_Y(signed long x, signed long y, unsigned char dir)
{
	X_cilj = x * scale_factor_for_mm;
	Y_cilj = y * scale_factor_for_mm;
	smer_zadati = dir;
}

void zadaj_teta(signed long teta_des)
{
	teta_cilj_final = (teta_des * krug360) / 360;
	//smer_zadati = dir;
}

void inicijalizuj_bluetooth()
{
	//USARTE1, PE7 -> USARTE1_TX, PE6 -> USARTE1_RX
	PORTE.DIR |= (1 << 7);		//set pin PE7 as output
	PORTE.DIR &= ~(1 << 6);		//set pin PE6 as input
	
	USARTE1.CTRLA |= (1 << 4 | 1 << 2);		//enable receiver and transmitter interrupts at low level
	USARTE1.CTRLB |= (1 << 4 | 1 << 3);		//enable receiver and transmitter
	USARTE1.CTRLC |= (1 << 1 | 1 << 0);		//no parity, 1 stop bit, 8 bit data size
	
	USARTE1.BAUDCTRLA = 12;
	USARTE1.BAUDCTRLB |= (2 << 4);
	
	PMIC.CTRL |= (1 << 0);		//enable low level interrupts
	sei();						//global interrupts enabled
}

void posalji_poruku_bt(char *poruka)
{
	while(*poruka != '\0'){
		posalji_karakter_bt(*poruka);
		poruka++;
	}
}

void posalji_karakter_bt(char c)
{
	USARTE1.DATA = c;
	while(!(USARTE1.STATUS & (1 << 5)));
}

void inicijalizuj_servo_tajmer_20ms()
{
	PORTF.DIR |= (1 << 0);	//servo 1
	
	//Clock source = 32/4 MHz = 8 MHz
	TCF0.CTRLA |= (1 << 2 | 1 << 0);						//Set presclaer to 64, PER 2500 = 20 ms
	TCF0.CTRLB |= (0x0F << 4 | 0x03 << 0);					//Enable Capture/compare A,B,C,D and select single slope PWM
	TCF0.INTCTRLA |= (1 << 0);								//Enable low level overflow interrupt
	TCF0.INTCTRLB |= (1 << 0 | 1 << 2 | 1 << 4 | 1 << 6);	//Enable Capture/compare low level interrupts
	TCF0.PER = 2500;
}

void pomeri_servo_1(uint16_t deg)
{
	uint16_t res = (uint16_t)(deg*(250/180));	//250 cycles for 180 degree turn
	if(res <= 0)
		res = 125;								//125 cycles for 0 degree turn
	else if(res > 250)
		res = 250;
	TCF0.CCA = res;
}

void pomeri_servo_2(uint16_t deg)
{
	uint16_t res = (uint16_t)(deg*(250/180));	//250 cycles for 180 degree turn
	if(res <= 0)
	res = 125;								//125 cycles for 0 degree turn
	else if(res > 250)
	res = 250;
	TCF0.CCB = res;
}

void pomeri_servo_3(uint16_t deg)
{
	uint16_t res = (uint16_t)(deg*(250/180));	//250 cycles for 180 degree turn
	if(res <= 0)
	res = 125;								//125 cycles for 0 degree turn
	else if(res > 250)
	res = 250;
	TCF0.CCC = res;
}

void pomeri_servo_4(uint16_t deg)
{
	uint16_t res = (uint16_t)(deg*(250/180));	//250 cycles for 180 degree turn
	if(res <= 0)
	res = 125;								//125 cycles for 0 degree turn
	else if(res > 250)
	res = 250;
	TCF0.CCD = res;
}

void otvori_hvataljku()
{

	//TCF0.CCB = 120; // levi servo  sto veci broj manje se otvara
	//TCF0.CCC = 200;	// desni servo

	TCF0.CCB = 110; // levi servo  sto veci broj manje se otvara
	TCF0.CCC = 190;
}

void otvori_hvataljku_vise()
{
	TCF0.CCB = 90; // levi servo  sto veci broj manje se otvara
	TCF0.CCC = 235;	// desni servo
}

void zatvori_hvataljku()
{
	TCF0.CCB = 200; // levi servo
	TCF0.CCC = 90; // desni servo
}

void zatvori_hvataljku_pola()
{
	TCF0.CCB = 150; // levi servo
	TCF0.CCC = 140; // desni servo
}

void otvori_lepezu()
{
	TCF0.CCA = 10;
}

void zatvori_lepezu()
{
	TCF0.CCA = 200;
}


void izvuci_cilindar()
{
	PORT_SetPins(&PORTC, 0b00000001);
}

void uvuci_cilindar()
{
	PORT_ClearPins(&PORTC, 0b00000001);
}


void spusti_zvono()
{
	PORT_SetPins(&PORTC, 0b00000100);
	PORT_ClearPins(&PORTC, 0b00000010); //jedan smer
	PORT_SetPins(&PORTC, 0b00010000); //pokreni servo
	_delay_ms(1580);
	PORT_ClearPins(&PORTC, 0b00010010); //zaustavi servo
}

void podigni_zvono_pola()
{
	PORT_SetPins(&PORTC, 0b00001000);
	PORT_ClearPins(&PORTC, 0b00010000); //drugi smer
	PORT_SetPins(&PORTC, 0b00000010); //pokreni servo
	_delay_ms(1675);
	PORT_ClearPins(&PORTC, 0b00010010); //zaustavi servo
}

void podigni_zvono_full()
{
	PORT_SetPins(&PORTC, 0b00001000);
	PORT_ClearPins(&PORTC, 0b00010000); //drugi smer
	PORT_SetPins(&PORTC, 0b00000010); //pokreni servo
	while (!(PORTB.IN & 0b0010000) == 1);
	PORT_ClearPins(&PORTC, 0b00010010); //zaustavi servo
}

ISR(TCF0_CCA_vect)
{
	PORTF.OUT |= (1 << 0);
}

ISR(TCF0_OVF_vect)
{
	PORTF.OUT &= ~(1 << 0);
}