package modelo.xml;

public class DatosPooglins {
	//atributos del poogling
	private String posicionX;
	private String posicionY;
	private String vida;
	private String nombreHabilidad;
	private String estadoHabilidad;
	
	//atributos de movimiento
	private String direccionMovimiento;
	private String cantidadDePasos;
	private String contar;
	private String quietoEnDireccion;
	private String velocidad;
	
	
	public String getCantidadDePasos() {
		return cantidadDePasos;
	}
	public void setCantidadDePasos(String cantidadDePasos) {
		this.cantidadDePasos = cantidadDePasos;
	}
	public String getContar() {
		return contar;
	}
	public void setContar(String contar) {
		this.contar = contar;
	}
	public String getDireccionMovimiento() {
		return direccionMovimiento;
	}
	public void setDireccionMovimiento(String direccionMovimiento) {
		this.direccionMovimiento = direccionMovimiento;
	}
	public String getPosicionX() {
		return posicionX;
	}
	public void setPosicionX(String posicionX) {
		this.posicionX = posicionX;
	}
	public String getPosicionY() {
		return posicionY;
	}
	public void setPosicionY(String posicionY) {
		this.posicionY = posicionY;
	}
	public String getQuietoEnDireccion() {
		return quietoEnDireccion;
	}
	public void setQuietoEnDireccion(String quietoEnDireccion) {
		this.quietoEnDireccion = quietoEnDireccion;
	}
	public String getVelocidad() {
		return velocidad;
	}
	public void setVelocidad(String velocidad) {
		this.velocidad = velocidad;
	}
	public String getVida() {
		return vida;
	}
	public void setVida(String vida) {
		this.vida = vida;
	}
	public String getEstadoHabilidad() {
		return estadoHabilidad;
	}
	public void setEstadoHabilidad(String estadoHabilidad) {
		this.estadoHabilidad = estadoHabilidad;
	}
	public String getNombreHabilidad() {
		return nombreHabilidad;
	}
	public void setNombreHabilidad(String nombreHabilidad) {
		this.nombreHabilidad = nombreHabilidad;
	}
}
