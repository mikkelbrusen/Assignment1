#include "filters.h"
#include "structures.h"

struct detectStructure{
	int h;
	int x[3];

	/* peaks should be saved in .txt file? */
	int peaks[30];
};

struct detectStructure detect(struct detectStructure a, int mwiValue ){
	struct detectStructure b;
	b = a;

	int xMin1, x0, xPlus1;
	int spkf, npkf, threshold1, threshold2;
	int rr_average1, rr_average2, rr_low, rr_high, rr_miss;

	int h = a.h;

	a.x[h] = mwiValue;
	b.x[h] = mwiValue;

	x0 = a.x[h];
	h = (h+1)%3;

	xMin1 = a.x[h];
	h = (h+1)%3;

	xPlus1 = a.x[h];

	/* Equation5 */
	if (xMin1 < x0 && x0 > xPlus1){

	}

	/* Equation6 */
	spkf = 0.125*x0 + 0.875*spkf;

	/* Equation7 */
	threshold1 = npkf + 0.25*(spkf-npkf);

	/* Equation8 */
	threshold2 = 0.5*threshold2;

	/* Equation9 */
	npkf = 0.125*x0 + 0.875*npkf;

	/* Equation10 for searchback BEWARE p_n is not defined yet */
	spkf = 0.25*p_n + 0.75*spkf;


}






