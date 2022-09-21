
    #include <stdio.h>
	#include <stdlib.h>
	#include "lib/CSerialPort.h"
 

	int main(){
		PORT p1 = OpenPort(1);
		PORT p2 = OpenPort(2);
		char sendstr[80] = "Hello CSerialPort";
		char recivestr[80];
        
		SendData(p1, sendstr);
		ReciveData(p2, recivestr, 80);
        printf("envio:%s\n",sendstr);
		printf("recivo:%s \n",recivestr);
		ClosePort(p1);
		ClosePort(p2);
		return 0;
	}