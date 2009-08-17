#define TAM_LINEA 40

typedef struct balde{
	float x;
	float y;
	float ancho;
	float vol;
	char* id;
	int cantGotas;


}TDA_Balde;


void crearBalde(TDA_Balde* balde);