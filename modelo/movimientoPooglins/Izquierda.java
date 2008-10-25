package movimientoPooglins;

import propiedadesDeElementos.Posicion;

public class Izquierda implements Direccion {
	
	static private Izquierda instance = null;

	private Izquierda(){
		
	}
	
	//devuelve una unica instancia por ser singleton
	public static Izquierda getInstance() {
		if (instance==null)
		return new Izquierda();
		else
			return instance;
	}

	@Override
	public Posicion siguientePosicionEnDireccion(Posicion posicion) {
		return posicion.obtenerPosicionSiguienteIzquierda();
	}

	@Override
	public Direccion cambiarDireccion() {
		return Derecha.getInstance(); 
	}
		
}
