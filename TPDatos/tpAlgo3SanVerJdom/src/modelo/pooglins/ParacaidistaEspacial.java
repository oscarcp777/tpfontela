package modelo.pooglins;

import modelo.constantes.Constantes;
/**
 * Clase: ParacaidistaEspacial (extiende de Habilidad).
 * Utilidad: Representar la caida de un Pooglin, pero teniendo la habilidad de caer
 * 			 despacio, o sea como el Paracaidista del juego original Lemmings.
 * Utilizada por: Pooglin.
 * Colabora con: Constantes.
 * */
public class ParacaidistaEspacial extends Habilidad {
	
	public ParacaidistaEspacial(){
		this.id = Constantes.PARACAIDISTA_ESPACIAL;
	}

	public int getVelocidadDeCaida() {
		return Constantes.VELOCIDAD_CAIDA_DISMINUIDA;
	}

}
