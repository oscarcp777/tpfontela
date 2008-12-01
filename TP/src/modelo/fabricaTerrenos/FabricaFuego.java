package modelo.fabricaTerrenos;

import modelo.elementosDelMapa.Fuego;
import modelo.elementosDelMapa.Terreno;
import modelo.utilitarios.Constants;

public class FabricaFuego extends FabricaTerrenos{
	@Override
	public Terreno crear() {
		// TODO Auto-generated method stub
		return new Fuego();
	}

	@Override
	public String obtenerNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreTerrenos.FUEGO;
	}
}
