package modelo.nivelDeJuego;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import modelo.elementosDelMapa.Terreno;
import modelo.propiedadesDeElementos.Posicionable;






public class ColTerreno implements ColPosicionable{
	
	private List colTerrenos;
	
	public ColTerreno(){
		colTerrenos = new ArrayList();
	}
	
	public ColTerreno(List terrenos){
		colTerrenos=terrenos;
	}
		
	public int tamanio(){
		return colTerrenos.size();
	}
	
	public Iterator iterator(){
		return colTerrenos.iterator();
	}

	public void agregarPosicionable(Posicionable posicionable) {
		// TODO Auto-generated method stub
		colTerrenos.add(posicionable);
	}

	public boolean borrarPosicionable(Posicionable posicionable) {
		// TODO Auto-generated method stub
		return colTerrenos.remove(posicionable);
	}

	public boolean eliminarPosicionable(Posicionable posicionable) {
		// TODO Auto-generated method stub
		return colTerrenos.remove(posicionable);
	}

	public boolean estaVacia() {
		// TODO Auto-generated method stub
		return colTerrenos.isEmpty();
	}

	public Terreno obtenerPosicionable(int pos) {
		// TODO Auto-generated method stub
		return (Terreno)colTerrenos.get(pos);
	}
	
}

