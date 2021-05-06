/*
 * fcts.c
 *
 *  Created on: Apr 6, 2021
 *      Author: jerem
 */

#include "fcts.h"


char buffer[50];

int clign;
int position_clign;
int active_clign;
int position_clign_before;

int phare;

void blink_LED(int delay)
{
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, SET);
	HAL_Delay(delay);
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, RESET);
	HAL_Delay(delay);
}

// "vi1000"
// "vi 100"
// "vi  10"
// Commence à rouler pour vit300
void vitesse_M()
{
	int pwm_value;
	char buffer_vitesse[50];
	for(int i=3; i<strlen("vit 100"); i++){
		buffer_vitesse[i-3] = buffer[i];
	}
	pwm_value = (atoi(buffer_vitesse)*10);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm_value);
	display(pwm_value);
}

// Le servo-moteur pivote de -90° à +90°
// -90° -> pwm_value = 30
// +90° -> pmw_value = 120
void servo_M()  // conversion à faire
{
	int pwm_value;
	char buffer_direction[50];

	for(int i=3; i<strlen("dir100"); i++)
	{
		buffer_direction[i-3] = buffer[i];
	}
	pwm_value = atoi(buffer_direction);

	if((pwm_value>0)&&(pwm_value<=180)){
		sens_moteur(1);
		pwm_value = pwm_value*110/180;
	}
	else if((pwm_value>180)&&(pwm_value<=360)){
		sens_moteur(0);
		pwm_value = (pwm_value-180)*110/180;
	}

	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pwm_value);
	display(pwm_value);
}


// PC7  = D9 = sens1
// PB10 = D6 = sens2
void sens_moteur(int sens)
{
	if(sens == 1){
		HAL_GPIO_WritePin(sens1_GPIO_Port, sens1_Pin, RESET);
		HAL_GPIO_WritePin(sens2_GPIO_Port, sens2_Pin, SET);
	}
	else if(sens == 0){
		HAL_GPIO_WritePin(sens1_GPIO_Port, sens1_Pin, SET);
		HAL_GPIO_WritePin(sens2_GPIO_Port, sens2_Pin, RESET);
	}
}

void klaxon()
{
	//HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, SET);
}


// On utilise le timer 3 en interruption pour cette fonction (cf TIM3_IRQHandler)
void cligno()
{
	position_clign_before = position_clign;
	// Choix du clignotant
	if(string_compare(buffer, "cligno", strlen("cligno")))
	{
		position_clign = 1;
	}
	else if(string_compare(buffer, "clignD", strlen("clignD")))
	{
		position_clign = 2;
	}
	else if(string_compare(buffer, "clignG", strlen("clignG")))
	{
		position_clign = 3;
	}

	// Activation ou non du mode clignotant
	if(active_clign == 0)
	{
		active_clign = 1;
	}
	else if (active_clign == 1)
	{
		HAL_GPIO_WritePin(ClignD_GPIO_Port, ClignD_Pin, RESET);
		HAL_GPIO_WritePin(ClignG_GPIO_Port, ClignG_Pin, RESET);
		if(position_clign == position_clign_before)
		{
			active_clign = 0;
		}
	}
}

void phares()
{
	phare = (phare+1)%2;
	if(phare == 1){
		HAL_GPIO_WritePin(phares_GPIO_Port, phares_Pin, SET);
	}else{
		HAL_GPIO_WritePin(phares_GPIO_Port, phares_Pin, RESET);
	}
}





