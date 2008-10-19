package Otros;

import com.sun.net.ssl.internal.ssl.Debug;

import TipoPosicion.Posicion;

public class Abajo implements Direccion{

	private Posicion posicion;
	
	public Abajo(Posicion posicion){
		
		this.posicion = posicion;
	}
	
	@Override
	public Direccion cambiarDireccion(Posicion posicion) {
		// TODO Auto-generated method stub
		return new Derecha(posicion);
		
	}

	@Override
	public void siguientePosicion(Posicion posicion) {
		// TODO Auto-generated method stub
		posicion.decrementarY();
		
				
	}

	



}
