struct LPStructure lowPass(struct LPStructure a, int signal);
struct HPStructure highPass(struct HPStructure a, int lpValue);
struct DeStructure derivative(struct DeStructure a, int hpValue);
int squaring(int DeValue);
void filter();
