package modelo.FabricaHabilidades;

import modelo.habilidadesPooglins.Habilidad;
import modelo.habilidadesPooglins.TaladroUltrasonico;
import modelo.utilitarios.Constants;

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
