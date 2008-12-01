package modelo.fabricaTerrenos;

import modelo.elementosDelMapa.Terreno;
import modelo.elementosDelMapa.TunelIzquierda;
import modelo.utilitarios.Constants;

public class FabricaTunelIzquierda extends FabricaTerrenos{
	@Override
	public Terreno crear() {
		// TODO Auto-generated method stub
		return new TunelIzquierda();
	}

	@Override
	public String obtenerNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreTerrenos.TUNEL_IZQUIERDA;
	}
}
