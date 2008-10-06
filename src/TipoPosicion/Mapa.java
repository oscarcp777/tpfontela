package TipoPosicion;

import Utilidades.Constants;


public class Mapa {
	private Posicionable[][] posicionable;
	
	public Mapa(){
		posicionable = new Posicionable[Constants.MAX][Constants.MAX];
	}

	public Posicionable[][] getPosicionable() {
		return posicionable;
	}

	public void setPosicionable(Posicionable[][] posicionable) {
		this.posicionable = posicionable;
	}
}
