#define TAM_MSJ 10000                 //Tamaño maximo del mensaje a enviar
#define PRIMER_ENVIO 15   
#define ARCH_CONF "config.txt"    //Nombre archivo configuración parser
#define ARCH_LOG  "log.txt"     //Nombre archivo de log del parser
#define TAM_NOMBRE_ARCH 30



DWORD WINAPI recibir(CONEXION *conexion);


DWORD WINAPI enviar(CONEXION *conexion);