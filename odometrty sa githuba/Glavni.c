/*
 * X_Drive_Odometry.c
 *
 * Created: 03/11/15 11:29:01
 *  Author: miros
 */ 

#include <avr/io.h>
#include "avr_compiler.h"
#include "usart_driver.h"
#include "port_driver.h"
#include "adc_driver.h"
#include "math.h"
#include "globals.h"
#include "mechanism.h"
#include "hardware.h"
#include "testiranje.h"
#include "detekcija.h"

volatile signed int
PID_brzina_L,
PID_brzina_R,
motor_sample_L16,
motor_sample_R16,
Pe_brzina_L,
Pe_brzina_R,
Ie_brzina_L,
Ie_brzina_R;

volatile signed long
rastojanje_cilj,
PID_teta;

volatile float
sharp1_value;

volatile unsigned long brojac = 0;
volatile unsigned char step1 = 0;
volatile char flag1 = 0;

int main(void)
{
	int msg_counter = 0;
	int servo_counter = 0;
	char servo_flag = 0;
	Podesi_Oscilator();					//podesavanje oscilatora
	Podesi_Parametre_Robota();			//podesavanje broja impulsa u krugu
	Podesi_PID_Pojacanja();				//podesavanje pojacanja PID regulatora
	PodesiADC();						//podesavanje AD konvertora
	Podesi_Tajmere();					//podesavanje tajmera
	Podesi_QDEC();						//podesavanje kvadraturnih dekodera
	Podesi_PWM();						//podesavanje PWM signala za motore i servoe
	Podesi_Interapt();					//podesavanje interapt prioriteta
	Podesi_Pinove();					//podesavanje I/O pinova
	Podesi_USART_Komunikaciju();		//podesavanje komunikacije
	inicijalizuj_bluetooth();
	inicijalizuj_servo_tajmer_20ms();
	zatvori_lepezu();
	
	_delay_ms(2000);					//cekanje da se stabilizuje sistem
	
	nuliraj_poziciju_robota();
	
	////jedan smer
	//PORT_SetPins(&PORTC,	0b00010000);
	//PORT_ClearPins(&PORTC,	0b00000100);

	////drugi smer
	//PORT_SetPins(&PORTC, 0b00000100);
	//PORT_ClearPins(&PORTC, 0b00000010);

	
	////pokrece
	//PORT_SetPins(&PORTC, 0b00010000);

	////zaustavlja
	//PORT_ClearPins(&PORTC, 0b00010010);


	//postavi_koordinatni_sistem ( 0, -98, 0 );

	//while ((PORTB.IN & 0b00001000) == 0)
	//{
		//zatvori_hvataljku();
	//}

	brojac90s = 0;


	//zatvori_hvataljku();


	//spusti_zvono();
	//_delay_ms(4000);
	//podigni_zvono_pola();


	while(1){
		
		//posalji_poruku_bt("servo 180\n\r");
		//posalji_karakter_bt(step1);
		//kombinacija1pink();
		//kombinacija2pink();
		kombinacija3pink();
		//kombinacija4pink();
		//kombinacija5pink();
		//kombinacija1green();
		//kombinacija2green();
		//kombinacija3green();
		//kombinacija4green();
		//kombinacija5green();
		
		
		//Mladen je kaka.
		

		//provera asinhronog stop signala za momentalno zaustavljanje robota
		CheckInputMotorControl();
		
		//Racunanje trenutne pozicije
		if (Rac_tren_poz_sample_counter >= 3){		//9ms
			Rac_tren_poz_sample_counter = 0;
			Racunanje_trenutne_pozicije();
		}
		
		
		//Korekcija pravca i distance prema cilju
		if(Pracenje_Pravca_sample_counter >= 30){	//90ms
			msg_counter++;
			servo_counter++;
			Pracenje_Pravca_sample_counter = 0;
			Pracenje_pravca();
		}

		
		
		//PID regulacija
		if(PID_pozicioni_sample_counter >= 3){		//9ms
			PID_pozicioni_sample_counter = 0;
			PID_ugaoni();
			PID_pravolinijski(); //PID_brzinski se poziva direktno u interaptu sistemskog tajmera TCE1!
		}
				
		//brojanje od 90 sekundi nakon toga stani i otvori lepezu
		if ( brojac90s >= 60000 )
		{
			otvori_lepezu();
			step1 = 100;
		}	

		if(servo_counter > 80)
		{
			servo_counter = 0;
			posalji_poruku_bt("servo 180\n\r");
		}
		
		

	}
}
