package TipoTerrenos;

import Otros.Poogling;
import TipoHabilidades.Habilidad;
import Utilidades.Constants;

public class Hielo extends Terreno{

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
		// TODO Auto-generated method stub
		
	}

	@Override
	public String getNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreTerreno.HIELO;
	}

	@Override
	public int compareTo(Object o) {
		// TODO Auto-generated method stub
		return 0;
	}

}
