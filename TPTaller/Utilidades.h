#define TAM_MSJ 10000                 //Tama�o maximo del mensaje a enviar
#define PRIMER_ENVIO 15   
#define ARCH_CONF "config.txt"    //Nombre archivo configuraci�n parser
#define ARCH_LOG  "log.txt"     //Nombre archivo de log del parser
#define TAM_NOMBRE_ARCH 30
#define maxlinea 1000

#define RES_OK 0
#define RES_ERROR -1
#define RES_QUIT -2

//#define DEBUG


DWORD WINAPI recibir(CONEXION *conexion);


DWORD WINAPI enviar(CONEXION *conexion);

int reconectarSockets(CONEXION *pConexion);