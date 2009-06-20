#ifndef _PARSER_H_
#define _PARSER_H_


typedef struct parser{
        char config[3];  //0-sep 1-esc 2-coment
        char* linea;
        int ncampos;
        FILE *log;
}TDA_Parser;

/*********************************************************************************/
/* PRE:	Parser no creado. El carácter separador es distinto del escape.          */
/* POST:	Devuelve 1 si pudo crear el parser, y escribe en el log "parserCrear:*/
/* Parser creado exitosamente". No lee ninguna línea. Devuelve 0 en otro caso, y */
/* escribe en el log "parserCrear: Error <descripción del error>".               */
/*********************************************************************************/
int parserCrear(TDA_Parser* tda,char* arch_conf,char* arch_log);
/*********************************************************************************/
/*PRE: Parser creado.                                                            */
/*POST:	Devuelve 1 si pudo destruir el parser, y escribe en el log               */
/*"parserDestruir: Parser destruido". Devuelve 0 en otro caso, y escribe en el   */
/* log "parserDestruir: Error <descripción del error>".                          */
/*********************************************************************************/
int parserDestruir(TDA_Parser* tda);
/*********************************************************************************/
/*PRE: Parser creado.                                                            */
/*POST:	Devuelve 1 si pudo obtener la siguiente línea, y escribe en el log       */
/* "parserSiguiente: Linea leida exitosamente". Devuelve 0 en otro caso (Fin de  */
/* archivo), y escribe en el log "parserSiguiente: Error <descripción del        */
/* error>".                                                                      */
/*********************************************************************************/
int parserCargarLinea(TDA_Parser* tda,char* linea);

/*********************************************************************************/
/*PRE:	Parser creado, se leyó al menos una línea.                               */
/*POST:	Devuelve la cantidad de campos de la línea (Los campos vacíos se         */
/* cuentan) , y escribe en el log "parserCantCampos: Cantidad de campos de la    */
/* linea = <cantidad de campos>".                                                */
/*********************************************************************************/
int parserCantCampos(TDA_Parser* tda);

/*********************************************************************************/
/*PRE:	Parser creado. La función parserSiguiente se ejecuto previamente sin     */
/*POST:	Devuelve 1 si pudo obtener el valor del campo, y escribe en el log       */
/*"parserCampo: Campo <n> obtenido exitosamente = "<valor>"".                    */
/*error. El campo N existe en la línea actual.                                   */  
/*********************************************************************************/
int parserCampo(TDA_Parser* tda, int n, char* valor);

 
 

#endif