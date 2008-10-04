package Otros;

import java.util.ArrayList;
import java.util.List;

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
