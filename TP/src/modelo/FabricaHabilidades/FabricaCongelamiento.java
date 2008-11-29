package modelo.FabricaHabilidades;

import modelo.habilidadesPooglins.Congelamiento;
import modelo.habilidadesPooglins.Habilidad;
import modelo.utilitarios.Constants;

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
