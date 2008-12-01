package modelo.fabricaTerrenos;

import modelo.elementosDelMapa.Terreno;
import modelo.elementosDelMapa.TunelDerecha;
import modelo.utilitarios.Constants;

public class FabricaTunelDerecha extends FabricaTerrenos{
	
	@Override
	public Terreno crear() {
		// TODO Auto-generated method stub
		return new TunelDerecha();
	}

	@Override
	public String obtenerNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreTerrenos.TUNEL_DERECHA;
	}
}
