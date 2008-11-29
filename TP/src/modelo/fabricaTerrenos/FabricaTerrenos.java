package modelo.fabricaTerrenos;

import modelo.elementosDelMapa.Terreno;


public abstract class FabricaTerrenos {
	
	private Terreno terreno;
			
	public abstract Terreno crear();

	public abstract String obtenerNombre();
		
	public void operacion (){
		terreno = crear();
	}
		
	
}
