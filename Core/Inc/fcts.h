/*
 * fcts.h
 *
 *  Created on: Apr 6, 2021
 *      Author: jerem
 */

#ifndef INC_FCTS_H_
#define INC_FCTS_H_

#include "main.h"
#include "tim.h"
#include "usart.h"
#include "bluetooth.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gpio.h>

extern char buffer[50];

extern int clign;
extern int position_clign;
extern int active_clign;
extern int position_clign_before;

extern int phare;

void blink_LED(int);

void vitesse_M();
void servo_M() ;
void sens_moteur(int);

void klaxon();
void cligno();
void phares();


#endif /* INC_FCTS_H_ */

