package modelo.xml;

import java.util.List;

public class DatosNave {

	private String coordenadaX;
	private String coordenadaY;
	private String cantidadPooglins;
	private String cantidadVidasPooglins;
	private List<DatosPooglins> pooglins;
	
	public List<DatosPooglins> getPooglins() {
		return pooglins;
	}
	public void setPooglins(List<DatosPooglins> pooglins) {
		this.pooglins = pooglins;
	}
	public String getCantidadVidasPooglins() {
		return cantidadVidasPooglins;
	}
	public void setCantidadVidasPooglins(String cantidadVidasPooglins) {
		this.cantidadVidasPooglins = cantidadVidasPooglins;
	}
	public String getCoordenadaX() {
		return coordenadaX;
	}
	public void setCoordenadaX(String coordenadaX) {
		this.coordenadaX = coordenadaX;
	}
	public String getCoordenadaY() {
		return coordenadaY;
	}
	public void setCoordenadaY(String coordenadaY) {
		this.coordenadaY = coordenadaY;
	}
	public String getCantidadPooglins() {
		return cantidadPooglins;
	}
	public void setCantidadPooglins(String cantidadPooglins) {
		this.cantidadPooglins = cantidadPooglins;
	}
}
