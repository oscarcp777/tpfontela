
package Otros;

import fabricas.FabricaTerreno;
import fabricas.Movimiento;
import TipoHabilidades.Habilidad;
import TipoPosicion.Estatico;
import TipoPosicion.Mapa;
import TipoPosicion.Posicion;
import TipoPosicion.Posicionable;
import TipoPosicion.Velocidad;
import TipoTerrenos.Terreno;

public class Poogling extends Posicionable{

	private Habilidad habilidad;
	private Vida vida;
	private Velocidad velocidad;
	private Movimiento movimiento;
	
	//Constructor por defecto
	public Poogling(){
	  
	}
	
	
	public Poogling(Posicion posicionInicial){
		this.asignarPosicion(posicionInicial);
		movimiento = new Movimiento(posicionInicial);
	}
	
	
	public Velocidad getVelocidad() {
		return velocidad;
	}

	public void setVelocidad(Velocidad velocidad) {
		this.velocidad = velocidad;
	}

	public Vida getVida() {
		return vida;
	}

	public void setVida(Vida vida) {
		this.vida = vida;
	}
		


	public void setHabilidad(Habilidad habilidad) {
		this.habilidad = habilidad;
	}

	public Habilidad getHabilidad() {;
		return habilidad;
	}
		
	public void asignarPosicion(Posicion posicion,Direccion direccion){
		
	}
	
    public void mover(Mapa mapa){
    	
    	//obtengo el terreno de la posicion siguiente del pooglin
		Terreno terrenoCostado=mapa.obtenerTerreno(movimiento.verPosicionSiguiente());
		terrenoCostado.colisionPoogling(this);
		movimiento.mover();
		
		//para ver donde esta parado el pooglin
		Terreno terrenoAbajo=mapa.obtenerTerreno(movimiento.verPosicionAbajo());
		terrenoAbajo.colisionPoogling(this);
		
		
				
	}
	
	public Movimiento getMovimiento() {
		return movimiento;
	}


	public void setMovimiento(Movimiento movimiento) {
		this.movimiento = movimiento;
	}


	//Para copiar datos y no referencias
	public void pooglingMellizo(Poogling otroPoogling){
		habilidad = otroPoogling.habilidad;
		vida = otroPoogling.vida;
		velocidad = otroPoogling.velocidad;
	}
	
}
