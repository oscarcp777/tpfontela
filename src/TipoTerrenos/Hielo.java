package TipoTerrenos;

import Otros.Poogling;

import TipoHabilidades.Habilidad;
import Utilidades.Constants;

import TipoPosicion.Velocidad;

public class Hielo extends Terreno{

	@Override
	public void colisionPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		Velocidad velocidadPoogling=poogling.getVelocidad();
		int valorVelocidad=velocidadPoogling.getVelocidad();
		velocidadPoogling.setVelocidad((valorVelocidad+valorVelocidad));
		poogling.setVelocidad(velocidadPoogling);
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

