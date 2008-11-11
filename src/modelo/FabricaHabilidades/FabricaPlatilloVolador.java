package modelo.FabricaHabilidades;

import modelo.habilidadesPooglins.Habilidad;
import modelo.habilidadesPooglins.PlatilloVolador;
import modelo.utilitarios.Constants;

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
