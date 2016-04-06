/*
 * kombinacija4green.c
 *
 * Created: 02-Apr-16 2:35:26 PM
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
