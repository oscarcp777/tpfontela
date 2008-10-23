package TipoTerrenos;

import Otros.Poogling;
import Otros.Vida;
import TipoHabilidades.Habilidad;
import TipoPosicion.Posicion;
import Utilidades.Constants;

public class AgujeroNegro extends Terreno{

	//Constructor por defecto
	public AgujeroNegro(){
		
	}
	
	public AgujeroNegro(Posicion posicion){
		asignarPosicion(posicion);
	}
	
	@Override
	public boolean colisionPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		poogling.setVida(new Vida(0));
		return true;
	}



	@Override
	public void aplicarHabilidad(Habilidad habilidad) {
		// TODO Auto-generated method stub
		
	}
	

}
