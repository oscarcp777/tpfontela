package Otros;

import TipoPosicion.Mapa;

public class Planeta extends Mapa{

	private Nave naveEntrada;
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
	private Nave naveEscape;
} 
