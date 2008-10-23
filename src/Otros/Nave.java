package Otros;

import java.util.ArrayList;
import java.util.List;

import TipoPosicion.Estatico;
import TipoPosicion.Posicion;
import TipoPosicion.Posicionable;
import Utilidades.Constants;

public class Nave extends Posicionable implements Estatico{

	public ColPooglins pooglings;
	
	public Nave(Posicion posicion){
		//pooglings=new ArrayList();
       this.asignarPosicion(posicion);
	}

	public ColPooglins obtenerPooglings() {
		return pooglings;
	}

	public void cargarPooglings(ColPooglins pooglings) {
		this.pooglings = pooglings;
	}

	@Override
	public boolean colisionPoogling(Poogling poogling) {
		if(poogling.obtenerPosicion().compareTo(this.obtenerPosicion())==Constants.ValorComparador.IGUAL){
		this.pooglings.agregarPooglin(poogling);
		return true;
		}
		return false;
	}


	
}
