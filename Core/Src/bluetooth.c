/*
 * bluetooth.c
 *
 *  Created on: Apr 6, 2021
 *      Author: jerem
 */
#include "bluetooth.h"

// Conversion d'un int en string pour l'afficher sur le terminal
void display(int value)
{
	char msg[10];
	sprintf(msg, "%hu\r\n", value);
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}

// Permet de comparer deux chaines de caracteres
// Retourne -> 1 si elles sont identiques
//             0 si elles sont différentes
uint8_t string_compare(char msg1[], char msg2[], uint16_t length)
{
	uint8_t compare = 0, i;
	for(i=0; i<length; i++)
	{
		if(msg1[i]==msg2[i])
		{
			compare++;
		}
	}
	if(compare==length)
	{ return 1; }
	else
	{ return 0; }
}


// On appel cette fonction à chaque fois que l'on reçoit des données via bluetooth
// Cette fonction sert à traiter ces données pour piloter la voiture
void car_command()
{
	if(string_compare(buffer, "vit", strlen("vit")))
	{
		vitesse_M();
		strcat(buffer,"est la fonction appelee \n");
		HAL_UART_Transmit(&huart2,(uint8_t*)buffer, strlen(buffer), 1000); // via moniteur série
	}else
	if(string_compare(buffer,"an", strlen("an")))
	{
		servo_M();
		strcat(buffer,"est la fonction appelee \n");
		HAL_UART_Transmit(&huart2,(uint8_t*)buffer, strlen(buffer), 500); // via moniteur série
	}else
	if(string_compare(buffer, "klaxon", strlen("klaxon"))) // Si on reçoit "klaxon"
	{
		klaxon();
		strcat(buffer,"est la fonction appelee \n");
		HAL_UART_Transmit(&huart2,(uint8_t*)buffer, strlen(buffer), 500); // via moniteur série
	}else
	if((string_compare(buffer, "clign",strlen("clign"))))  // Si on recoit "clign"
	{
		cligno();
		strcat(buffer,"est la fonction appelee \n");
		HAL_UART_Transmit(&huart2,(uint8_t*)buffer, strlen(buffer), 500); // via moniteur série
	}else
	if(string_compare(buffer, "phares",strlen("phares")))
	{
		phares();
		strcat(buffer,"est la fonction appelee \n");
		//HAL_UART_Transmit(&huart1,(uint8_t*)buffer, strlen(buffer), 500); // via bluetooth
		HAL_UART_Transmit(&huart2,(uint8_t*)buffer, strlen(buffer), 500); // via moniteur série
	}else
	{	// Permet d'observer le message reçu
		strcat(buffer,"est le message recu (aucune fonction appelee) \n");
		HAL_UART_Transmit(&huart2,(uint8_t*)buffer, strlen(buffer), 500); // via le moniteur série
	}
}




