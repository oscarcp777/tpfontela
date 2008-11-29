package modelo.fabricaTerrenos;

import modelo.elementosDelMapa.Terreno;
import modelo.elementosDelMapa.Tierra;
import modelo.utilitarios.Constants;

public class FabricaTierra extends FabricaTerrenos{

	@Override
	public Terreno crear() {
		// TODO Auto-generated method stub
		return new Tierra();
	}

	@Override
	public String obtenerNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreTerrenos.TIERRA;
	}
}
