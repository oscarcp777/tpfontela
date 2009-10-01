package controlador;

import modelo.pooglins.Posicion;

public class MarcoPosicion {

	private Posicion margenSupIzq;
	private Posicion margenInfIzq;
	private Posicion margenSupDer;
	private Posicion margenInfDer;
	
public MarcoPosicion(Posicion margenInfIzquierdo) {

	margenInfIzq = margenInfIzquierdo.copiar();
	margenSupIzq = new Posicion(margenInfIzquierdo.getX(),margenInfIzquierdo.getY() - ConstantesControlador.ALTURA_DEFAULT*ConstantesControlador.ALTURA_POOLGIN);
	margenInfDer = new Posicion(margenInfIzquierdo.getX()+ConstantesControlador.ANCHURA_DEFAULT,margenInfIzquierdo.getY());
	margenSupDer = new Posicion(margenInfIzquierdo.getX()+ConstantesControlador.ANCHURA_DEFAULT,margenInfIzquierdo.getY() - ConstantesControlador.ALTURA_DEFAULT*ConstantesControlador.ALTURA_POOLGIN);
}	

public boolean estaDentro(Posicion posicion){
	return ( posicion.getX()<= this.margenInfDer.getX() && posicion.getX()>= this.margenInfIzq.getX() 
				&& posicion.getY()<= this.margenInfDer.getY() && posicion.getY()>= this.margenSupDer.getY() );
}


}
