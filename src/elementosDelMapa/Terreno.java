package modelo.elementosDelMapa;

import modelo.habilidadesPooglins.Habilidad;
import modelo.mapaDeJuego.Mapa;
import modelo.propiedadesDeElementos.Colisionable;
import modelo.propiedadesDeElementos.Posicion;
import modelo.propiedadesDeElementos.Posicionable;
import modelo.propiedadesDeElementos.Vida;
import modelo.utilitarios.Constants;



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
	
	//Para tierra y aire
	public void aplicar(Habilidad habilidad, Mapa mapa, Poogling poogling) {
		// TODO Auto-generated method stub
		habilidad.aplicarAterreno(mapa,this,poogling); //le aplica la habilidad rayoLaser o taladroUltrasonico (si el terreno es tierra)
													   // o congelamiento (si el terreno es aire, y a este terreno se lo cambiara por hielo).
		  											   	
		
	}
	
	public abstract String obtenerNombre();
	
}
