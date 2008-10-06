package Otros;

import java.util.ArrayList;
import java.util.List;

import TipoPosicion.Posicionable;

public class Poogling extends Posicionable{

	private List habilidades;
	private Vida vida;
	
	public Poogling(){
		habilidades = new ArrayList();
	}
	
	public List getHabilidades() {
		return habilidades;
	}

	public void setHabilidades(List habilidades) {
		this.habilidades = habilidades;
	}
	
}
