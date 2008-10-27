package movimientoPooglins;

import propiedadesDeElementos.Posicion;

public class Izquierda extends Direccion {
	
	private static Izquierda instance = new Izquierda();

	private Izquierda(){
		resetearPasosEnDireccion();
	}
	
	//devuelve una unica instancia por ser singleton
	public static Izquierda getInstance() {
		return instance;
	}

	@Override
	public Posicion siguientePosicionEnDireccion(Posicion posicion) {
		darUnPasoEnDireccion();
		return posicion.obtenerPosicionSiguienteIzquierda();
	}

	@Override
	public Direccion cambiarDireccion() {
		resetearPasosEnDireccion();
		return Derecha.getInstance(); 
	}
		
}
