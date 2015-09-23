#include "filters.h"
#include <stdio.h>

void storePeak(int);
void checkThreshold(int);
void checkForRR();
void storeRPeak(int);
void storeRecentRR(int);
void storeRecentOK(int);
void peak2Update(int);
void commonUpdate(int);
int calcRRAve(int[],int);
void searchBack();
void checkRRMiss(int);

//rPeak consists of the peak value and a timestamp. Row 0 is peaks and Row 1 is the time
//See storeRpeak
static int rPeak[2][500]= {0};
static int data[3] = {0};
static int spkf = 4500;
static int npkf = 1000;
static int threshold1 = 1875;
static int threshold2 = 938;
static int rr;
static int rr_average1 = 150;
static int rr_average2 = 155;
static int rr_low = 138;
static int rr_high = 174;
static int rr_miss = 249;
static int recentRR_OK[500]= {0};
static int recentRR[500] = {0};
static int peaks[500] = {0};
static int hpeaks = 0;
static int timer = -1;
static int hRPeak = 0;
static int recentRRlength = 0;
static int recentOKlength = 0;


//Reads in the first two data points
void gatherFT(int mwiValue, int index){
	//Increment timer for first to values
	timer++;
	data[index] = mwiValue;
}

//Reads new data, and detects peaks
void detect(int mwiValue ){
	static int slope = 0;
	//Increment timer each time we read a new value
	timer++;
	if(timer==4682){
		int test = 5;
	}
	data[2] = mwiValue;
	if (data[1] > data[2] && slope){
		storePeak(data[1]);
		checkThreshold(data[1]);
		slope = 0;
	} else if(data[2]>data[1]){
		slope = 1;
	}
	data[0]=data[1];
	data[1]=data[2];
}

//Stores a peak value into peaks
void storePeak(int x){
	peaks[hpeaks] = x;
	hpeaks = (hpeaks+1) % 500;
}

//Checks if peak is higher than threshold1
void checkThreshold(int x){
	if(x > threshold1){
		checkForRR();
	} else{
		npkf = 0.125*x + 0.875*npkf;
		threshold1 = npkf + 0.25*(spkf-npkf);
		threshold2 = 0.5*threshold1;
	}
}

//Checking RRvalue if its higher than rr_low and lower than rr_high
void checkForRR(){
	static int rtprev = 0;
	static int counter = 0;
	rr = timer - rtprev;
	rtprev = timer;
	//Checks if interval is OK
	if(rr_low < rr && rr < rr_high){
		storeRPeak(data[1]);
		storeRecentRR(rr);
		storeRecentOK(rr);
		rr_average2 = calcRRAve(recentRR_OK,recentOKlength);
		rr_average1 = calcRRAve(recentRR,recentRRlength);
		commonUpdate(rr_average2);
		counter = 0;
	} else {
		counter++;
		if(counter>4){
			printf("WARNING: DEAD MAN; Timer: %d \n",timer);
			counter = 0;
		}
		checkRRMiss(rr);
	}

}

//stores Rpeak. Takes the peak value as argument. Timer should be known globally within detect.c
void storeRPeak(int x){
	//Stores peak value in row 0, and column number equal the header
	rPeak[0][hRPeak]=x;
	//Stores timer value in row 1, and column number equal the header
	rPeak[1][hRPeak]=timer;
	hRPeak = (hRPeak + 1) % 500;

	// Print the latest R-peak, time and if needed a warning to console
	if (x<2000){
		printf("WARNING! Low R-peak");
	}
	printf("Timer: %d ; R-peak: %d ; Threshold: %d \n", timer, x, threshold1);

}

//Stores recent RR value
void storeRecentRR(int x){
	if(recentRRlength<500){
		recentRRlength++;
	}
	static int hRecent = 0;
	recentRR[hRecent]=x;
	hRecent = (hRecent + 1) % 500;
}

//Stores recent RR value, which was OK (correctly inside the interval)
void storeRecentOK(int x){
	if(recentOKlength<500){
		recentOKlength++;
	}
	static int hRecentOK = 0;
	recentRR_OK[hRecentOK] = x;
	hRecentOK = (hRecentOK+1) % 500;
}

//Updates peak and relevant values
void peak2Update(int peak){
	storeRPeak(peak);
	spkf = 0.25*peak + 0.75*spkf;
	storeRecentRR(rr);
	rr_average1 = calcRRAve(recentRR,recentRRlength);
	commonUpdate(rr_average1);
}

//Updates RR values and thresholds
void commonUpdate(int rr_av){
	rr_low = 0.92*rr_av;
	rr_high = 1.16*rr_av;
	rr_miss = 1.66*rr_av;
	threshold1 = npkf + 0.25*(spkf-npkf);
	threshold2 = 0.5*threshold1;
}

//Calculates Average of RR recent values (both OK and regular)
int calcRRAve(int x[],int length){
	int average = 0;
	for(int i = 0; i<length; i++){
		average += x[i];
	}
	return average/length;
}

// Looks back to see if there is an R-peak that needs to be classified
void searchBack(){
	int hsB = hpeaks;
	for (int i=0; i<500; i++) {
		if(peaks[hsB] > threshold2) {
			peak2Update(peaks[hsB]);
			break;
		} else {
			hsB = (hsB + 499) % 500;
		}
	}
}

//Checks if RR value is higher than rr_miss - if not do nothing.
void checkRRMiss(int rr){
	if(rr>rr_miss){
		printf("hey");
		searchBack();
	}
}


