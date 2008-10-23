package TipoTerrenos;

import Otros.Poogling;

import TipoHabilidades.Habilidad;
import TipoPosicion.Posicion;
import Otros.Vida;
import Utilidades.Constants;
public class Fuego extends Terreno{

	//Constructor por defecto
	public Fuego(){
		
	}
	
	public Fuego(Posicion posicion){
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

