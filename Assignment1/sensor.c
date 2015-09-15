#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

FILE *file;

int getNextData(){
	int value;

	if(fscanf(file,"%i",&value) != EOF) {
		return value;
	} else{
		return 9999;
	}
}

void readFile(){
	static const char ECG[] = "ECG.txt";
	file = fopen(ECG,"r");
}
