package modelo.movimientoPooglins;

import modelo.propiedadesDeElementos.Posicion;

public class DiagonalAbajoDerecha extends Direccion{
	
	private static DiagonalAbajoDerecha instance = new DiagonalAbajoDerecha();
	
	private DiagonalAbajoDerecha(){
	
	}
	
	public static DiagonalAbajoDerecha getInstance(){
		
		return instance;
	}
	
	@Override
	public Direccion cambiarDireccion() {
		// TODO Auto-generated method stub
		
		return Derecha.getInstance();
	}

	@Override
	public Posicion siguientePosicionEnDireccion(Posicion posicion) {
		// TODO Auto-generated method stub
		return posicion.obtenerPosicionSiguienteDerecha().obtenerPosicionSiguienteAbajo();
	}

}
