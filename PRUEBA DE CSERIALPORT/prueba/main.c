
    #include <stdio.h>
	#include <stdlib.h>
	#include "lib/CSerialPort.h"
 

	int main(){
		printf("hola");
		PORT p3 = OpenPort(6);
		SetPortBoudRate(p3, CP_BOUD_RATE_9600);
		SetPortDataBits(p3, CP_DATA_BITS_8);
		
		//char sendstr[80] = "Hello CSerialPort";
		char recivestr[6];
        
		//SendData(p1, sendstr);
		while(1)
		{
		ReciveData(p3, recivestr, 6);
        int num = atoi(recivestr);
		printf("recivo:%s \n",recivestr);
		//printf("recivo int:%d\n",num);
		}
		ClosePort(p3);
		
		return 0;
	}