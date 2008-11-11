package modelo.FabricaHabilidades;

import modelo.habilidadesPooglins.Habilidad;
import modelo.habilidadesPooglins.TunelElectromagnetico;
import modelo.utilitarios.Constants;

public class FabricaTunelElectromagnetico extends FabricaHabilidades {

	@Override
	public Habilidad crear() {
		// TODO Auto-generated method stub
		return new TunelElectromagnetico();
	}

	@Override
	public String obtenerNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreHabilidades.TUNEL_ELECTROMAGNETICO;
	}

}
