package movimientoPooglins;

public class PasosEnDireccion {

	private int cantidadDePasos;
	
	public PasosEnDireccion(){
		this.cantidadDePasos = 0;
	}
	
	public void darPasosEnDireccion(int cantidadDePasos){
		this.cantidadDePasos += cantidadDePasos;
	}
	
	public int cantidadDePasosEnDireccion(){
		return cantidadDePasos;
	}
	
	public void inicializarCantidadDePasos(){
		cantidadDePasos = 0;
	}
	
}
