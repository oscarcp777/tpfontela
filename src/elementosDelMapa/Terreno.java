package elementosDelMapa;

import propiedadesDeElementos.Colisionable;
import propiedadesDeElementos.Posicionable;
import propiedadesDeElementos.Vida;
import utilitarios.Constants;
import habilidadesPooglins.Habilidad;



public abstract class Terreno extends Posicionable implements Colisionable{
	
	private Vida vida;

	
	
	//colisiona el poogling contra tierra o roca,
	@Override
	public void colisionarPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		if(this.obtenerPosicion().compareTo(poogling.siguientePosicion())==
			Constants.ValorComparador.IGUAL) 
		poogling.cambiarDireccionDeMovimiento();
	}
	
	public abstract void aplicarHabilidad(Habilidad habilidad);

	public void setVida(Vida vida) {
		this.vida = vida;
	}

	public Vida getVida() {
		return vida;
	}

	
	
}
