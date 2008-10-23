package Otros;


import TipoPosicion.Posicion;

public class InfoNivel {
	private Posicion posicionNaveIngreso;
	private Posicion posicionNaveEscape;
	private ColPooglins colPooglins;
	private ColTerreno colTerreno;
	private DimensionTerreno dimensionTerreno;
	
	/** LEVANTA ESTA INFO DE UN XML **/
	
	public InfoNivel(Posicion posNaveIngreso, Posicion posNaveEscape, ColPooglins colPooglins, ColTerreno colTerr,DimensionTerreno dimensionTerr){
		this.posicionNaveIngreso = posNaveIngreso;
		this.posicionNaveEscape = posNaveEscape;
		this.colPooglins = colPooglins;
		this.colTerreno = colTerr;
		this.dimensionTerreno=dimensionTerr;
		
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

	public DimensionTerreno getDimensionTerreno() {
		return dimensionTerreno;
	}

}
