package modelo.xml;

public class DatosTerreno {
	
	private String nombreTerreno;
	private String coordenadaX;
	private String coordenadaY;
	private String cantVidas;
	
	public String getNombreTerreno() {
		return nombreTerreno;
	}
	public void setNombreTerreno(String nombreTerreno) {
		this.nombreTerreno = nombreTerreno;
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
	public void setCantVidas(String cantVidas) {
		this.cantVidas = cantVidas;
	}
	public String getCantVidas() {
		return cantVidas;
	}
	
}
