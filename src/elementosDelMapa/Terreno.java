package elementosDelMapa;

import mapaDeJuego.Mapa;
import propiedadesDeElementos.Colisionable;
import propiedadesDeElementos.Posicion;
import propiedadesDeElementos.Posicionable;
import propiedadesDeElementos.Vida;
import utilitarios.Constants;
import habilidadesPooglins.Habilidad;



public abstract class Terreno extends Posicionable implements Colisionable{
	
	
	private Vida vida;
	
	//colisiona el poogling contra tierra o roca,
	@Override
	public void colisionarPoogling(Poogling poogling) {
		
		if((this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteAbajo())==
			Constants.ValorComparador.IGUAL) && (poogling.cantidadDePasosEnDireccion()==Constants.PooglinAlVacio.CANTIDAD_PASOS_AIRE_MUERE)) 
						
			poogling.quitarVida();
	
		if(this.obtenerPosicion().compareTo(poogling.siguientePosicion())==
			Constants.ValorComparador.IGUAL && !poogling.quieto())
				
		    poogling.cambiarDireccionDeMovimiento();
		
		
		/*el if anterior seguido de esto && !poogling.isConHabilidad()||
		(poogling.isConHabilidad()&& 
		!poogling.habilidadAplicada().equalsIgnoreCase(Constants.NombreHabilidades.RAYO_LASER) &&
		!poogling.habilidadAplicada().equalsIgnoreCase(Constants.NombreHabilidades.TALADRO_ULTRASONICO)))*/
	}
	
	public void setVida(Vida vida) {
		this.vida = vida;
	}

	public Vida getVida() {
		return vida;
	}
	
	public abstract void aplicar(Habilidad habilidad,Mapa mapa,Poogling poogling);
	
	public abstract String obtenerNombre();
	
}
