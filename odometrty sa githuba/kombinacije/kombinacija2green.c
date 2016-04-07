/*
 * kombinacija2green.c
 *
 * Created: 02-Apr-16 2:30:50 PM
 *  Author: miros
 */ 

#include <avr/io.h>
#include "math.h"
#include "../testiranje.h"
#include "../avr_compiler.h"
#include "../usart_driver.h"
#include "../port_driver.h"
#include "../adc_driver.h"
#include "../globals.h"
#include "../mechanism.h"
#include "../hardware.h"

volatile unsigned char step1;
volatile char flag1;
volatile unsigned long brojac;

#define VremeCekanjaPIDa 0  //15000
#define Napred 2
#define Nazad 1

void kombinacija2green (void)
{
	if(stigao_flag == 1)
	brojac ++;
	
	switch(step1)
	{
		case 0: // pozicionira se za gurenje blokova
		if(flag1 == 0)
		{
			zatvori_hvataljku();
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-300, 0, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 1: //gura u polje
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = prva_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-1000, 0, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 2: // vraca se da izbegne skoljke
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = prva_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-450, 0, Nazad);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 3: // prilazi do zida i pozicionira se za pecanje
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = druga_brzina;
			zatvori_hvataljku();
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -450, 850, -90, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			izvuci_cilindar();
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 4: // ide pored zida
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = prva_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-1000, 850, Nazad);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 5: // vraca se
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = prva_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-450, 850, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 6: // peca drugi put
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = prva_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-1000, 850, Nazad);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 7: // vraca se drugi put
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = prva_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-450, 850, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 8: // staje da ostavi ribice
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = druga_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -800, 800, -180, Nazad); // 1520
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;

		case 9: // pozicionira se za najdalje skoljke
		if(flag1 == 0)
		{
			uvuci_cilindar();
			zeljena_pravolinijska_brzina = druga_brzina;
			stigao_flag = 0;
			flag1 = 1;
			otvori_hvataljku_vise();
			zadaj_X_Y_teta( -1250, 715, 90, Napred); // 1520
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 10: // skuplja srednje i okrece se ka peskiru
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = druga_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -1250, 700, 90, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 11:
		if(flag1 == 0) // skuplja srednju skoljku blizu peksiru
		{
			zeljena_pravolinijska_brzina = druga_brzina;
			zatvori_hvataljku();
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y( -1150, 600,  Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 12:  // pozicionira se za skupljanje donjih skoljki
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = druga_brzina;
			otvori_hvataljku_vise();
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y( -225, 650, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 13:  // pozicionira se za skupljanje donjih skoljki
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = druga_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -225, 120, 90, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 14: // vraca se na peksir
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = treca_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -225, 120, 180, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			zeljena_pravolinijska_brzina = treca_brzina;
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 15: // gura na peksira
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = treca_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y( -100, 120, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 16: // gura na peksira
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = treca_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y( -600, 120, Nazad);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			zatvori_hvataljku();
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 17: // gura na peksira
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = prva_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y( -180, 0, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		default:
		//do nothing
		break;
	}
}