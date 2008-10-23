package TipoTerrenos;

import Otros.Poogling;

import TipoHabilidades.Habilidad;
import Utilidades.Constants;

import TipoPosicion.Posicion;
import TipoPosicion.Velocidad;

public class Hielo extends Terreno{

	//Constructor por defecto
	public Hielo(){
		
	}
	
	public Hielo(Posicion posicion){
		asignarPosicion(posicion);
	}
	
	@Override
	public boolean colisionPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		Velocidad velocidadPoogling=poogling.getVelocidad();
		int valorVelocidad=velocidadPoogling.getVelocidad();
		velocidadPoogling.setVelocidad((valorVelocidad+valorVelocidad));
		poogling.setVelocidad(velocidadPoogling);
		return true;
	}

	
	@Override
	public void aplicarHabilidad(Habilidad habilidad) {
		// TODO Auto-generated method stub
	
	}
	

}

