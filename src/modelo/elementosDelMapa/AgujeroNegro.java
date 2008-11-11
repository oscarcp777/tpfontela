package modelo.elementosDelMapa;

import modelo.habilidadesPooglins.Habilidad;
import modelo.mapaDeJuego.Mapa;
import modelo.propiedadesDeElementos.Posicion;
import modelo.propiedadesDeElementos.Vida;
import modelo.utilitarios.Constants;

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
