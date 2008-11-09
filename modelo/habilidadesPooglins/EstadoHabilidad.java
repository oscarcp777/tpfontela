package habilidadesPooglins;

public class EstadoHabilidad {

	private boolean estado;
	
	public EstadoHabilidad(){
		estado = false;
	}
	
	public void activarHabilidad(){
		estado = true;
	}
	
	public void desactivarHabilidad(){
		estado = false;
	}
		
	public boolean isActivadaHabilidad(){
		return estado;
	}
	
}
