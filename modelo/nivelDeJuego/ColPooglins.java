package nivelDeJuego;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import elementosDelMapa.Poogling;

public class ColPooglins {

	private List colPooglins;
	
	public ColPooglins(){
		colPooglins=new ArrayList();
	}
	
	public Poogling obtenerPooglin(int pos){
		return (Poogling)colPooglins.remove(pos);
	}
	
	public void agregarPooglin(Poogling pooglin){
		colPooglins.add(pooglin);
	}
	
	public boolean eliminarPooglin(Poogling pooglin){
		return colPooglins.remove(pooglin);
	}
	
	public Iterator iterator(){
		return colPooglins.iterator();
	}
	
	public boolean estaVacia(){
		return colPooglins.isEmpty(); 	
	}
	
}
