package Otros;

import java.util.ArrayList;
import java.util.List;

import TipoPosicion.Posicionable;

public class Nave extends Posicionable{

	public List pooglings;
	
	public Nave(){
		pooglings=new ArrayList();
	}

	public List getPooglings() {
		return pooglings;
	}

	public void setPooglings(List pooglings) {
		this.pooglings = pooglings;
	}
	
}
