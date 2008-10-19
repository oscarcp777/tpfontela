package Otros;

import TipoPosicion.Posicion;

public class Izquierda implements Direccion {

	
	private Posicion posicion;
	
	public Izquierda(Posicion posicion){
		this.posicion = posicion;
	}


	@Override
	public void siguientePosicion(Posicion posicion) {
		// TODO Auto-generated method stub
		posicion.decrementarX();

	}

	@Override
	public Direccion cambiarDireccion(Posicion posicion) {
		// TODO Auto-generated method stub
		return new Derecha(posicion);
	}

}
