package modelo.FabricaHabilidades;

import modelo.habilidadesPooglins.Habilidad;
import modelo.habilidadesPooglins.RayoLaser;
import modelo.utilitarios.Constants;

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
