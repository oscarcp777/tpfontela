package vista.utilitarias;

import modelo.pooglins.Posicion;

public class ConversorDeEscalas {
	
	private ConversorDeEscalas(){
		
	}

	public static Posicion ajustarEscala(Posicion pos){
		return new Posicion(pos.getX()*ConstantesVista.ANCHO_PARCELA, pos.getY()*ConstantesVista.ALTO_PARCELA);		
	}
	
	public static Posicion ajustarEscala(int x, int y){
		return new Posicion(x*ConstantesVista.ANCHO_PARCELA, y*ConstantesVista.ALTO_PARCELA);		
	}
	

}
