package Otros;

import com.sun.net.ssl.internal.ssl.Debug;

import TipoPosicion.Posicion;

public class Abajo implements Direccion{

	public Abajo(){
		
		
	}
	
	@Override
	public Direccion cambiarDireccion() {
		// TODO Auto-generated method stub
		return new Derecha();
	}

	@Override
	public void siguientePosicion(Posicion posicion) {
		// TODO Auto-generated method stub
		posicion.incrementarY(); //baja una fila
		
				
	}

	@Override
	public boolean verPosicionAbajo(Posicion posicion) {
		// TODO Auto-generated method stub
		//devuelve false pues la posicion de abajo se obtiene con el metodo
		//siguientePosicion
		siguientePosicion(posicion);
		return true;
	}
	

}
