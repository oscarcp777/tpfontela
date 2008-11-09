package FabricaHabilidades;

import habilidadesPooglins.Habilidad;

public abstract class FabricaHabilidades {

	private Habilidad habilidad;
		
	public abstract Habilidad crear();

	public abstract String obtenerNombre();
	
	public void operacion (){
		habilidad = crear();
	}
	
}
