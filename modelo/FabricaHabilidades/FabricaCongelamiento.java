package FabricaHabilidades;

import utilitarios.Constants;
import habilidadesPooglins.Congelamiento;
import habilidadesPooglins.Habilidad;

public class FabricaCongelamiento extends FabricaHabilidades {

	@Override
	public Habilidad crear() {
		return new Congelamiento();
	}

	@Override
	public String obtenerNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreHabilidades.CONGELAMIENTO;
	}

}
