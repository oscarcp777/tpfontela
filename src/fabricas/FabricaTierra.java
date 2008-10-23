package fabricas;

import Otros.DimensionTerreno;
import TipoPosicion.Posicion;
import TipoTerrenos.AgujeroNegro;
import TipoTerrenos.Terreno;
import TipoTerrenos.Tierra;


public class FabricaTierra extends FabricaTerreno {

	@Override
	public void crearTerreno(Posicion posicion) {
		this.setTerreno(new Tierra(posicion));
	}

	public Tierra getTerreno(){
		return this.getTerreno();
	}
}
