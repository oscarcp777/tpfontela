package controlador;

import java.util.Iterator;
import java.util.LinkedList;

import modelo.pooglins.Posicion;

public class PooglinsEnJuego {

	private LinkedList<PooglinPosicion> lista;
	
public PooglinsEnJuego() {
	this.lista = new LinkedList<PooglinPosicion>();
}	

public void crearPooglinPosicion(int id, Posicion pos){
	this.lista.add(new PooglinPosicion(id,pos));
}

public void modificarPosicionPooglin(int id, Posicion pos){
	Iterator<PooglinPosicion> iter =  this.lista.iterator();
	boolean encontrado = false;
	while(iter.hasNext() || !encontrado ){
		PooglinPosicion pooglin = iter.next();
		if (pooglin.getIdPooglin() == id) {
			pooglin.setNuevaPosicion(pos);
			encontrado = true;
		}
	}
}
/*
 * Devuelve 0 si ningun pooglin fue cliqueado
 */
public int getPooglinCliqueado(Posicion pos){
	Iterator<PooglinPosicion> iter =  this.lista.iterator();
	while(iter.hasNext()){
		PooglinPosicion pooglin = iter.next();
		if (pooglin.estaDentro(pos)) {
			return pooglin.getIdPooglin();
		}
	}
	return 0;
}

public PooglinPosicion getPooglinPorId(int id){
	Iterator<PooglinPosicion> iter =  this.lista.iterator();
	while(iter.hasNext()){
		PooglinPosicion pooglin = iter.next();
		if (pooglin.getIdPooglin() == id) {
			return pooglin;
		}
	}
	return null;
}
}
