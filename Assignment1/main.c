#include <stdio.h>
#include "sensor.h"

int main() {

	readFile();

	printf("%i \n",getNextData());
	printf("%i \n",getNextData());

	return 0;
}
