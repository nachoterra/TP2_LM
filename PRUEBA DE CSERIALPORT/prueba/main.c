
    #include <stdio.h>
	#include <stdlib.h>
	#include "lib/CSerialPort.h"
 

	int main(){
		printf("hola");
		PORT p3 = OpenPort(4);
		SetPortBoudRate(p3, CP_BOUD_RATE_9600);
		SetPortDataBits(p3, CP_DATA_BITS_8);

		FILE *ptr_file;
		ptr_file =fopen("serialport.txt","w");
		fprintf(ptr_file,"%d",5);
		fclose(ptr_file);	
		ptr_file =fopen("serialport.txt","w");
		fprintf(ptr_file,"%d",6);
		fclose(ptr_file);
		if(ptr_file == NULL)
		{
			printf("Error!");   
			//exit(1);             
		}
		//char sendstr[80] = "Hello CSerialPort";
		char recivestr[18];
        
		//SendData(p1, sendstr);
		while(1)
		{
		ReciveData(p3, recivestr, 18);
        int num = atoi(recivestr);
		printf("recivo:%s \n",recivestr);
		//printf("recivo int:%d\n",num);
		}
		ClosePort(p3);
		
		return 0;
	}