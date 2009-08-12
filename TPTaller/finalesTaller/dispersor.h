#define TAM_LINEA 100
#define MAX_ID 20


typedef struct dispersor{
        char* id;  //0-sep 1-esc 2-coment
        float x;
        float y;
        float ancho;
        float alto;
        char *linea;
}TDA_Dispersor;



int dispersorCrear(TDA_Dispersor* tda);

void parsearLineaDispersor(TDA_Dispersor* tda);

void cargarLineaDispersor(TDA_Dispersor* tda, char* linea);  

void mostrarLineaDisp();

int dispersorDestruir(TDA_Dispersor* tda);
