package movimientoPooglins;

import propiedadesDeElementos.Posicion;

public class Derecha extends Direccion {

	private static Derecha instance=new Derecha();
	
	private Derecha() {
		resetearPasosEnDireccion();
	}

	//devuelve una unica instancia por ser singleton
	public static Derecha getInstance(){
		return instance;
	}
	
	@Override
	public Direccion cambiarDireccion() {
		// TODO Auto-generated method stub
		resetearPasosEnDireccion();
		return Izquierda.getInstance();
	}
	
	@Override
	public Posicion siguientePosicionEnDireccion(Posicion posicion) {
		if(!quietoEnDireccion())
		darUnPasoEnDireccion();
		return posicion.obtenerPosicionSiguienteDerecha();		
	}

}
