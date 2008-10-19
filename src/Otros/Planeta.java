package Otros;

import TipoPosicion.Mapa;


public class Planeta extends Mapa{
	
	private Nave naveEntrada;
	private Nave naveEscape;
	
	public Planeta(Nave naveEntrada,Nave naveEscape){
		//llamo al constructor del Mapa
		super();
		this.naveEntrada = naveEntrada;
		this.naveEscape = naveEscape;
	}
	
	public Nave getNaveEntrada() {
		return naveEntrada;
	}
	public void setNaveEntrada(Nave naveEntrada) {
		this.naveEntrada = naveEntrada;
	}
	public Nave getNaveEscape() {
		return naveEscape;
	}
	public void setNaveEscape(Nave naveEscape) {
		this.naveEscape = naveEscape;
	}
	
} 
