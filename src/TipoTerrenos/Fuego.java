package TipoTerrenos;

import Otros.Poogling;
import TipoHabilidades.Habilidad;
import Otros.Vida;
public class Fuego extends Terreno{

	@Override
	public void colisionPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		Vida vidaPoogling=poogling.getVida();
		while (vidaPoogling.getCantidadVidas()>0){
			vidaPoogling.sacarVidas(1);
		}
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

