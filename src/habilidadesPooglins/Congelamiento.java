package habilidadesPooglins;

import elementosDelMapa.Poogling;
import elementosDelMapa.Terreno;

public class Congelamiento extends Habilidad{

	@Override
	public void aplicar(Poogling poogling) {
		// TODO Auto-generated method stub
		poogling.quitarVida();
		
		/*le quita vidas al pooglin (lo mata)y en esa 
		 * posicion se debe reemplazar el bloque de 
		 * aire (porque alli hay un pooglin) por un 
		 * bloque de hielo*/
		
		
		 
	}
	
	public void aplicar(Terreno terreno){
		
	}

	@Override
	public void aplicar(Terreno terreno) {
		// TODO Auto-generated method stub
		
	}

	
}
