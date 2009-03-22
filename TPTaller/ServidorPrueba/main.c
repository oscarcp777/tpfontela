#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librería


WSADATA wsadata; //Declaramos WSADATA

struct hostent *host;
//Delcaramos estrucutra hostent donde almacenaremos la IP que nos devuelva gethostbyname

SOCKADDR_IN conexrem;
/*Declaramos una estructura SOCKADDR_IN para no tener que definir una IP y un puerto
en cada paquete que enviemos. De esa forma todo viajara encapsulado utilizando la estructura
SOCKADDR_IN.
*/
 char buffin[1024];
     char* pbuff = buffin;

SOCKET locsock; // Declaramos el descriptor de fichero que nos de el socket



int WSAInicio() { //declaramos procedimiento
         int wasa = WSAStartup(MAKEWORD(2,0),&wsadata); //Indicamos version 2.0 del socket
         if (wasa != 0) { // Si existen errores…
     printf("%s","Error iniciando WSAStartup \n"); //Mostramos un mensaje
                WSACleanup(); //Limpiamos WSADATA
                return 1; // Retornamos 1 dado que la funcion fallo
         }
         return 0; // Si se inicio todo bien retornamos 0
}

int definirsocket() {
         locsock = socket(AF_INET/* IP V4 */, SOCK_STREAM, 0); // Indicamos que usaremos un socket Stream(TCP)
         if (locsock == INVALID_SOCKET) { // Si existen errores…
         printf("%s","Error definiendo socket \n"); //Mostramos un mensaje
                WSACleanup(); //Limpiamos WSADATA
                return 1; // Retornamos 1 dado que la funcion fallo
         }
         return 0; // Si se inicio todo bien retornamos 0
}

int estructsocket() { // Definimos procedimiento
         host=gethostbyname("localhost"); //Definimos Host con la IP que devuelva gethostbyname
         /* Resolvemos la direccion IP del Dominio localhost, con esto conseguimos traducir nombres de dominio
         sin utilizar direccion IP directamente.
         Esta sera la IP a donde nuestro Cliente conectara.
         */
         conexrem.sin_port = htons(2627); //Ordenacion de Red.
     /*  Definimos puerto (9999) del socket utilizando un "short de máquina a short de la red" (htons)
     Esto lo hacemos para ordenar la forma en la que enviaremos y recibiremos los datos por el puerto del socket
     Mas informacion buscar en google "Big-Endian".
     */
         conexrem.sin_addr = *((struct in_addr *)host->h_addr);
         /* Definimos la IP a donde conectaremos, como teniamos la direccion IP almacenada en "host"
     y la funcion solo admite "in_addr" para almacenar la IP en "h_addr" tenemos que hacer un Casting de modo que
     "host" que es ahora un "in_addr" (debido a el casting (struct in_addr *) ) sea un puntero a "h_addr".
         */
         conexrem.sin_family = AF_INET; // Ordenacion de Maquina
         /*
         Definimos la version 4 de IP
         */
         memset(conexrem.sin_zero,0,8); // Ponemos en 0 la cadena sin_zero en sus 8 espacios

         if ((bind(locsock, (SOCKADDR*)&conexrem, sizeof(conexrem)))!=-1) { // Si existe un error…
     /* Ahora procedemos a realizar la conexion con la IP remota que definimos en la estructura "conexrem.sin_addr"
     y el puerto definido en "conexrem.sin_port". Dado que connect solo acepta "sockaddr" enves de nuestra
     estructura "SOCKADDR_IN" tenemos que realizar un casting para convertir "conexrem" en un "sockaddr".
     Despues medimos la longitud de la estructura con "sizeof" y por ultimo verificamos si se produjo un error
     tratando de conectar ya que por ejemplo la direccion IP remota podria no existir o estar detras de un FireWall
    */
         printf("%s","Error conectando al servidor remoto \n"); // En caso de error mostramos msj
                WSACleanup(); //Limpiamos WSADATA
                return 1; // Retornamos 1 dado que la funcion fallo
         }  else // De lo contrario…
        printf("%s","Coneccion realizada con exito \n"); // Mostramos msj
                return 0; // Si se inicio todo bien retornamos 0
}


     
void escuchar(){
     int exitoEscucha;
     char* lectuar;     
      int addrleng = sizeof(conexrem);
                 
     do{
           exitoEscucha = listen(locsock,1); 
           printf("%d \n",exitoEscucha);
           
            if(exitoEscucha==-1){
                      printf("ERROR EN LA ESCUCHA \n");
                      system("PAUSE");
                      }
            
            else{
                 printf("ESCUCHANDO CORRECTAMENTE \n");
                 /*recv(locsock,pbuff,sizeof(buffin),0);
                 printf("%s \n", buffin);
                 system("PAUSE");*/
                 }            
     }while(TRUE);    
}     

void sockets(){ // Procedimiento que iniciara el socket secuencialmente.
                int addrleng;
        if((WSAInicio()) == 0) { // Si se inicio WSAInicio sin errores…
           if((definirsocket()) == 0) { // Si se inicio definirsocket sin errores…
              if((estructsocket()) == 0) { // Si se inicio estructsocket sin errores…
                int i;
                i=-1;               
                 escuchar();
                  while(i<0){
                i = accept(locsock, (SOCKADDR*)&conexrem, &addrleng);                
                }
              }  else { // Si no conecto..
                      Sleep(500); // Esperamos 500 Milisegundos y…
                              sockets(); // Repetimos proceso
                      }
           }
        }
     }

int main(int argc, char *argv[])
{  
    sockets(); // Iniciamos el Socket
    
    
    system("PAUSE");	
}




