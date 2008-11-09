package elementosDelMapa;

import mapaDeJuego.Mapa;
import propiedadesDeElementos.Posicion;
import habilidadesPooglins.Habilidad;
import utilitarios.Constants;

public class Roca extends Terreno{

	
	//Constructor por defecto
	public Roca(){
		
	}
	
	public Roca(Posicion posicion){
		asignarPosicion(posicion);
	
	}

	@Override
	public String obtenerNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreTerrenos.ROCA;
	}

	@Override
	public void aplicar(Habilidad habilidad, Mapa mapa, Poogling poogling) {
		// TODO Auto-generated method stub
		
	}
	
	public void colisionarPoogling(Poogling poogling) {
		
		if((this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteAbajo())==
			Constants.ValorComparador.IGUAL) && (poogling.cantidadDePasosEnDireccion()==Constants.PooglinAlVacio.CANTIDAD_PASOS_AIRE_MUERE)) 
						
			poogling.quitarVida();
	
		if(this.obtenerPosicion().compareTo(poogling.siguientePosicion())==
			Constants.ValorComparador.IGUAL)
				
		    poogling.cambiarDireccionDeMovimiento();
		
		
		/*el if anterior seguido de esto && !poogling.isConHabilidad()||
		(poogling.isConHabilidad()&& 
		!poogling.habilidadAplicada().equalsIgnoreCase(Constants.NombreHabilidades.RAYO_LASER) &&
		!poogling.habilidadAplicada().equalsIgnoreCase(Constants.NombreHabilidades.TALADRO_ULTRASONICO)))*/
	}

}
