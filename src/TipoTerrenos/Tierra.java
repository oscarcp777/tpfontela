package TipoTerrenos;

import Otros.Poogling;
import TipoHabilidades.Habilidad;
import Utilidades.Constants;

public class Tierra extends Terreno{

	@Override
	public void colisionPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public boolean movimientoPooglingValido(Poogling poogling) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void aplicarHabilidad(Habilidad habilidad) {
		
		
	}

	@Override
	public String getNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreTerreno.TIERRA;
	}

	@Override
	public int compareTo(Object o) {
		// TODO Auto-generated method stub
		return 0;
	}

}
