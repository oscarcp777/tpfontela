package modelo.pooglins;
/**
 * Clase: Habilidad (abstracta).
 * Utilidad: Representar la Habilidad de los Pooglins, mantener una interfaz basica para 
 * 			 habilidades que extiendan de esta (como por ejemplo ParacaidistaEspacial).
 * Utilizada por: Pooglin.
 * */
public abstract class Habilidad {
	protected int id;
	
	public int getID(){
		return this.id;
	}
	public abstract int getVelocidadDeCaida();

}
