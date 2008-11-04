package elementosDelMapa;

import mapaDeJuego.Mapa;
import propiedadesDeElementos.Posicion;
import propiedadesDeElementos.Vida;
import habilidadesPooglins.Habilidad;
import utilitarios.Constants;

public class AgujeroNegro extends Terreno{

	//Constructor por defecto
	public AgujeroNegro(){
	
	}
	
	public AgujeroNegro(Posicion posicion){
		asignarPosicion(posicion);
		
	}
	
	//hace lo mismo que fuego
	@Override
	public void colisionarPoogling(Poogling poogling) {
		poogling.quitarVida();
	}

	@Override
	public String obtenerNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreTerrenos.AGUJERO_NEGRO;
	}

	@Override
	public void aplicar(Habilidad habilidad, Mapa mapa, Poogling poogling) {
		// TODO Auto-generated method stub
		
	}
	
}
