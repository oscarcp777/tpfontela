package elementosDelMapa;

import mapaDeJuego.Mapa;
import propiedadesDeElementos.Posicion;
import habilidadesPooglins.Habilidad;
import utilitarios.Constants;

public class Tierra extends Terreno{

	//Constructor por defecto
	public Tierra(){
			
	}
	
	public Tierra(Posicion posicion){
		asignarPosicion(posicion);
	}


	@Override
	public String obtenerNombre() {
		return Constants.NombreTerrenos.TIERRA;		
	}

	public void colisionarPoogling(Poogling poogling) {
		
		if((this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteAbajo())==
			Constants.ValorComparador.IGUAL) && (poogling.cantidadDePasosEnDireccion()==Constants.PooglinAlVacio.CANTIDAD_PASOS_AIRE_MUERE)) 
						
			poogling.quitarVida();
	
		else if(this.obtenerPosicion().compareTo(poogling.siguientePosicion())==
			Constants.ValorComparador.IGUAL && !poogling.quieto())
				
		    poogling.cambiarDireccionDeMovimiento();
		
	}
	
	public void cambiarPorAire(Mapa mapa){
		mapa.cambiarTerreno(new Aire(obtenerPosicion()));
	}

}
