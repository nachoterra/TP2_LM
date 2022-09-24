/***************************************************************************//**
  @file     App.c
  @brief    Application functions
  @author   Nicolás Magliola
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "board.h"
#include "gpio.h"
#include "uart_drv.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void delayLoop(uint32_t veces);


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
	UART_Init();
}

/* Función que se llama constantemente en un ciclo infinito */

void App_Run (void)
{
	/*static bool test = true;
	static int val = 0;
	int cant = 1;
	//val = -179;
	val++;
	if (val<0) cant++;
	if((val>=10) || (val<=-10)) cant++;
	if((val>=100) || (val<=-100)) cant++;
	if(val > 180)
	{
		val = -179;

	}
	char text [cant++];
	itoa(val, text, 10);*/

	//text[cant-1]='\0';
	static int count=0;
	char text[18]="AG1P0000R0000Y0000";
	switch(count)
	{
	case 0:
		text[6]='0';
		break;
	case 1:
		text[6]='3';
		break;
	case 2:
		text[6]='6';
		break;
	case 3:
		text[6]='9';
		break;
	case 4:
		text[6]='2';
		text[5]='1';
		break;
	case 5:
		text[6]='5';
		text[5]='1';
		break;
	case 6:
		text[6]='8';
		text[5]='1';
		break;
	default:
		break;

	}
	count++;
	if(count>6)
	{
		count=0;
	}


	text[8]='\0';
	text[13]='\0';
	//UART_Send_Data(text, cant);
	UART_Send_Data(text, 18);
	delayLoop(900000);
	//if(test){
	//	char text []= "Boca la concha de tu madre";
	//	UART_Send_Data(text, sizeof(text)-1);
//		test = false;
	//}


}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void delayLoop(uint32_t veces)
{
    while (veces--);
}


/*******************************************************************************
 ******************************************************************************/
