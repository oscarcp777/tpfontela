package TipoTerrenos;

import Otros.Poogling;
import TipoHabilidades.Habilidad;
import Utilidades.Constants;

public class Aire extends Terreno{
	
	public boolean movimientoPooglingValido(Poogling poogling){
		return true;
	}

	@Override
	public void colisionPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void aplicarHabilidad(Habilidad habilidad) {
		// TODO Auto-generated method stub
		
	}





	@Override
	public void aplicarAdinamico(Poogling poogling) {
		// TODO Auto-generated method stub
		if(poogling.obtenerPosicion().posicionValidaLateral(this, poogling)){
			poogling.asignarPosicion(this.obtenerPosicion());
		}
	
	}
}
