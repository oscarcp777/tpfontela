package modelo.pooglins;

import modelo.constantes.Constantes;
/**
 * Clase: HabilidadNula (extiende de Habilidad)
 * Utilidad: Sirve para representar el caso en que un Pooglin no tenga seteada aun
 * 			 alguna habilidad en particular.
 * Utilizada por: Pooglin.
 * Colabora con: Constantes.
 * 
 * */
public class HabilidadNula extends Habilidad {
	
	public HabilidadNula(){
		this.id = Constantes.HABILIDAD_NULA;
	}

	@Override
	public int getVelocidadDeCaida() {
		return Constantes.VELOCIDAD_CAIDA_NORMAL;
	}

}
