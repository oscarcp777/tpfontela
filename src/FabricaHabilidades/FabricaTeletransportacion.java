package FabricaHabilidades;

import utilitarios.Constants;
import habilidadesPooglins.Habilidad;
import habilidadesPooglins.Teletransportacion;

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
