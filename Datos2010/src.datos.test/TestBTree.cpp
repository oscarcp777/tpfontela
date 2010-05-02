/*
 * TestBTree.cpp
 *
 *  Created on: 27/04/2010
 *      Author: Santiago
 */

#include "TestBTree.h"
#include "../src.datos.utils/ParserInput.h"
#include "../src.datos.storage/TextFile.h"

TestBTree::TestBTree() {
}

TestBTree::~TestBTree() {
}

/**
 * Test que evalúa el método insert del BTree, crea un nuevo árbol y le ingresa una serie de datos
 * preparados para que su resultante en los nodos hojas quede ordenado alfabéticamente, también
 * valida ingresos de igual clave, e ingresos con datos que superan el máximo permitido para un
 * tamaño de bloque dado
 * En caso de querer ingresar mas elementos usar claves como por ejemplo BB o FD y usar alguna clave
 * libre que corresponda a su orden alfabético
 *
 * @param fileName nombre del archivo a ser creado
 * @param blockSize tamaño de bloque del archivo
 */
void TestBTree::runTestInsert(string fileName, int blockSize){

	BPlusTree<int> bt(blockSize);
	bt.create(fileName,ios::out);
	bt.print("files/input.btree.dat");

	try{
	/*
	 * Inserta los datos provenientes de un archivo input.btree.dat.
	 * Con este conjunto de datos el secuence set tiene
	 * que quedar ordenado alfabéticamente
	 */
		fstream file;
		file.open("files/input.btree.dat3",ios::in|ios::out);
		ParserInput* parser = new ParserInput();
		string line;

		while(!file.eof()){
			getline(file,line);
			if(line.length()!=0){
				parser->parser(line);
				if(bt.insert(parser->getKey(),parser->getData().c_str())){
					cout << "Inserto el dato con la clave = " << parser->getKey() << endl;
				}else{
					cout << "No se inserto el dato " << parser->getKey() << endl;
				}
			}
		}
		file.close();

	}catch (string& e){
			cerr << e << endl;
	}

	bt.print("files/arbolAltas.txt");
	bt.close();
}

/**
 * Test que evalúa el Secuence Set del BTree, abre un archivo existente y recorre sus claves
 *
 * @param fileName nombre del archivo a ser usado
 * @param blockSize tamaño de bloque del archivo
 */
void TestBTree::runTestSecuenceSet(string fileName, int blockSize){

	BPlusTree<int>* bt = new BPlusTree<int>(blockSize);
	try {
		bt->open(fileName,ios::in|ios::out);
		char* element = bt->getFirstElementSecuentSet();
		while( element != NULL){
			cout<< element << endl;
			element = bt->getNextElementSecuentSet();
		}
		bt->close();

	} catch (string& e){
		cerr << e << endl;
	}
}

/**
 * Test que evalúa el método remove del BTree
 */
