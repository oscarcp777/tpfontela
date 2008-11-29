package modelo.fabricaTerrenos;

import modelo.elementosDelMapa.Hielo;
import modelo.elementosDelMapa.Terreno;
import modelo.utilitarios.Constants;

public class FabricaHielo extends FabricaTerrenos{
	@Override
	public Terreno crear() {
		// TODO Auto-generated method stub
		return new Hielo();
	}

	@Override
	public String obtenerNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreTerrenos.HIELO;
	}
}
