/*
 * kombinacija4pink.c
 *
 * Created: 02-Apr-16 2:23:33 PM
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


void kombinacija4pink(void)
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
		
		case 1: //gura u polje
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
		
		case 2: // vraca se da izbegne skoljke
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = treca_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-625, -65, Nazad);
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
			zadaj_X_Y_teta( -625, -880, 0, Napred); //-820
			
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;

		case 4: // prilazi do zida i pozicionira se za pecanje
		if(flag1 == 0)
		{
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -625, -880, 0, Napred);
			
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 5: // ide pored zida
		if(flag1 == 0)
		{
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
		
		case 6: // vraca se
		if(flag1 == 0)
		{
			zeljena_pravolinijska_brzina = treca_brzina;
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y(-450, -860, Nazad); //-800
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 7: // peca drugi put
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
		
		case 8: // vraca se drugi put
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
		
		case 9: // pozicionira se za najdalje skoljke
		if(flag1 == 0)
		{
			otvori_hvataljku();
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -1480, -860, -90, Napred);
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
			zatvori_hvataljku();
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -1480, -760, 180, Napred); //-700
		}
		else if((stigao_flag == 1) && (brojac >= VremeCekanjaPIDa))
		{
			brojac = 0;
			step1++;
			flag1 = 0;
		}
		break;
		
		case 11: // skuplja srednju skoljku blizu sredini
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
		
		case 12:
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
		
		case 13:  // pozicionira se za skupljanje donjih skoljki
		if(flag1 == 0)
		{
			stigao_flag = 0;
			flag1 = 1;
			zadaj_X_Y_teta( -170, -610, -90, Napred); //-550
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

		case 15: // vraca se na peksir
		if(flag1 == 0)
		{
			otvori_hvataljku();
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