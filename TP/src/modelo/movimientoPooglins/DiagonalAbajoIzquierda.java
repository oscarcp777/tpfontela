package modelo.movimientoPooglins;

import modelo.propiedadesDeElementos.Posicion;

public class DiagonalAbajoIzquierda extends Direccion{
	
	private static DiagonalAbajoIzquierda instance = new DiagonalAbajoIzquierda();
	
	private DiagonalAbajoIzquierda(){
	
	}
	
	public static DiagonalAbajoIzquierda getInstance(){
		
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
		return posicion.obtenerPosicionSiguienteIzquierda().obtenerPosicionSiguienteAbajo();
	}

}
