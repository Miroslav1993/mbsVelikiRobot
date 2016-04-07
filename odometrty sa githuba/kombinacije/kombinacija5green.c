/*
 * kombinacija5green.c
 *
 * Created: 02-Apr-16 2:35:35 PM
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

//volatile unsigned char step1;
//volatile char flag1;
//volatile unsigned long brojac;

#define VremeCekanjaPIDa 0  //15000
#define Napred 2
#define Nazad 1

void kombinacija5green(void)
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
			zadaj_X_Y(-645, 0, Nazad);
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
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -645, 850, -90, Napred);
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
			zadaj_X_Y( -1000, 850, Nazad); // 1520
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 9: // pozicionira mid korak
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = druga_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y( -820, 825, Napred); // 1520
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			otvori_hvataljku_vise();
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		
		case 10: 
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = prva_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta(-450, 825, 90, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;

		case 11: 
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = prva_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta(-450, 500, 180, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;		

		case 12:
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = prva_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta(-225, 500, 90, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
				
		case 13:
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = prva_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta(-225, 120, 180, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;		
		
		case 14: // gura na peksira
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
		
		case 15: // gura na peksira
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