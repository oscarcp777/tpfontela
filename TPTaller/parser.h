// parser.h
typedef struct parser{
               char config[3];  //0-sep 1-esc 2-coment
               char* linea;
               int ncampos;
               FILE *log;
                     }TDA_Parser;
//PRE:	Parser no creado. El car�cter separador es distinto del escape.
int parserCrear(TDA_Parser* tda,char* arch_conf,char* arch_log);
/*POST:	Devuelve 1 si pudo crear el parser, y escribe en el log "parserCrear: 
 Parser creado exitosamente". No lee ninguna l�nea. Devuelve 0 en otro caso, y 
 escribe en el log "parserCrear: Error <descripci�n del error>". */

//PRE: Parser creado.
int parserDestruir(TDA_Parser* tda);
/*POST:	Devuelve 1 si pudo destruir el parser, y escribe en el log 
 "parserDestruir: Parser destruido". Devuelve 0 en otro caso, y escribe en el
  log "parserDestruir: Error <descripci�n del error>".*/
  
//PRE: Parser creado.
int parserCargarLinea(TDA_Parser* tda,char* linea);
/*POST:	Devuelve 1 si pudo obtener la siguiente l�nea, y escribe en el log 
 "parserSiguiente: Linea leida exitosamente". Devuelve 0 en otro caso (Fin de 
 archivo), y escribe en el log "parserSiguiente: Error <descripci�n del 
 error>".*/

//PRE:	Parser creado, se ley� al menos una l�nea.
int parserCantCampos(TDA_Parser* tda);
/*POST:	Devuelve la cantidad de campos de la l�nea (Los campos vac�os se 
 cuentan) , y escribe en el log "parserCantCampos: Cantidad de campos de la
  linea = <cantidad de campos>".*/
  
/*PRE:	Parser creado. La funci�n parserSiguiente se ejecuto previamente sin
 error. El campo N existe en la l�nea actual.*/  
int parserCampo(TDA_Parser* tda, int n, char* valor);
/*POST:	Devuelve 1 si pudo obtener el valor del campo, y escribe en el log
 "parserCampo: Campo <n> obtenido exitosamente = "<valor>"".*/
 
 

