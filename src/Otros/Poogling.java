package Otros;

import TipoHabilidades.Habilidad;
import TipoPosicion.Posicion;
import TipoPosicion.Posicionable;
import TipoPosicion.Velocidad;

public class Poogling extends Posicionable{

	private Habilidad habilidad;
	private Vida vida;
	private Velocidad velocidad;
	private SentidoMovimiento sentido;
	
	public Velocidad getVelocidad() {
		return velocidad;
	}

	public void setVelocidad(Velocidad velocidad) {
		this.velocidad = velocidad;
	}

	public Vida getVida() {
		return vida;
	}

	public void setVida(Vida vida) {
		this.vida = vida;
	}
		
	@Override
	public int compareTo(Object arg0) {
		// TODO Auto-generated method stub
		return 0;
	}

	public void setHabilidad(Habilidad habilidad) {
		this.habilidad = habilidad;
	}

	public Habilidad getHabilidad() {
		return habilidad;
	}
		
	public void asignarPosicion(Posicion posicion,SentidoMovimiento sentido){
		
	}
}
