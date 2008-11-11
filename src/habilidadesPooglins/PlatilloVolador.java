package modelo.habilidadesPooglins;
import modelo.elementosDelMapa.Poogling;
import modelo.elementosDelMapa.Terreno;
import modelo.mapaDeJuego.Mapa;
import modelo.movimientoPooglins.Abajo;
import modelo.propiedadesDeElementos.Posicion;
import modelo.utilitarios.Constants;

public class PlatilloVolador extends Habilidad{
	
	public PlatilloVolador() {
		estadoHabilidad = new EstadoHabilidad();
		estadoHabilidad.activarHabilidad();
	}

	/*hace que el pooglin "atraviese" bloques de aire (en direccion 
	 * hacia abajo) hasta que se choque con algun otro bloque
	 * diferente de aire
	 
	 * ver que si el pooglin baja mas de 5 bloques de aire
	 * sin tener un platillo volador, se muere
	 */
	@Override
	public void aplicarApooglin(Mapa mapa, Poogling poogling,Terreno terreno) {
		
		if(terreno.obtenerNombre().compareToIgnoreCase(Constants.NombreTerrenos.AIRE)==Constants.ValorComparador.IGUAL &&
		   terreno.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteAbajo())==Constants.ValorComparador.IGUAL){
			poogling.contarPasos(false);
			poogling.redireccionar(Abajo.getInstance());		
		}else if(poogling.siguientePosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteAbajo())
		   !=Constants.ValorComparador.IGUAL){ 	   //si la siguiente posicion no es abajo, el pooglin podra caminar hacia los costados
			estadoHabilidad.desactivarHabilidad(); //el poogling dejo el platillo volador porque llego a tierra
			poogling.contarPasos(true); //el pooglin se bajo del platillo y vuelve a contar los pasos en esa direccion
		}
	}

	@Override
	public String getNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreHabilidades.PLATILLO_VOLADOR;
	}

	@Override
	public void aplicarAterreno(Mapa mapa, Terreno terreno, Poogling poogling) {
		// TODO Auto-generated method stub
		
	}






	
}
