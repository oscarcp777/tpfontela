package TipoTerrenos;

import Otros.Poogling;
import TipoHabilidades.Habilidad;
import TipoPosicion.Posicion;
import Utilidades.Constants;

public class Roca extends Terreno{

	
	//Constructor por defecto
	public Roca(){
		
	}
	
	public Roca(Posicion posicion){
		asignarPosicion(posicion);
	}
	
	@Override
	public boolean colisionPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		return true;
	}


	@Override
	public void aplicarHabilidad(Habilidad habilidad) {
		// TODO Auto-generated method stub
		
	}

	

}
