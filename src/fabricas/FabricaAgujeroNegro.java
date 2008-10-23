package fabricas;

import Otros.DimensionTerreno;
import TipoPosicion.Posicion;
import TipoTerrenos.AgujeroNegro;
import TipoTerrenos.Terreno;


public class FabricaAgujeroNegro extends FabricaTerreno {

	@Override
	public void crearTerreno(Posicion posicion) {
		// TODO Auto-generated method stub
		this.setTerreno(new AgujeroNegro(posicion));
	}
	
	public AgujeroNegro getTerreno(){
		return this.getTerreno();
	}

}
