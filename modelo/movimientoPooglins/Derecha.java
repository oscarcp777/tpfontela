package movimientoPooglins;

import propiedadesDeElementos.Posicion;

public class Derecha implements Direccion {

	static private Derecha instance=null;
	
	private Derecha() {
	
	}

	//devuelve una unica instancia por ser singleton
	public static Derecha getInstance(){
		if(instance==null)
			return new Derecha();
		else 
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
