package TipoTerrenos;

import Otros.Poogling;
import Otros.Vida;

import TipoHabilidades.Habilidad;
import TipoPosicion.Estatico;
import TipoPosicion.Posicionable;


public abstract class Terreno extends Posicionable implements Estatico{
	
	private Vida vida;

	
	
	//colisiona el poogling contra el terreno,
	//si es fuego, se quema y le saca vidas
	public abstract void colisionPoogling(Poogling poogling);
	
	public abstract void aplicarHabilidad(Habilidad habilidad);

	public void setVida(Vida vida) {
		this.vida = vida;
	}

	public Vida getVida() {
		return vida;
	}

	
	
	
	public abstract void aplicarAdinamico(Poogling poogling);
	
	
	

	
	
	
}
