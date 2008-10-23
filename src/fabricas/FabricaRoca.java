package fabricas;

import Otros.DimensionTerreno;
import TipoPosicion.Posicion;
import TipoTerrenos.AgujeroNegro;
import TipoTerrenos.Roca;
import TipoTerrenos.Terreno;


public class FabricaRoca extends FabricaTerreno {

	@Override
	public void crearTerreno(Posicion posicion) {
		this.setTerreno(new Roca(posicion));
	}

	public Roca getTerreno(){
		return this.getTerreno();
	}

}
