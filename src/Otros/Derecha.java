package Otros;

import TipoPosicion.Posicion;

public class Derecha implements Direccion {

private Posicion posicion;

	public Derecha(Posicion posicion) {
		
		// TODO Auto-generated constructor stub
		this.posicion = posicion;
		
	}

	@Override
	public void siguientePosicion(Posicion posicion) {
		// TODO Auto-generated method stub
		
		posicion.incrementarX();

	}

	@Override
	public Direccion cambiarDireccion(Posicion posicion) {
		// TODO Auto-generated method stub
		return new Izquierda(posicion);
	}

}
