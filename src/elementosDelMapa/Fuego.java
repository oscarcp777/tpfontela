package elementosDelMapa;

import propiedadesDeElementos.Posicion;
import propiedadesDeElementos.Vida;
import habilidadesPooglins.Habilidad;
import utilitarios.Constants;

public class Fuego extends Terreno{

	//Constructor por defecto
	public Fuego(){
		
	}
	
	public Fuego(Posicion posicion){
		asignarPosicion(posicion);
	}
	
	//En caso de que el pooglin colisione con este
	//tipo de terreno, el mismo morir� de manera
	//instantanea.
	@Override
	public void colisionarPoogling(Poogling poogling) {
		if(this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteAbajo())==
			Constants.ValorComparador.IGUAL) 
		
			poogling.quitarVida();
	}



	@Override
	public void aplicarHabilidad(Habilidad habilidad) {
		
	}

}
