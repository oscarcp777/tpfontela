#ifndef _TRANSFERENCIA_H_
#define _TRANSFERENCIA_H_

typedef struct _CONEXION{
        WSADATA wsdata;
        struct hostent* host;
        SOCKADDR_IN conexrem;
        SOCKET locsock;
        SOCKET cliente;
        //si es 1 es cliente  , si es 0 en servidor
        int usuario;
}CONEXION;

enum tr_tipo_dato {td_comando, td_int , td_char , td_float, td_double};

#define RES_OK 0

int trEscuchar(int Puerto,	CONEXION *pConexion);

int trConectar(const char *pDireccion, int Puerto, CONEXION *pConexion);

int trEnviar(CONEXION *pConexion, enum tr_tipo_dato tipo, int cantItems, const void *datos);

int trRecibir(CONEXION *pConexion, enum tr_tipo_dato tipo, int cantItems, void *datos);

int trCerrarConexion(CONEXION *pConexion);

int trIP(CONEXION *pConexion, char *pIP);

int trPuerto(CONEXION *pConexion, int *pPuerto);

#endif
