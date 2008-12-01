package modelo.fabricaTerrenos;

import modelo.elementosDelMapa.Roca;
import modelo.elementosDelMapa.Terreno;
import modelo.utilitarios.Constants;

public class FabricaRoca extends FabricaTerrenos{
	@Override
	public Terreno crear() {
		// TODO Auto-generated method stub
		return new Roca();
	}

	@Override
	public String obtenerNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreTerrenos.ROCA;
	}
}
