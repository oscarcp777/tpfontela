#ifndef _PARSER_H_
#define _PARSER_H_


typedef struct parser{
        char config[3];  //0-sep 1-esc 2-coment
        char* linea;
        int ncampos;
        FILE *log;
}TDA_Parser;

/*********************************************************************************/
/* PRE:	Parser no creado. El car�cter separador es distinto del escape.          */
/* POST:	Devuelve 1 si pudo crear el parser, y escribe en el log "parserCrear:*/
/* Parser creado exitosamente". No lee ninguna l�nea. Devuelve 0 en otro caso, y */
/* escribe en el log "parserCrear: Error <descripci�n del error>".               */
/*********************************************************************************/
int parserCrear(TDA_Parser* tda,char* arch_conf,char* arch_log);
/*********************************************************************************/
/*PRE: Parser creado.                                                            */
/*POST:	Devuelve 1 si pudo destruir el parser, y escribe en el log               */
/*"parserDestruir: Parser destruido". Devuelve 0 en otro caso, y escribe en el   */
/* log "parserDestruir: Error <descripci�n del error>".                          */
/*********************************************************************************/
int parserDestruir(TDA_Parser* tda);
/*********************************************************************************/
/*PRE: Parser creado.                                                            */
/*POST:	Devuelve 1 si pudo obtener la siguiente l�nea, y escribe en el log       */
/* "parserSiguiente: Linea leida exitosamente". Devuelve 0 en otro caso (Fin de  */
/* archivo), y escribe en el log "parserSiguiente: Error <descripci�n del        */
/* error>".                                                                      */
/*********************************************************************************/
int parserCargarLinea(TDA_Parser* tda,char* linea);

/*********************************************************************************/
/*PRE:	Parser creado, se ley� al menos una l�nea.                               */
/*POST:	Devuelve la cantidad de campos de la l�nea (Los campos vac�os se         */
/* cuentan) , y escribe en el log "parserCantCampos: Cantidad de campos de la    */
/* linea = <cantidad de campos>".                                                */
/*********************************************************************************/
int parserCantCampos(TDA_Parser* tda);

/*********************************************************************************/
/*PRE:	Parser creado. La funci�n parserSiguiente se ejecuto previamente sin     */
/*POST:	Devuelve 1 si pudo obtener el valor del campo, y escribe en el log       */
/*"parserCampo: Campo <n> obtenido exitosamente = "<valor>"".                    */
/*error. El campo N existe en la l�nea actual.                                   */  
/*********************************************************************************/
int parserCampo(TDA_Parser* tda, int n, char* valor);

 
 

#endif