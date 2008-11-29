package modelo.fabricaTerrenos;

import modelo.elementosDelMapa.AgujeroNegro;
import modelo.elementosDelMapa.Terreno;
import modelo.habilidadesPooglins.Habilidad;
import modelo.habilidadesPooglins.PlatilloVolador;
import modelo.utilitarios.Constants;

public class FabricaAgujeroNegro extends FabricaTerrenos{
	
	@Override
	public Terreno crear() {
		// TODO Auto-generated method stub
		return new AgujeroNegro();
	}

	@Override
	public String obtenerNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreTerrenos.AGUJERO_NEGRO;
	}
}
