package modelo.movimientoPooglins;

public class PasosEnDireccion {

	private int cantidadDePasos;
	private boolean quietoEnDireccion;
	private boolean contar;
	
	public PasosEnDireccion(){
		this.cantidadDePasos = 0;
		quietoEnDireccion = false;
		contar = true;
	}
		
	public void darPasosEnDireccion(int cantidadDePasos){
		if (contar())
		this.cantidadDePasos+=cantidadDePasos;
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
	
	public void contarPasosEnDireccion(boolean contar){
		this.contar=contar;
	}
	
	public boolean contar(){
		return contar;
	}
	
}
