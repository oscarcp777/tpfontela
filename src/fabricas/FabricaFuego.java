package fabricas;

import Otros.DimensionTerreno;
import TipoPosicion.Posicion;
import TipoTerrenos.AgujeroNegro;
import TipoTerrenos.Fuego;
import TipoTerrenos.Terreno;


public class FabricaFuego extends FabricaTerreno {

	@Override
	public void crearTerreno(Posicion posicion) {
		this.setTerreno(new Fuego(posicion));
	}

	public Fuego getTerreno(){
		return this.getTerreno();
	}
}
