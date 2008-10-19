package TipoTerrenos;

import Otros.Poogling;
import TipoHabilidades.Habilidad;
import Utilidades.Constants;

public class Tierra extends Terreno{

	@Override
	public void colisionPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		
	}


	@Override
	public void aplicarHabilidad(Habilidad habilidad) {
		
		
	}

	@Override
	public void aplicarAdinamico(Poogling poogling) {
		// TODO Auto-generated method stub
		if(poogling.obtenerPosicion().posicionValidaLateral(this,poogling)){
			poogling.getDireccion().cambiarDireccion(poogling.obtenerPosicion());
		}
	}
	
	


}
