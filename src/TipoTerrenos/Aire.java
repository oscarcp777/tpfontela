package TipoTerrenos;

import Otros.Poogling;
import TipoHabilidades.Habilidad;
import TipoPosicion.Posicion;
import Utilidades.Constants;

public class Aire extends Terreno{
	
	//Constructor por defecto
	public Aire(){
		
	}
	
	public Aire(Posicion posicion){
		asignarPosicion(posicion);
	}
	
	public boolean movimientoPooglingValido(Poogling poogling){
		return true;
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
