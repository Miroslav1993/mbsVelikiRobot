/*

PORT_ClearPins(&PORTC, 0b00001000);
PORT_SetPins(&PORTC, 0b00000001);


PORT_Get PortValue(&PORTB);


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
#include "detekcija.h"
#include "testiranje.h"



//volatile unsigned char step1;

// volatile signed long
// X_pos,
// Y_pos,
// X_cilj,
// Y_cilj,
// teta,
// teta_cilj,
// teta_cilj_final;



