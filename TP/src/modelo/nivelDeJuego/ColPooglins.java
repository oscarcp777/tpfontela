package modelo.nivelDeJuego;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import modelo.elementosDelMapa.Poogling;
import modelo.propiedadesDeElementos.Posicionable;


public class ColPooglins{

	private List colPooglin;
	
	public ColPooglins(){
		colPooglin=new ArrayList();
	}
	
	public ColPooglins(List colPooglin){
		this.colPooglin=colPooglin;
	}
	
	public boolean estaVacia(){
		return colPooglin.isEmpty(); 	
	}

	public void agregarPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		colPooglin.add(poogling);
	}

	public boolean borrarPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		return colPooglin.remove(poogling);
	}

	public Poogling obtenerPoogling(int pos) {
		// TODO Auto-generated method stub
		return (Poogling)colPooglin.get(pos);
	}

	public int tamanio() {
		// TODO Auto-generated method stub
		return colPooglin.size();
	}

	public Iterator iterator() {
		// TODO Auto-generated method stub
		return colPooglin.iterator();
	}
	
	public List obtenerTodos(){
		List otraColeccion = new ArrayList();
		otraColeccion.addAll(colPooglin);
		colPooglin.removeAll(colPooglin);
		return otraColeccion;
	}
	
}
