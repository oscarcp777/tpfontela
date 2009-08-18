

typedef struct gota{
	float x;
	float y;
	int enBalde;}TDA_Gota;


void crearGota(TDA_Gota* gota);

void cargarCamposGotas(TDA_Gota* gota, char* linea);

void destruirGota(TDA_Gota* gota);