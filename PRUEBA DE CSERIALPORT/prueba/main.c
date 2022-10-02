
#include <stdio.h>
#include <stdlib.h>
#include "lib/CSerialPort.h"

// typedef struct valor {
// 	char p0;
// 	char p1;
// 	char p2;
// 	char p3;
// } valor;

// typedef struct info {
// 	char init;
// 	char group;
// 	valor pitch;
// 	valor roll;
// 	valor yaw;
// 	char final  
// } info;





int main(){

	// info text={0};
	// text.init = 'A';
	// text.pitch={0};
	// text.final = '\0';
	// printf("text: %s",text.pitch);
	


	// printf("hola");
	PORT p3 = OpenPort(3);
	SetPortBoudRate(p3, CP_BOUD_RATE_9600);
	SetPortDataBits(p3, CP_DATA_BITS_8);

	// FILE *ptr_file;
	// ptr_file =fopen("serialport.txt","w");
	// fprintf(ptr_file,"%d",5);
	// fclose(ptr_file);	
	// ptr_file =fopen("serialport.txt","w");
	// fprintf(ptr_file,"%d",6);
	// fclose(ptr_file);
	// if(ptr_file == NULL)
	// {
	// 	printf("Error!");   
	// 	//exit(1);             
	// }
	// //char sendstr[80] = "Hello CSerialPort";
	char recivestr[15];
	
	// //SendData(p1, sendstr);
	while(1)
	{
		
		if(ReciveData(p3, recivestr, 15))
		{
		int num = atoi(recivestr);
		printf("recivo:%s ",recivestr);
		//printf("recivo int:%d\n",num);
		}
		else
		{
			printf("error recieve");
		}
	 }
	 ClosePort(p3);
	
	return 0;
}