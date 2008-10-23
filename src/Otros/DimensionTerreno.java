package Otros;

import TipoPosicion.Mapa;
import TipoPosicion.Posicion;
import Utilidades.Constants;

public class DimensionTerreno {

	private int dimX;
	private int dimY;

	public int compareTo(Posicion posicion){
		int posX = posicion.getPosicionX();
		int posY = posicion.getPosicionY();

		if((this.dimX<posicion.getPosicionX())&&(this.dimY<posicion.getPosicionY()))
			return Constants.ValorComparador.MENOR; //en este caso seria una posicion no valida (fuera de rango)
		else if((this.dimX==posicion.getPosicionX())&&(this.dimY==posicion.getPosicionY()))
			return Constants.ValorComparador.IGUAL;
		else 
			return Constants.ValorComparador.MAYOR; 

	}

	public int getdimX() {
		return dimX;
	}

	public void setdimX(int dimX) {
		this.dimX = dimX;
	}

	public int getdimY() {
		return dimY;
	}

	public void setdimY(int dimY) {
		this.dimY = dimY;
	}

}
