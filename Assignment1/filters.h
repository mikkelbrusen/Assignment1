struct LPStructure lowPass(struct LPStructure a, int signal);
struct HPStructure highPass(struct HPStructure a, int lpValue);
struct DeStructure derivative(struct DeStructure a, int hpValue);
struct MWIStructure movingWI(struct MWIStructure a, int sqValue);
int squaring(int DeValue);

void filter();
