package elementosDelMapa;

import propiedadesDeElementos.Posicion;
import habilidadesPooglins.Habilidad;
import utilitarios.Constants;

public class Tierra extends Terreno{

	//Constructor por defecto
	public Tierra(){
		setNombreTerreno(Constants.NombreTerreno.TIERRA);		
	}
	
	public Tierra(Posicion posicion){
		asignarPosicion(posicion);
		setNombreTerreno(Constants.NombreTerreno.TIERRA);
	}
	
}
