/*
 * kombinacija2pink.c
 *
 * Created: 02-Apr-16 2:22:48 PM
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


void kombinacija2pink(void)
{
	if(stigao_flag == 1)
	brojac ++;
	
	switch(step1)
	{
		case 0: // pozicionira se za gurenje blokova
		zeljena_pravolinijska_brzina = prva_brzina;
		if(flag1 == 0)
		{
			//otvori_hvataljku();
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
		
		case 1: //gura u polje
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = prva_brzina;
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
		
		case 2: // vraca se da izbegne skoljke
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = treca_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-450, -65, Nazad);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 3: // prilazi do zida i pozicionira se za pecanje
		//zeljena_pravolinijska_brzina = 100;
		if(flag1 == 0)
		{

			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -450, -910, 0, Napred); //-915
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 4: // ide pored zida
		zeljena_pravolinijska_brzina = prva_brzina;
		if(flag1 == 0)
		{
			izvuci_cilindar();
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-950, -910, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 5: // vraca se
		zeljena_pravolinijska_brzina = treca_brzina;
		if(flag1 == 0)
		{
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-450, -910, Nazad);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 6: // peca drugi put
		zeljena_pravolinijska_brzina = prva_brzina;
		if(flag1 == 0)
		{
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-950, -910, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 7: // vraca se drugi put
		zeljena_pravolinijska_brzina = treca_brzina;
		if(flag1 == 0)
		{
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-450, -910, Nazad);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;

		case 8: //ide ka srednjem paku da ga gurne u stranu
		zeljena_pravolinijska_brzina = treca_brzina;
		if(flag1 == 0)
		{
			otvori_hvataljku();
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-900, -910, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;

		
		case 9: // pozicionira se za najdalje skoljke
		//zeljena_pravolinijska_brzina = treca_brzina;
		if(flag1 == 0)
		{
			uvuci_cilindar();
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-1450, -760, Napred); // -1450 -760
			//zadaj_X_Y_teta( -1620, -855, -90, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;

		case 10: // pozicionira se za najdalje skoljke
		//zeljena_pravolinijska_brzina = treca_brzina;
		if(flag1 == 0)
		{
			stigao_flag = 0;
			flag1 = 1;
			//zadaj_X_Y( -1620, -650, Napred);
			zadaj_X_Y_teta( -1340, -830, 180, Napred); // -1350 -860
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;

		case 11: // otvara hvataljku i prikuplja srednji pak
		//zeljena_pravolinijska_brzina = treca_brzina;
		if(flag1 == 0)
		{
			//otvori_hvataljku();
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y( -1400, -860, Napred); //-1400
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			//zatvori_hvataljku();
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;

		case 12:
		//zeljena_pravolinijska_brzina = treca_brzina;
		if(flag1 == 0) // skuplja srednju skoljku blizu peksiru
		{
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y( -1280, -760, Napred); //-1280
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			otvori_hvataljku();
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;

		case 13:
		//zeljena_pravolinijska_brzina = treca_brzina;
		if(flag1 == 0) // skuplja srednju skoljku blizu peksiru
		{
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y( -800, -615, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;

		case 14:  // pozicionira se za skupljanje donjih skoljki
		//zeljena_pravolinijska_brzina = treca_brzina;
		if(flag1 == 0)
		{
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -170, -615, -90, Napred);
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 15: // vraca se na peksir
		//zeljena_pravolinijska_brzina = treca_brzina;
		if(flag1 == 0)
		{
			//zatvori_hvataljku();
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

		case 16: // vraca se na peksir
		//zeljena_pravolinijska_brzina = treca_brzina;
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