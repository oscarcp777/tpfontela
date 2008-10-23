package fabricas;

import Otros.DimensionTerreno;
import TipoPosicion.Posicion;
import TipoTerrenos.AgujeroNegro;
import TipoTerrenos.Aire;
import TipoTerrenos.Fuego;


public class FabricaAire extends FabricaTerreno{

	@Override
	public void crearTerreno(Posicion posicion){
		this.setTerreno(new Aire(posicion));
	}
	
	public Aire getTerreno(){
		return this.getTerreno();
	}
	
}	

