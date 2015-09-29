#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

FILE *file;
static int validData;

int getNextData(){
	int value;

	if(fscanf(file,"%i",&value) != EOF) {
		validData = 1;
		return value;
	} else{
		return validData = 0;
	}
}

void readFile(){
	static const char ECG[] = "ECG.txt";
	file = fopen(ECG,"r");
}

int getNextDataValid(){
	return validData;
}
