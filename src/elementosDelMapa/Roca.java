package elementosDelMapa;

import propiedadesDeElementos.Posicion;
import habilidadesPooglins.Habilidad;
import utilitarios.Constants;

public class Roca extends Terreno{

	
	//Constructor por defecto
	public Roca(){
		setNombreTerreno(Constants.NombreTerreno.ROCA);
	}
	
	public Roca(Posicion posicion){
		asignarPosicion(posicion);
		setNombreTerreno(Constants.NombreTerreno.ROCA);
	}

}
