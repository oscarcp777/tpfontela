
typedef struct rec_base{
	char* id;
	float x; //sup izq
	float y; //sup izq
	float ancho;
	float alto;}TDA_RBase;
	

typedef struct rec_result{
	float distancia;
	float area;
	TDA_RBase* rect[3];}TDA_RRes;



void crearRBase(TDA_RBase* rect);

void cargarRBase(TDA_RBase* rect, char* linea);

void destruirRBase(TDA_RBase* rect);
