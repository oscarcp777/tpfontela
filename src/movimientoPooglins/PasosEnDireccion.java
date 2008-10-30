package movimientoPooglins;

public class PasosEnDireccion {

	private int cantidadDePasos;
	private boolean quietoEnDireccion;
	
	public PasosEnDireccion(){
		this.cantidadDePasos = 0;
		quietoEnDireccion = false;
	}
	
	public void darPasosEnDireccion(int cantidadDePasos){
		this.cantidadDePasos += cantidadDePasos;
	}
	
	public void setQuietoEnDireccion(boolean quietoEnDireccion){
		this.quietoEnDireccion = quietoEnDireccion;
	}
	
	public boolean getQuietoEnDireccion(){
		return quietoEnDireccion;
	}
	
	public int cantidadDePasosEnDireccion(){
		return cantidadDePasos;
	}
	
	public void inicializarCantidadDePasos(){
		cantidadDePasos = 0;
	}
	
}
