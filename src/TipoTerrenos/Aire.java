package TipoTerrenos;

import Otros.Poogling;

public class Aire extends Terreno{
	
	public boolean movimientoPooglingValido(Poogling poogling){
		return true;
	}

	@Override
	public void colisionPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		
	}
}
