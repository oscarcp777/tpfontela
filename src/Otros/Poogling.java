package Otros;

import java.util.ArrayList;
import java.util.List;

import TipoPosicion.Posicionable;
import TipoPosicion.Velocidad;

public class Poogling extends Posicionable{

	private List habilidades;
	private Vida vida;
	private Velocidad velocidad;
	
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

	public Poogling(){
		habilidades = new ArrayList();
	}
	
	public List getHabilidades() {
		return habilidades;
	}

	public void setHabilidades(List habilidades) {
		this.habilidades = habilidades;
	}

	@Override
	public int compareTo(Object arg0) {
		// TODO Auto-generated method stub
		return 0;
	}
	
}
