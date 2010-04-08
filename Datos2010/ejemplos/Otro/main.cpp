#include <iostream>
#include <string>
#include "HashingExt.hpp"
//#include "../Compuesto/Atributo.h"
//#include "../Compuesto/AtributoFijo.h"
#include "Atributo.h"
#include "AtributoFijo.h"

using namespace std;


int main()
{
   /*** CASO DE PRUEBA: "inserción con y sin overflow", "eliminación con y sin posibilidad de liberación de bloque"
                                "reutilización de cubos liberados"
   ***/


        char pausa;
        HashingExt un_indice;
        Referencia ref= 10;

        AtributoFijo<int> padron0("padron0");
	AtributoFijo<int> padron1("padron1");
	AtributoFijo<int> padron2("padron2");
	AtributoFijo<int> padron3("padron3");
	AtributoFijo<int> padron4("padron4");
	AtributoFijo<int> padron5("padron5");
	AtributoFijo<int> padron6("padron6");
	AtributoFijo<int> padron7("padron7");

        //Se usarán claves enteras de valores: 2,3,4,5,6,7,9 (las referencias no son importantes)
        //se eligieron estas claves para facilitar su seguimiento "en el papel"
        unsigned num = 2;
	padron0.set( &num);
	padron1.set( &(++num));
	padron2.set( &(++num) );
	padron3.set(&(++num));
	padron4.set(&(++num));
	padron5.set(&(++num));
	padron7.set(&(++num) ); //num == 8
	padron6.set(&(++num));//num==9

	Registro reg0(1, &padron0);
	Registro reg1(1, &padron1);
	Registro reg2(1, &padron2);
	Registro reg3(1, &padron3);
	Registro reg4(1, &padron4);
	Registro reg5(1, &padron5);
	Registro reg6(1, &padron6);
	Registro reg7(1, &padron7);

        //Se crean las claves
	Clave clave0(&reg0, 1, "padron0");
	Clave clave1(&reg1, 1, "padron1");
	Clave clave2(&reg2, 1, "padron2");
	Clave clave3(&reg3, 1, "padron3");
	Clave clave4(&reg4, 1, "padron4");
	Clave clave5(&reg5, 1, "padron5");
	Clave clave6(&reg6, 1, "padron6");
	Clave clave7(&reg7, 1, "padron7");


        /**Se crea un índice extensible modular con 32bytes por cubo, y capacidad para 3 registros

        Notar que el último parámetro es NULL, puesto que este índice no usa el comparador de claves
        Además se pasó la clave0, aunque no se insertará hasta que se llame con insertar().
        El propósito de clave0 es que el índice conozca la estructura de las claves que manejará

        **/
        un_indice.crear("Prueba1", 32, &clave0, NULL);

        un_indice.insertar(ref, &clave0);
        un_indice.insertar(++ref, &clave1);
        un_indice.insertar(++ref, &clave2);

        /**   Esta inserción producirá un overflow en el cubo 0  **/
        un_indice.insertar(++ref, &clave3);
        cout<<"Al insertar la clave 5 se produce un sobreflujo"<<endl;
        un_indice.mostrarEstado();
        cin>> pausa;

        un_indice.insertar(++ref, &clave4);
        un_indice.insertar(++ref, &clave5);
        /***Se llenaron los cubos 0 y 1 (con 3 registros cada uno)**/
        un_indice.mostrarEstado();
        cin>>pausa;

        /** Eliminaciones **/
        //Se elimina la clave de valor 6 en el cubo 1
        cout <<"Se elimina la clave de valor 6 en el cubo 1"<< endl;
        un_indice.eliminar(&clave4);
        un_indice.mostrarEstado();
        cin >> pausa;
        //Se elimina la clave de valor 2 en el cubo 1
        cout << "Se elimina la clave de valor 2 en el cubo 1"<<endl;
        un_indice.eliminar(&clave0);
        un_indice.mostrarEstado();
        cin >> pausa;
        /** Se elimina la clave de valor 4 en el cubo 1, vaciándolo.
                Se puede ver que en este caso, el cubo se puede liberar, quitándo su referencia de la tabla de dispersión.
                Ahora el cubo tendrá que aparecer 2 veces (dividirá por 2 su tamaño de dispersión == 1)
        **/
        cout<< "Se elimina la clave de valor 4 en el cubo 1, vaciandolo"<<endl;
        un_indice.eliminar(&clave2);
        un_indice.mostrarEstado();
        cin >> pausa;

        //cualquier inserción siguiente ocasionará un sobreflujo
        /** Se reutilizará el cubo 1 anteriormente liberado (se consignará de nuevo en la tabla de dispersión **/
        un_indice.insertar(100, &clave0);
        un_indice.mostrarEstado();
        cin >> pausa;

        //Se produce un nuevo sobreflujo, ahora en el cubo 0, por la inserción de la clave 9.
        //Se duplica la tabla
        un_indice.insertar(101, &clave6);
        un_indice.mostrarEstado();
        cin>> pausa;

        un_indice.insertar(102, &clave2);
        un_indice.insertar(103, &clave4);
        un_indice.mostrarEstado();
        cin >> pausa;
        //se produce un overflow que no duplica la tabla
        un_indice.insertar(104, &clave7);
        un_indice.mostrarEstado();
        cin >> pausa;

        return 0;
}
