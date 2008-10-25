
package elementosDelMapa;

import propiedadesDeElementos.Posicion;
import propiedadesDeElementos.Posicionable;
import propiedadesDeElementos.Velocidad;
import propiedadesDeElementos.Vida;
import habilidadesPooglins.Habilidad;
import mapaDeJuego.Mapa;
import movimientoPooglins.Abajo;
import movimientoPooglins.Direccion;
import movimientoPooglins.Movimiento;

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
		movimiento = new Movimiento(posicionInicial,Abajo.getInstance());
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
	
	//Mueve al pooglin y segun sobre que terreno este parado el mismo
	//cambiará de dirección en que se esta moviendo o se le duplicara 
	//la velocidad o puede llegar a quitarle la vida.
    public boolean mover(Mapa mapa){
    	    	    	
       	Terreno terrenoCostado=mapa.obtenerTerreno(movimiento.getPosicionSiguiente()); //obtengo el terreno de la posicion siguiente del pooglin
		terrenoCostado.colisionarPoogling(this); //lo colisiciono con ese terreno
		
		if(!mapa.isPooglinLlegoANaveEscape(this)){ //Si el pooglin no llego a la nave, seguira moviendose y colisionando con el terreno
		movimiento.mover(); //primero me muevo y luego miro que hay abajo
		Terreno terrenoAbajo=mapa.obtenerTerreno(movimiento.getPosicion().obtenerPosicionSiguienteAbajo());
		terrenoAbajo.colisionarPoogling(this);
		return true;
		}else{
			mapa.subirPooglinNaveEscape(this);
			return false;
		}
		
	}
	
	public Movimiento getMovimiento() {
		return movimiento;
	}


	public void setMovimiento(Movimiento movimiento) {
		this.movimiento = movimiento;
	}

	
}
