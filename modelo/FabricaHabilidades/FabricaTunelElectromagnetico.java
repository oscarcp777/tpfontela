package FabricaHabilidades;

import utilitarios.Constants;
import habilidadesPooglins.Habilidad;
import habilidadesPooglins.TunelElectromagnetico;

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
