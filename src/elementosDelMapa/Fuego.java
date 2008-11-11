package modelo.elementosDelMapa;

import modelo.habilidadesPooglins.Habilidad;
import modelo.mapaDeJuego.Mapa;
import modelo.propiedadesDeElementos.Posicion;
import modelo.propiedadesDeElementos.Vida;
import modelo.utilitarios.Constants;

public class Fuego extends Terreno{

	//Constructor por defecto
	public Fuego(){
		
	}
	
	public Fuego(Posicion posicion){
		asignarPosicion(posicion);
		
	}
	
	//En caso de que el pooglin colisione con este
	//tipo de terreno, el mismo morira de manera
	//instantanea.
	@Override
	public void colisionarPoogling(Poogling poogling) {
		if(this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteAbajo())==
			Constants.ValorComparador.IGUAL) 
		
			poogling.quitarVida();
	}

	@Override
	public String obtenerNombre() {
		return Constants.NombreTerrenos.FUEGO;
	}

	@Override
	public void aplicar(Habilidad habilidad, Mapa mapa, Poogling poogling) {
		// TODO Auto-generated method stub
		
	}

}

