package elementosDelMapa;

import habilidadesPooglins.Habilidad;
import mapaDeJuego.Mapa;
import movimientoPooglins.DiagonalArribaDerecha;
import movimientoPooglins.DiagonalArribaIzquierda;
import propiedadesDeElementos.Posicion;
import utilitarios.Constants;

public class Tunel extends Terreno{

	public Tunel(){
		
	}
	
	public Tunel(Posicion posicion){
		asignarPosicion(posicion);
	}
	
	@Override
	public void colisionarPoogling(Poogling poogling) {
		
		if (this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteArriba().obtenerPosicionSiguienteDerecha())==
			 Constants.ValorComparador.IGUAL) 
			poogling.redireccionar(DiagonalArribaDerecha.getInstance());
		else if (this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteArriba().obtenerPosicionSiguienteIzquierda())==
		   	 	Constants.ValorComparador.IGUAL)
			poogling.redireccionar(DiagonalArribaIzquierda.getInstance());
			
	}

	@Override
	public String obtenerNombre() {
		return Constants.NombreTerrenos.TUNEL;		
	}

	@Override
	public void aplicar(Habilidad habilidad, Mapa mapa, Poogling poogling) {
		// TODO Auto-generated method stub
		
	}
	

}
