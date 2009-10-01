package modelo.entornoDeJuego;

import modelo.pooglins.Posicion;
/**
 * Clase: Interfaz Controlable.
 * 
 * */
public interface Controlable extends EjecutadorDeRondas {

	public void agregarPooglin(Posicion posInicial);
	public void agregarPooglin();
	
}
