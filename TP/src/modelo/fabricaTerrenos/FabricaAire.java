package modelo.fabricaTerrenos;

import modelo.elementosDelMapa.Aire;
import modelo.elementosDelMapa.Terreno;
import modelo.utilitarios.Constants;

public class FabricaAire extends FabricaTerrenos{
	@Override
	public Terreno crear() {
		// TODO Auto-generated method stub
		return new Aire();
	}

	@Override
	public String obtenerNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreTerrenos.AIRE;
	}
}
