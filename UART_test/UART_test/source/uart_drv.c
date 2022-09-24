#include "uart_drv.h"
#include <stdio.h>

#define UART_HAL_DEFAULT_BAUDRATE 1000

#define BUFLEN 125

static char buffer[BUFLEN];
static char* input_pointer = &buffer;
static char* output_pointer = &buffer;



void UART_Init (void){
	//Clock gating
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;
	SIM->SCGC4 |= SIM_SCGC4_UART3_MASK;

	//Configure UART0 TX and RX PINS

	#define UART0_TX_PIN 17 //PTA2
	#define UART0_RX_PIN 16 //PTA1
	PORTB->PCR[UART0_TX_PIN]=0x0; //Clear all bits
	PORTB->PCR[UART0_TX_PIN]|=PORT_PCR_MUX(3); //Set MUX to UART0
	PORTB->PCR[UART0_TX_PIN]|=PORT_PCR_IRQC(0); //Disable Port interrupts
	PORTA->PCR[2] = 0;
	PORTA->PCR[2] |= PORT_PCR_MUX(2);
	PORTA->PCR[2] |= PORT_PCR_IRQC(0);

	//Dejo el baudrate en 9600;
	UART_SetBaudRate(UART0, 9600);

	//Habilitamos UART como transmisor
	UART0->C2 |= (UART_C2_TE_MASK | UART_C2_TIE_MASK);

}




void enable_UART_int(){
	NVIC_EnableIRQ(UART0_RX_TX_IRQn);
	NVIC_SetPriority(UART0_RX_TX_IRQn,0);
	NVIC_EnableIRQ(UART0_ERR_IRQn);
	NVIC_SetPriority(UART0_ERR_IRQn,0);
}

void disable_UART_int(){
	NVIC_DisableIRQ(UART0_RX_TX_IRQn);
	NVIC_DisableIRQ(UART0_ERR_IRQn);
}


static bool err = false;

__ISR__ UART0_RX_TX_IRQHandler (void)
{

	 if(((UART0->S1) & UART_S1_TDRE_MASK) !=0){ //Puedo Transmitir ?
		 if(output_pointer==input_pointer){
		 			 disable_UART_int();
		 }
		 else{

			 UART0->D = *output_pointer; // Transmito '!'
			 output_pointer++;
			 if (output_pointer== &buffer + BUFLEN){
				 output_pointer=&buffer;
			 }

		 }


	 }

}

__ISR__ UART0_ERR_IRQHandler(void)
{
	err=true;
}


void UART_SetBaudRate (UART_Type *uart, uint32_t mybaudrate) {

uint16_t sbr, brfa; 
uint32_t clock; 

#define __BASE_CLOCK__ 100000000U

clock = ((uart == UART0) || (uart == UART1))?(__BASE_CLOCK__):(__BASE_CLOCK__ >> 1);

uint32_t baudrate;
baudrate = ((mybaudrate == 0)?(UART_HAL_DEFAULT_BAUDRATE):((mybaudrate > __BASE_CLOCK__/2)?(UART_HAL_DEFAULT_BAUDRATE):(mybaudrate)));

sbr = clock / (baudrate<<4);
brfa = (clock << 1) / baudrate - (sbr<<5);

uart-> BDH = UART_BDH_SBR(sbr>>8);
uart-> BDL = UART_BDL_SBR(sbr);
uart-> C4 = (uart->C4 & ~UART_C4_BRFA_MASK) | UART_C4_BRFA(brfa);

}


void UART_Send_Data(unsigned char *tx_data, int datalen)
{

	for (int i=0; i<datalen; i++){
		*input_pointer=*(tx_data+i);
		input_pointer++;
		if (input_pointer== &buffer + BUFLEN){
			input_pointer=&buffer;
		}
	}

	enable_UART_int();

}
