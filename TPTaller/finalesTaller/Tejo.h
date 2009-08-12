#define TAM_LINEA 100
#define MAX_ID 20

typedef struct tejo{
        char* id;  //0-sep 1-esc 2-coment
        float x;
        float y;
        float radio;
        char* linea;
        char* idDispChoque;
        float distRecorrida;
        int choco;
}TDA_Tejo;


int tejoCrear(TDA_Tejo* tda);

void parsearLineaTejo(TDA_Tejo* tda);

void cargarLineaTejo(TDA_Tejo* tda, char* linea);  

void mostrarLineaTejo(TDA_Tejo* tda);

int tejoDestruir(TDA_Tejo* tda);

void setearIdDispChoque(TDA_Tejo* tda, char* idDisp);
