int lowPass(int signal);
int highPass(int lpValue);
int derivative(int hpValue);
int movingWI(int sqValue);
int squaring(int DeValue);

void filter();

void gatherFT(int mwiValue, int index);
void detect(int mwiValue);
