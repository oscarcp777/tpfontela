
package elementosDelMapa;

import java.util.Iterator;

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
	
	public Poogling(Posicion posicionInicial,Vida vida){
		this.asignarPosicion(posicionInicial);
		movimiento = new Movimiento(posicionInicial);
		this.vida = vida;
	}
	
	public Velocidad getVelocidad() {
		return velocidad;
	}

	public void setVelocidad(Velocidad velocidad) {
		this.velocidad = velocidad;
	}

	public void setHabilidad(Habilidad habilidad) {
		this.habilidad = habilidad;
	}

	public Habilidad getHabilidad() {;
		return habilidad;
	}
		
	//Mueve al pooglin y segun sobre que terreno este parado el mismo
	//cambiará de dirección en que se esta moviendo o se le duplicara 
	//la velocidad o puede llegar a quitarle la vida.
    public boolean mover(Mapa mapa){
    	    	    	
       	boolean llegoAnave = mapa.llegoPooglinANaveEscape(this);
    	
		for(Iterator itColTerrenoContiguo=mapa.obtenerBloquesContiguosAlPooglin(this).iterator(); itColTerrenoContiguo.hasNext();){
			Terreno terreno=(Terreno)itColTerrenoContiguo.next();
			terreno.colisionarPoogling(this);
		}
		
		if(!llegoAnave && isConVida()){ //Si el pooglin no llego a la nave, seguira moviendose y colisionando con el terreno
		this.asignarPosicion(movimiento.siguientePosicion()); //le pido la siguiente posicion y se la asigno al pooglin 
		return true;
		}else if(llegoAnave)
			mapa.subirPooglinNaveEscape(this);
			
		
		return false;	
	}
	
    public int cantidadDePasosEnDireccion(){
    	return movimiento.cantidadDePasosEnDireccion();
    }
    
    public void validezMovimiento(boolean mover){
    	movimiento.valido(mover);
    }
    
    public boolean quieto(){
    	return movimiento.invalido();
    }
    
    public void caerAlVacio(){
    	movimiento.cambiarDireccion(Abajo.getInstance());
    }
    
    public void cambiarDireccionDeMovimiento(){
    	movimiento.cambiarDireccion();
    }
    
    public Posicion siguientePosicion(){
    	return movimiento.verSiguientePosicion();
    }
    
	public void quitarVida(){
		vida.sacarVidas(vida.getCantidadVidas());
	}
	
	public boolean isConVida(){
		return vida.hayVida();
	}
	
}
