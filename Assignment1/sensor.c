#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

static const char ECG[] = "ECG.txt";
FILE *file;

int getNextData(){

	int value;

	if(fscanf(file,"%i",&value) != EOF) {
		return value;
	} else{
		return NULL;
	}
}

void readFile(){
	file = fopen(ECG,"r");
}
