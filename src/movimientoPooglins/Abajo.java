package movimientoPooglins;

import propiedadesDeElementos.Posicion;

import com.sun.net.ssl.internal.ssl.Debug;


public class Abajo extends Direccion{

	private static Abajo instance = new Abajo();
	
	private Abajo(){
		resetearPasosEnDireccion();
	}
	
	//devuelve una unica instancia por ser singleton
	public static Abajo getInstance(){
		return instance;
	}
	
	@Override
	public Direccion cambiarDireccion() {
		// TODO Auto-generated method stub
		resetearPasosEnDireccion();
		return Derecha.getInstance();
	}

	@Override
	public Posicion siguientePosicionEnDireccion(Posicion posicion) {
		darUnPasoEnDireccion();
		return posicion.obtenerPosicionSiguienteAbajo();
	}
	

}
