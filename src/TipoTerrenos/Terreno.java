package TipoTerrenos;

import Otros.Poogling;
import Otros.Vida;
import Otros.SentidoMovimiento;
import TipoHabilidades.Habilidad;
import TipoPosicion.Posicionable;


public abstract class Terreno extends Posicionable{
	
	private Vida vida;
	private String nombre;
	
	public abstract boolean movimientoPooglingValido(Poogling poogling);
	
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
	
	public abstract String getNombre();
	
	public abstract void darSentidoMovimiento(Poogling poogling); 

	
	
	
}
