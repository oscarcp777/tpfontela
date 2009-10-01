package modelo.pooglins;

import modelo.constantes.Constantes;
import modelo.excepciones.IdHabilidadIncorrectoException;

public class FabricaDeHabilidades {

	public static Habilidad crearHabilidad(int habilidad) {
		// TODO Auto-generated method stub
		switch (habilidad) {
		case Constantes.HABILIDAD_NULA: return new HabilidadNula();
		case Constantes.PARACAIDISTA_ESPACIAL: return new ParacaidistaEspacial();
		default: throw new IdHabilidadIncorrectoException(); 
		}

	}
}
