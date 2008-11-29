package modelo.FabricaHabilidades;

import modelo.habilidadesPooglins.Habilidad;
import modelo.habilidadesPooglins.Teletransportacion;
import modelo.utilitarios.Constants;

public class FabricaTeletransportacion extends FabricaHabilidades {

	@Override
	public Habilidad crear() {
		// TODO Auto-generated method stub
		return new Teletransportacion();
	}

	@Override
	public String obtenerNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreHabilidades.TELETRANSPORTACION;
	}

}
