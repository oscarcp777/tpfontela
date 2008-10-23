package TipoTerrenos;

import Otros.Poogling;
import Otros.Vida;

import TipoHabilidades.Habilidad;
import TipoPosicion.Estatico;
import TipoPosicion.Posicionable;
import Utilidades.Constants;


public abstract class Terreno extends Posicionable implements Estatico{
	
	private Vida vida;

	
	
	//colisiona el poogling contra el terreno,
	public boolean colisionPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		if(this.obtenerPosicion().compareTo(poogling.getMovimiento().verPosicionSiguiente())==Constants.ValorComparador.IGUAL){
		poogling.getMovimiento().cambiarMovimiento();
		return true;
		}
		return false;
	}
	
	public abstract void aplicarHabilidad(Habilidad habilidad);

	public void setVida(Vida vida) {
		this.vida = vida;
	}

	public Vida getVida() {
		return vida;
	}

	
	
}
