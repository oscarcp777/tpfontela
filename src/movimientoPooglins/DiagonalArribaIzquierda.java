package movimientoPooglins;

import propiedadesDeElementos.Posicion;

public class DiagonalArribaIzquierda extends Direccion{

	private static DiagonalArribaIzquierda instance = new DiagonalArribaIzquierda();
	
	private DiagonalArribaIzquierda(){
	
	}
	
	public static DiagonalArribaIzquierda getInstance(){
		
		return instance;
	}
	
	@Override
	public Direccion cambiarDireccion() {
		// TODO Auto-generated method stub
		
		return Izquierda.getInstance();
	}

	@Override
	public Posicion siguientePosicionEnDireccion(Posicion posicion) {
		// TODO Auto-generated method stub
		return posicion.obtenerPosicionSiguienteIzquierda().obtenerPosicionSiguienteArriba();
	}

}
