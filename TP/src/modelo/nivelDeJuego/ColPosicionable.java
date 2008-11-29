package modelo.nivelDeJuego;

import java.util.Iterator;

import modelo.propiedadesDeElementos.Posicionable;

public interface ColPosicionable {

	public Posicionable obtenerPosicionable(int pos);		
	
	public void agregarPosicionable(Posicionable posicionable);
	
	public Iterator iterator();
		
	public boolean estaVacia(); 	
	
	public boolean borrarPosicionable(Posicionable posicionable);

	public int tamanio();	
	
}
