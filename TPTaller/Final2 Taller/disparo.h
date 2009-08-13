
typedef struct disparo{
	int idPatea;
	int idAtaja;
	int xI,xF,yI,yF;
	int yArquero;
	int alturaArquero;}TDA_Disparo;


void crearDisparo(TDA_Disparo* tda);

void destruirDisparo(TDA_Disparo* tda);