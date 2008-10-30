package elementosDelMapa;

import mapaDeJuego.Mapa;
import propiedadesDeElementos.Posicion;
import propiedadesDeElementos.Vida;
import habilidadesPooglins.Habilidad;
import utilitarios.Constants;

public class Fuego extends Terreno{

	//Constructor por defecto
	public Fuego(){
		setNombreTerreno(Constants.NombreTerreno.FUEGO);
	}
	
	public Fuego(Posicion posicion){
		asignarPosicion(posicion);
		setNombreTerreno(Constants.NombreTerreno.FUEGO);
	}
	
	//En caso de que el pooglin colisione con este
	//tipo de terreno, el mismo morirá de manera
	//instantanea.
	@Override
	public void colisionarPoogling(Poogling poogling) {
		if(this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteAbajo())==
			Constants.ValorComparador.IGUAL) 
		
			poogling.quitarVida();
	}

	@Override
	public void cambiarPorAire(Mapa mapa) {
		// TODO Auto-generated method stub
		
	}

}

