package Otros;

import TipoPosicion.Posicion;

public class Izquierda implements Direccion {

	
	
	
	public Izquierda(){
		
	}


	@Override
	public void siguientePosicion(Posicion posicion) {
		// TODO Auto-generated method stub
		posicion.decrementarX();

	}

	@Override
	public Direccion cambiarDireccion() {
		// TODO Auto-generated method stub
		return new Derecha();
	}
	
	public boolean verPosicionAbajo(Posicion posicion) {
		posicion.incrementarY();
		return true;
	}

}
