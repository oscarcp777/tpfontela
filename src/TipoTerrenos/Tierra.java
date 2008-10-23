package TipoTerrenos;

import Otros.Poogling;
import TipoHabilidades.Habilidad;
import TipoPosicion.Posicion;
import Utilidades.Constants;

public class Tierra extends Terreno{

	//Constructor por defecto
	public Tierra(){
		
	}
	
	public Tierra(Posicion posicion){
		asignarPosicion(posicion);
	}
	
	@Override
	public void aplicarHabilidad(Habilidad habilidad) {
		
		
	}

}
