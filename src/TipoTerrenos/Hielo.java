package TipoTerrenos;

import Otros.Poogling;
import TipoHabilidades.Habilidad;

import TipoPosicion.Velocidad;

public class Hielo extends Terreno{

	@Override
	public void colisionPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		Velocidad velocidadPoogling=poogling.getVelocidad();
		int valorVelocidad=velocidadPoogling.getVelocidad();
		velocidadPoogling.setVelocidad((valorVelocidad+valorVelocidad));
		poogling.setVelocidad(velocidadPoogling);
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
		return null;
	}

	@Override
	public int compareTo(Object o) {
		// TODO Auto-generated method stub
		return 0;
	}

}
