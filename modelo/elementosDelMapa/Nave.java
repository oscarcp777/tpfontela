package elementosDelMapa;

import nivelDeJuego.ColPooglins;
import propiedadesDeElementos.Colisionable;
import propiedadesDeElementos.Posicion;
import propiedadesDeElementos.Posicionable;

public class Nave extends Posicionable implements Colisionable{

	public ColPooglins pooglings;
	
	public Nave(Posicion posicion){
		pooglings = new ColPooglins();
		this.asignarPosicion(posicion);
	}

	public ColPooglins obtenerPooglings() {
		return pooglings;
	}

	public void cargarPooglings(ColPooglins pooglings) {
		this.pooglings = pooglings;
	}

	
	//se agrega el pooglin a la coleccion de pooglins de la nave.
	@Override
	public void colisionarPoogling(Poogling poogling) {
		this.pooglings.agregarPooglin(poogling);
	}


	
}
