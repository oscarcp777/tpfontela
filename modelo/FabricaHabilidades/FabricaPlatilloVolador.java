package FabricaHabilidades;

import utilitarios.Constants;
import habilidadesPooglins.Habilidad;
import habilidadesPooglins.PlatilloVolador;

public class FabricaPlatilloVolador extends FabricaHabilidades {

	@Override
	public Habilidad crear() {
		// TODO Auto-generated method stub
		return new PlatilloVolador();
	}

	@Override
	public String obtenerNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreHabilidades.PLATILLO_VOLADOR;
	}

}
