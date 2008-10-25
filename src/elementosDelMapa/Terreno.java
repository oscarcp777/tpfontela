package elementosDelMapa;

import propiedadesDeElementos.Colisionable;
import propiedadesDeElementos.Posicionable;
import propiedadesDeElementos.Vida;
import habilidadesPooglins.Habilidad;



public abstract class Terreno extends Posicionable implements Colisionable{
	
	private Vida vida;

	
	
	//colisiona el poogling contra el terreno,
	public void colisionarPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		poogling.getMovimiento().cambiarMovimiento();
	}
	
	public abstract void aplicarHabilidad(Habilidad habilidad);

	public void setVida(Vida vida) {
		this.vida = vida;
	}

	public Vida getVida() {
		return vida;
	}

	
	
}
