package modelo.movimientoPooglins;

import modelo.propiedadesDeElementos.Posicion;

public class Derecha extends Direccion {

	private static Derecha instance=new Derecha();
	
	private Derecha() {
		
	}

	//devuelve una unica instancia por ser singleton
	public static Derecha getInstance(){
		return instance;
	}
	
	@Override
	public Direccion cambiarDireccion() {
		// TODO Auto-generated method stub

		return Izquierda.getInstance();
	}
	
	@Override
	public Posicion siguientePosicionEnDireccion(Posicion posicion) {
		return posicion.obtenerPosicionSiguienteDerecha();
	}

}
