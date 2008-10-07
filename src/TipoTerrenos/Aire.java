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
	public String getNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreTerreno.AIRE;
	}

	@Override
	public int compareTo(Object o) {
		// TODO Auto-generated method stub
		return 0;
	}
}
