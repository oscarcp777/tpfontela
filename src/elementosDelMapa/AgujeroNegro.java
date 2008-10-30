package elementosDelMapa;

import propiedadesDeElementos.Posicion;
import propiedadesDeElementos.Vida;
import habilidadesPooglins.Habilidad;
import utilitarios.Constants;

public class AgujeroNegro extends Terreno{

	//Constructor por defecto
	public AgujeroNegro(){
		setNombreTerreno(Constants.NombreTerreno.AGUJERO_NEGRO);
	}
	
	public AgujeroNegro(Posicion posicion){
		asignarPosicion(posicion);
		setNombreTerreno(Constants.NombreTerreno.AGUJERO_NEGRO);
	}
	
	//hace lo mismo que fuego
	@Override
	public void colisionarPoogling(Poogling poogling) {
		poogling.quitarVida();
	}



	@Override
	public void aplicarHabilidad(Habilidad habilidad) {
		// TODO Auto-generated method stub
		
	}
	

}
