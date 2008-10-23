package fabricas;

import Otros.DimensionTerreno;
import TipoPosicion.Posicion;
import TipoTerrenos.AgujeroNegro;
import TipoTerrenos.Hielo;
import TipoTerrenos.Terreno;


public class FabricaHielo extends FabricaTerreno {

	@Override
	public void crearTerreno(Posicion posicion) {
		this.setTerreno(new Hielo(posicion));
	}

	public Hielo getTerreno(){
		return this.getTerreno();
	}
}
