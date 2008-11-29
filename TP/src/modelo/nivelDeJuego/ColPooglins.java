package modelo.nivelDeJuego;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import modelo.elementosDelMapa.Poogling;
import modelo.propiedadesDeElementos.Posicionable;


public class ColPooglins implements ColPosicionable{

	private List colPooglins;
	
	public ColPooglins(){
		colPooglins=new ArrayList();
	}
	
	public boolean estaVacia(){
		return colPooglins.isEmpty(); 	
	}

	public void agregarPosicionable(Posicionable posicionable) {
		// TODO Auto-generated method stub
		colPooglins.add(posicionable);
	}

	public boolean borrarPosicionable(Posicionable posicionable) {
		// TODO Auto-generated method stub
		return colPooglins.remove(posicionable);
	}

	public Poogling obtenerPosicionable(int pos) {
		// TODO Auto-generated method stub
		return (Poogling)colPooglins.get(pos);
	}

	public int tamanio() {
		// TODO Auto-generated method stub
		return colPooglins.size();
	}

	public Iterator iterator() {
		// TODO Auto-generated method stub
		return colPooglins.iterator();
	}
	
}
