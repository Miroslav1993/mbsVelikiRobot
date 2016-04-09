/*
 * kombinacija5pink.c
 *
 * Created: 02-Apr-16 2:24:01 PM
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

#define VremeCekanjaPIDa 0  //15000
#define Napred 2
#define Nazad 1

void kombinacija5pink(void)
{
	if(stigao_flag == 1)
	brojac ++;
	switch(step1)
	{
		case 0: //pozicionira za guranje
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = prva_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-280, -65, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 1: //gura toranj u polje gde se sklapa zamak
		if(flag1 == 0)
		{
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-1000, -65, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 2: // vraca se unazad iz polja
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = treca_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-245, -65, Nazad); //-600
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
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -245, -880, 0, Napred); //-820
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 4: // ide pored zida
		if(flag1 == 0)
		{
			izvuci_cilindar();
			zeljena_pravolinijska_brzina = prva_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-950, -880, Napred);
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
			zeljena_pravolinijska_brzina = treca_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-450, -860, Nazad);
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
			zadaj_X_Y(-950, -860, Napred);
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
			zeljena_pravolinijska_brzina = treca_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-450, -860, Nazad);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 8: // hvata skoljku koju je gurnuo kad je isao da peca i okrece se 
		if(flag1 == 0)
		{
			otvori_hvataljku();
			zeljena_pravolinijska_brzina = treca_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -1100, -860, -90, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 9: // zatvara hvataljku da bi zadrzao skoljku i okrece se ka preostalim skoljkama koje su blizu peskira
		if(flag1 == 0)
		{
			zatvori_hvataljku();
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -1100, -760, 180, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 10: // NE ZNAM
		if(flag1 == 0)
		{
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-900, -760, Napred);
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
			otvori_hvataljku_vise();
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y( -800, -510, Napred); //bilo 550 //-450
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
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -170, -610, -90, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 13: // vraca se na peksir
		if(flag1 == 0)
		{
			otvori_hvataljku();
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -170, -65, -180, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;

		case 14: // ide unazad i zatvara hvataljku
		if(flag1 == 0)
		{
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y( -300, -65, Nazad);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			zatvori_hvataljku();
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;

		case 15: // ide blizu zida da se pozicionira za skoljke na protivnickoj strani
		if(flag1 == 0)
		{
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -245, -700, 0, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;

		case 16: //ide do najdaljih skoljki
		if(flag1 == 0)
		{
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -2150, -710, 0, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;

		case 17: // otvara hvataljku i okrece se da pokupi najdalje skoljke
		if(flag1 == 0)
		{
			otvori_hvataljku_vise();
			zeljena_pravolinijska_brzina = treca_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -2200, -710, 90, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 18: // okrece se ka peskiru
		if(flag1 == 0)
		{
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -2200, -900, 180, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;

		case 19: // zatvara hvataljku i ide ka peskiru
		if(flag1 == 0)
		{
			zatvori_hvataljku();
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y( -800, -750, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;

		case 20: // vraca se na peksir
		if(flag1 == 0)
		{
			otvori_hvataljku();
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y( -170, -65, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;

		case 21: // ide unazad i zatvara hvataljku
		if(flag1 == 0)
		{
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y( -300, -65, Nazad);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			zatvori_hvataljku();
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