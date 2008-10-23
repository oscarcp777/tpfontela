package fabricas;



import java.util.Map;
import java.util.TreeMap;

import Otros.DimensionTerreno;
import TipoPosicion.Posicion;
import TipoTerrenos.Aire;
import TipoTerrenos.Terreno;
import Utilidades.Constants;

public abstract class FabricaTerreno {

	private Terreno terreno;
	
	public abstract void crearTerreno(Posicion posicion);
	
	public Terreno getTerreno(){
		return this.terreno;
	}
	
	protected void setTerreno(Terreno terreno){
		this.terreno = terreno;
	}
	
}