void TestBTree::runTestRemove(string fileName, int blockSize){

	BPlusTree<int> bt(blockSize);
	/*
	 * Realizamos test de distinta índole, ya que segun que clave eliminemos
	 * el árbol estará en un estado u otro.
	 * Además cada vez que eliminemos una clave, ésta será ingresada nuevamente
	 * para tener el árbol original.
	 */
	try {

		bt.open(fileName,ios::in|ios::out);
		bt.print("files/salida");
		bt.remover(3);//P
		bt.remover(6);//U
		bt.remover(9);//J
		bt.remover(12);//R
		bt.remover(15);//L
		bt.remover(18);//L
		bt.remover(21);//L
		bt.remover(24);//
		bt.remover(27);//
		bt.remover(30);//L
		bt.remover(33);//L
		bt.remover(36);//L
		bt.remover(39);//L
		bt.remover(42);//L
		bt.remover(45);//L
		bt.remover(48);//L
		bt.remover(51);//L
		bt.remover(54);//L
    	bt.remover(57);//N
		bt.remover(60);//
		bt.remover(63);//Y
		bt.remover(66); //
		bt.remover(69);//W
		bt.remover(72);//I
		bt.remover(75);//K
		bt.remover(78);//K
		bt.remover(103);//P
		bt.remover(106);//U
		bt.remover(109);//J
		bt.remover(112);//R
		bt.remover(115);//L
		bt.remover(118);//L
		bt.remover(121);//L
		bt.remover(124);//L
		bt.remover(127);//L
		bt.remover(130);//L
		bt.remover(133);//L
		bt.remover(136);//L
		bt.remover(139);//L
		bt.remover(142);//L
		bt.remover(145);//L
		bt.remover(148);//L
		bt.remover(151);//L
		bt.remover(154);//L
		bt.remover(157);//N
		bt.remover(160);//X
		bt.remover(163);//Y
		bt.remover(166);//Z
		bt.remover(169);//W
		bt.remover(172);//I
		bt.remover(175);//K
		bt.remover(178);//K
		//bt.print("files/salida");
		bt.remover(203);//P
		bt.remover(206);//U
		bt.remover(209);//J
		bt.remover(212);//R
		bt.remover(215);//L
		bt.remover(218);//L
		bt.remover(221);//L
		bt.remover(224);//L
		bt.remover(227);//
		bt.remover(230);//L
		bt.remover(233);//L
		bt.remover(236);//L
		bt.remover(239);//L
		bt.remover(242);//L
		bt.remover(245);//L
		bt.remover(248);//L
		bt.remover(251);//L
		bt.remover(254);//L
    	bt.remover(257);//N
		bt.remover(260);//
		bt.remover(263);//Y
		bt.remover(266); //
		bt.remover(269);//W
		bt.remover(272);//I
		bt.remover(275);//K
		bt.remover(278);//K
		bt.remover(303);//P
		bt.remover(306);//U
		bt.remover(309);//J
		bt.remover(312);//R
		bt.remover(315);//L
		bt.remover(318);//L
		bt.remover(321);//L
		bt.remover(324);//L
		bt.remover(327);//L
		bt.remover(330);//L
		bt.remover(333);//L
		bt.remover(336);//L
		bt.remover(339);//L
		bt.remover(342);//L
		bt.remover(345);//L
		bt.remover(348);//L
		bt.remover(351);//L
		bt.remover(354);//L
		bt.remover(357);//N
		bt.remover(360);//X
		bt.remover(363);//Y
		bt.remover(366);//Z
		bt.remover(369);//W
		bt.remover(372);//I
		bt.remover(375);//K
		bt.remover(378);//K
		bt.remover(403);//P
		bt.remover(406);//U
		bt.remover(409);//J
		bt.remover(412);//R
		bt.remover(415);//L
		bt.remover(418);//L
		bt.remover(421);//L
		bt.remover(424);//L
		bt.remover(427);//
		bt.remover(430);//L
		bt.remover(433);//L
		bt.remover(436);//L
		bt.remover(439);//L
		bt.remover(442);//L
		bt.remover(445);//L
		bt.remover(448);//L
		bt.remover(451);//L
		bt.remover(454);//L
    	bt.remover(457);//N
		bt.remover(460);//
		bt.remover(463);//Y
		bt.remover(466); //
		bt.remover(469);//W
		bt.remover(472);//I
		bt.remover(475);//K
		bt.remover(478);//K
		bt.remover(503);//P
		bt.remover(506);//U
		bt.remover(509);//J
		bt.remover(512);//R
		bt.remover(515);//L
		bt.remover(518);//L
		bt.remover(521);//L
		bt.remover(524);//L
		bt.remover(527);//L
		bt.remover(530);//L
		bt.remover(533);//L
		bt.remover(536);//L
		bt.remover(539);//L
		bt.remover(542);//L
		bt.remover(545);//L
		bt.remover(548);//L
		bt.remover(551);//L
		bt.remover(554);//L
		bt.remover(557);//N
		bt.remover(560);//X
		bt.remover(563);//Y
		bt.remover(566);//Z
		bt.remover(569);//W
		bt.remover(572);//I
		bt.remover(575);//K
		bt.remover(578);//K
		bt.remover(603);//P
		bt.remover(606);//U
		bt.remover(609);//J
		bt.remover(612);//R
		bt.remover(615);//L
		bt.remover(618);//L
		bt.remover(621);//L
		bt.remover(624);//L
		bt.remover(627);//
		bt.remover(630);//L
		bt.remover(633);//L
		bt.remover(636);//L
		bt.remover(639);//L
		bt.remover(642);//L
		bt.remover(645);//L
		bt.remover(648);//L
		bt.remover(651);//L
		bt.remover(654);//L
    	bt.remover(657);//N
		bt.remover(660);//
		bt.remover(663);//Y
		bt.remover(666); //
		bt.remover(669);//W
		bt.remover(672);//I
		bt.remover(675);//K
		bt.remover(678);//K
		bt.remover(703);//P
		bt.remover(706);//U
		bt.remover(709);//J
		bt.remover(712);//R
		bt.remover(715);//L
		bt.remover(718);//L
		bt.remover(721);//L
		bt.remover(724);//L
		bt.remover(727);//L
		bt.remover(730);//L
		bt.remover(733);//L
		bt.remover(736);//L
		bt.remover(739);//L
		bt.remover(742);//L
		bt.remover(745);//L
		bt.remover(748);//L
		bt.remover(751);//L
		bt.remover(754);//L
		bt.remover(757);//N
		bt.remover(760);//X
		bt.remover(763);//Y
		bt.remover(766);//Z
		bt.remover(769);//W
		bt.remover(772);//I
		bt.remover(775);//K
		bt.remover(778);//K

	} catch (string& e){
		cerr << e << endl;
	}

}
/**
 * Test que evalúa el método remove del BTree
 */
