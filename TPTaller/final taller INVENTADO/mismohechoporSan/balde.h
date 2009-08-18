
typedef struct balde{
	char* id;
	float x;
	float y;
	int vol;
	float ancho;
	int cantidadGotas;}TDA_Balde;


void crearBalde(TDA_Balde* balde);

void cargarCamposBaldes(TDA_Balde* balde,char* linea);

void destruirBalde(TDA_Balde* balde);