package TipoTerrenos;

import Otros.Poogling;
import Otros.Vida;
import TipoHabilidades.Habilidad;
import Utilidades.Constants;

public class AgujeroNegro extends Terreno{

	@Override
	public void colisionPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		poogling.setVida(new Vida(0));
		
	}



	@Override
	public void aplicarHabilidad(Habilidad habilidad) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void aplicarAdinamico(Poogling poogling) {
		// TODO Auto-generated method stub
		if(poogling.obtenerPosicion().posicionValidaLateral(this, poogling)){
			colisionPoogling(poogling);
		}
		
		
	}


	
	

}
