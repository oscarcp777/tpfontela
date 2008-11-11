package modelo.nivelDeJuego;


import modelo.FabricaHabilidades.FabricaHabilidades;
import modelo.propiedadesDeElementos.Posicion;

public class InfoNivel {
	private Posicion posicionNaveIngreso;
	private Posicion posicionNaveEscape;
	private ColPooglins colPooglins;
	private ColTerreno colTerreno;
	private ColFabricaHabilidades fabricaHabilidades;
		
	/** LEVANTA ESTA INFO DE UN XML **/
	
	public InfoNivel(Posicion posNaveIngreso, Posicion posNaveEscape, ColPooglins colPooglins, ColTerreno colTerr,ColFabricaHabilidades fabrica){
		this.posicionNaveIngreso = posNaveIngreso;
		this.posicionNaveEscape = posNaveEscape;
		this.colPooglins = colPooglins;
		this.colTerreno = colTerr;
		this.fabricaHabilidades = fabrica;
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

	public ColFabricaHabilidades getFabricaHabilidades() {
		return fabricaHabilidades;
	}

}
