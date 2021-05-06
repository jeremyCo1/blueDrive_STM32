/*
 * bluetooth.h
 *
 *  Created on: Apr 6, 2021
 *      Author: jerem
 */

#ifndef INC_BLUETOOTH_H_
#define INC_BLUETOOTH_H_


#include "fcts.h"

uint8_t string_compare(char msg1[], char msg2[], uint16_t length); // Compare 2 chaines de caracteres
void display(int);          // Affiche un int via le moniteur série
void car_command();


#endif /* INC_BLUETOOTH_H_ */
