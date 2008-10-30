package habilidadesPooglins;
import elementosDelMapa.Poogling;
import elementosDelMapa.Terreno;

public class PlatilloVolador extends Habilidad{

	
	/*hace que el pooglin "atraviese" bloques de aire (en direccion 
	 * hacia abajo) hasta que se choque con algun otro bloque
	 * diferente de aire
	 
	 * ver que si el pooglin baja mas de 5 bloques de aire
	 * sin tener un platillo volador, se muere
	 */
	@Override
	public void aplicar(Poogling poogling) {
		poogling.validezMovimiento(false);			
	}

	@Override
	public void aplicar(Terreno terreno) {
		// TODO Auto-generated method stub
		
	}






	
}
