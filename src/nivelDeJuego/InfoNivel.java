package nivelDeJuego;


import propiedadesDeElementos.Posicion;

public class InfoNivel {
	private Posicion posicionNaveIngreso;
	private Posicion posicionNaveEscape;
	private ColPooglins colPooglins;
	private ColTerreno colTerreno;
		
	/** LEVANTA ESTA INFO DE UN XML **/
	
	public InfoNivel(Posicion posNaveIngreso, Posicion posNaveEscape, ColPooglins colPooglins, ColTerreno colTerr){
		this.posicionNaveIngreso = posNaveIngreso;
		this.posicionNaveEscape = posNaveEscape;
		this.colPooglins = colPooglins;
		this.colTerreno = colTerr;
	}

	public Posicion getPosicionNaveIngreso() {
		return posicionNaveIngreso;
	}

	public Posicion getPosicionNaveEscape() {
		return posicionNaveEscape;
	}

	public ColPooglins getColPooglins() {
		return colPooglins;
	}
	
	public ColTerreno getColTerreno() {
		return colTerreno;
	}

	public void setColTerreno(ColTerreno colTerreno) {
		this.colTerreno = colTerreno;
	}

}
