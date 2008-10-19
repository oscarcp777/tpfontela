package Otros;

import java.util.ArrayList;
import java.util.List;

import TipoPosicion.Estatico;
import TipoPosicion.Posicionable;

public class Nave extends Posicionable implements Estatico{

	public List pooglings;
	
	public Nave(){
		//pooglings=new ArrayList();
	}

	public List getPooglings() {
		return pooglings;
	}

	public void setPooglings(List pooglings) {
		this.pooglings = pooglings;
	}


	
}
