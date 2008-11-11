package modelo.movimientoPooglins;

import modelo.propiedadesDeElementos.Posicion;

public class DiagonalArribaDerecha extends Direccion{

	private static DiagonalArribaDerecha instance = new DiagonalArribaDerecha();
	
	private DiagonalArribaDerecha(){
	
	}
	
	public static DiagonalArribaDerecha getInstance(){
		
		return instance;
	}
	
	@Override
	public Direccion cambiarDireccion() {
		// TODO Auto-generated method stub
		
		return Derecha.getInstance();
	}

	@Override
	public Posicion siguientePosicionEnDireccion(Posicion posicion) {
		return posicion.obtenerPosicionSiguienteDerecha().obtenerPosicionSiguienteArriba();
	}

}
