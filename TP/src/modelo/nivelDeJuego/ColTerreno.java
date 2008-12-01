package modelo.nivelDeJuego;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import modelo.elementosDelMapa.Terreno;
import modelo.propiedadesDeElementos.Posicionable;






public class ColTerreno{
	
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

	public void agregarTerreno(Terreno terreno) {
		// TODO Auto-generated method stub
		colTerrenos.add(terreno);
	}

	public boolean borrarTerreno(Terreno terreno) {
		// TODO Auto-generated method stub
		return colTerrenos.remove(terreno);
	}

	public boolean eliminarTerreno(Terreno terreno) {
		// TODO Auto-generated method stub
		return colTerrenos.remove(terreno);
	}

	public boolean estaVacia() {
		// TODO Auto-generated method stub
		return colTerrenos.isEmpty();
	}

	public Terreno obtenerTerreno(int pos) {
		// TODO Auto-generated method stub
		return (Terreno)colTerrenos.get(pos);
	}
	
}