void TestBTree::runTestRemoveRompe(string fileName, int blockSize){

	BPlusTree<int> bt(blockSize);
	/*
	 * Realizamos test de distinta índole, ya que segun que clave eliminemos
	 * el árbol estará en un estado u otro.
	 * Además cada vez que eliminemos una clave, ésta será ingresada nuevamente
	 * para tener el árbol original.
	 */
	try {

		bt.open(fileName,ios::in|ios::out);
		bt.remover(36);//N
		bt.remover(39);//N
		bt.remover(42);//N
    	bt.print("files/arbol/arbolBajas1.txt");
		bt.remover(24);//N
		bt.remover(27);//N
    	bt.remover(42);//N
    	bt.print("files/arbol/arbolBajas2.txt");
		bt.remover(69);//N
		bt.remover(72);//N
    	bt.remover(75);//N
    	bt.remover(78);//N
    	bt.print("files/arbol/arbolBajas3.txt");
		bt.remover(112);//N
		bt.remover(178);//N
		bt.remover(115);//N
		bt.print("files/arbol/arbolBajas4.txt");
		bt.remover(118);//N
		//ACA VUELA
    	bt.print("files/arbol/arbolBajas5.txt");

		bt.close();
		cout<<"todo bien"<<endl;

	} catch (string& e){
		cerr << e << endl;
	}

	catch (exception& e){
		 cerr << "exception caught: " << e.what() << endl;
		cout<<" se ha producido un error comuniquese con el administrador del sistema"<<endl;
	}

}
/*
 * Métodos que diferencian distintos caso de eliminación de una clave.
 *
 * El caso UNO consta de eliminar una clave que no es la mayor de ese nodo
 * y además no produce underflow. Es un caso básico en donde no influye en la
 * estructura del árbol. En este ejemplo eliminaremos la clave 9.
 *
 * Test OK
 */
void TestBTree::removeCaseOne(BPlusTree<int>* btree, int clave = 9){

	btree->remover(clave);
	btree->print("treeRemove1.txt");
}

/*
 * Eliminamos una clave que es la mayor dentro del nodo hoja,
 * sin provocar underflow en este nodo. En este ejemplo eliminamos la clave 21.
 *
 * Test OK
 */
void TestBTree::removeCaseTwo(BPlusTree<int>* btree, int clave = 21){

	btree->remover(clave);
	btree->print("treeRemove2.txt");

}
/*
 * Eliminamos una clave que no es la mayor dentro de la hoja y
 * al eliminarla produce underflow. Le pide una la clave menor al vecino
 * derecho si este no puede pasarle, porque este vecino entra en underflow, se la pide al izquierdo para equilibrar.
 * Para este ejemplo eliminamos la clave 27.
 * Aca se contemplan otros casos tambien ya que cuando el nodo entra en underflow, este le
 * pide una clave al hermano derecho pero este no se la da porque sino entraria en
 * underflow tambien. Por lo tanto le pide una clave al hermano derecho y este si le puede
 * prestar.
 *
 * Test NO OK.
 */
void TestBTree::removeCaseThree(BPlusTree<int>* btree, int clave = 27){

	btree->remover(clave);
	btree->print("treeRemove3.txt");
}
/*
 * Eliminamos una clave que se encuentra en la raiz. Para este caso
 * la clave a eliminar es la 66.
 *
 * Test NO OK
 */
void TestBTree::removeCaseFor(BPlusTree<int>* btree, int clave = 66){

	btree->remover(clave);
	btree->print("treeRemove4.txt");
}
