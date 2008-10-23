package Otros;

import TipoPosicion.Posicion;

public class Derecha implements Direccion {

	public Derecha() {
		// TODO Auto-generated constructor stub
	
	}

	//Si se movio a la derecha se chequeara luego si se puede avanzar a esa posicion mediante los terrenos
	//Si ya se movio a la derecha, se movera hacia abajo y se chequeara con que tipo de terreno esta parado 
	//el pooglin.
	public void siguientePosicion(Posicion posicion) {
		posicion.incrementarX();
	}
	
	@Override
	public Direccion cambiarDireccion() {
		// TODO Auto-generated method stub
		return new Izquierda();
	}
	
	public boolean verPosicionAbajo(Posicion posicion) {
		posicion.incrementarY();
		return true;
	}

}
