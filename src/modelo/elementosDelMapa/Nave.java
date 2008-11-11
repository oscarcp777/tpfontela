package modelo.elementosDelMapa;

import modelo.nivelDeJuego.ColPooglins;
import modelo.propiedadesDeElementos.Colisionable;
import modelo.propiedadesDeElementos.Posicion;
import modelo.propiedadesDeElementos.Posicionable;

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
