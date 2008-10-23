package fabricas;

import Otros.Abajo;
import Otros.Direccion;
import TipoPosicion.Posicion;
import TipoTerrenos.Terreno;

public class Movimiento {
	private Posicion posicion; //posicion donde esta parado el pooglin
	private Posicion posicionSiguiente; //posicion siguiente para ver los terrenos a 
										//los costados del pooglin
	private Direccion direccion;
		
	public Movimiento(Posicion posicionInicial){
		posicion = posicionInicial;
		posicionSiguiente = new Posicion();
		posicion.posicionMelliza(posicionSiguiente); //a la posicionSiguiente le paso el contenido de posicion
		direccion = new Abajo(); //direccion inicial
	}
	
	public void mover(){
		direccion.siguientePosicion(posicion);
	}
	
	public void cambiarMovimiento(){
		direccion=direccion.cambiarDireccion();
	}
	
	public Posicion verPosicionSiguiente(){
		posicion.posicionMelliza(posicionSiguiente); //hago una copia de la posicion del pooglin actual
		direccion.siguientePosicion(posicionSiguiente);
		return posicionSiguiente;
	}
	
	
	public Posicion verPosicionAbajo(){
		Posicion posicionAbajo = new Posicion();
		posicionSiguiente.posicionMelliza(posicionAbajo);
		direccion.verPosicionAbajo(posicionAbajo);
		return posicionAbajo;
	}

	public Posicion getPosicion() {
		return posicion;
	}
	
}
