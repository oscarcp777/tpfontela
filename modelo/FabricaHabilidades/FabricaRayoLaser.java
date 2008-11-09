package FabricaHabilidades;

import utilitarios.Constants;
import habilidadesPooglins.Habilidad;
import habilidadesPooglins.RayoLaser;

public class FabricaRayoLaser extends FabricaHabilidades {

	@Override
	public Habilidad crear() {
		// TODO Auto-generated method stub
		return new RayoLaser();
	}

	@Override
	public String obtenerNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreHabilidades.RAYO_LASER;
	}

}
