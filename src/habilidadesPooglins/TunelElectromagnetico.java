package habilidadesPooglins;

import propiedadesDeElementos.Posicion;
import utilitarios.Constants;
import elementosDelMapa.Poogling;
import elementosDelMapa.Terreno;

public class TunelElectromagnetico extends Habilidad{

	@Override
	public void aplicar(Poogling poogling) {
		
		Posicion posicionSigAlPooglinDerecha = poogling.siguientePosicion().obtenerPosicionSiguienteDerecha();
		if(posicionSigAlPooglinDerecha.compareTo(poogling.obtenerPosicion())==
		   Constants.ValorComparador.IGUAL){ //El pooglin se esta moviendo a la derecha, por lo que se pondra al lado dicho tunel
			poogling.asignarPosicion(posicionSigAlPooglinDerecha.obtenerPosicionSiguienteDerecha());
			poogling.asignarPosicion(poogling.obtenerPosicion().obtenerPosicionSiguienteArriba().obtenerPosicionSiguienteArriba());
		}else{
			poogling.asignarPosicion(poogling.obtenerPosicion().obtenerPosicionSiguienteIzquierda().obtenerPosicionSiguienteIzquierda());	
			poogling.asignarPosicion(poogling.obtenerPosicion().obtenerPosicionSiguienteArriba().obtenerPosicionSiguienteArriba());
		}
		
	}

	@Override
	public void aplicar(Terreno terreno) {
		// TODO Auto-generated method stub
		
	}

	

}
