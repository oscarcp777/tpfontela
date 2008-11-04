package FabricaHabilidades;

import utilitarios.Constants;
import habilidadesPooglins.Habilidad;
import habilidadesPooglins.TaladroUltrasonico;

public class FabricaTaladroUltrasonico extends FabricaHabilidades {

	@Override
	public Habilidad crear() {
		// TODO Auto-generated method stub
		return new TaladroUltrasonico();
	}

	@Override
	public String obtenerNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreHabilidades.TALADRO_ULTRASONICO;
	}

}
