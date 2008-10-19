package TipoTerrenos;

import Otros.Poogling;

import TipoHabilidades.Habilidad;
import Otros.Vida;
import Utilidades.Constants;
public class Fuego extends Terreno{

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

