package movimientoPooglins;

import propiedadesDeElementos.Posicion;

import com.sun.net.ssl.internal.ssl.Debug;


public class Abajo extends Direccion{

	private static Abajo instance = new Abajo();
		
	private Abajo(){
			
	}
	
	//devuelve una unica instancia por ser singleton
	public static Abajo getInstance(){
		return instance;
	}
	
	@Override
	public Direccion cambiarDireccion() {
		// TODO Auto-generated method stub
		
		return Derecha.getInstance();
	}

	@Override
	public Posicion siguientePosicionEnDireccion(Posicion posicion) {
		return posicion.obtenerPosicionSiguienteAbajo();
	}
	

}
