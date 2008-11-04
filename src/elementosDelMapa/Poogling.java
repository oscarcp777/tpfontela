
package elementosDelMapa;

import java.util.Iterator;
import java.util.List;

import nivelDeJuego.ColTerreno;

import propiedadesDeElementos.Posicion;
import propiedadesDeElementos.Posicionable;
import propiedadesDeElementos.Velocidad;
import propiedadesDeElementos.Vida;
import habilidadesPooglins.ContenedorHabilidades;
import habilidadesPooglins.Habilidad;
import mapaDeJuego.Mapa;
import movimientoPooglins.Abajo;
import movimientoPooglins.DiagonalArribaIzquierda;
import movimientoPooglins.Direccion;
import movimientoPooglins.Movimiento;
import movimientoPooglins.PasosEnDireccion;

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

	public void darHabilidad(String nombre) {
		this.habilidad = ContenedorHabilidades.getInstance().obtenerHabilidadDeFabrica(nombre);
	}
	
	public void desactivarHabilidad() {
		habilidad.desactivarHabilidad();
	}
	
	public String habilidadAplicada(){
		return habilidad.getNombre();
	}
	
	private void aplicarHabilidadTerrenoYpooglin(Mapa mapa, Terreno terreno){
		if (habilidad!=null && habilidad.isActivada()){
			terreno.aplicar(habilidad,mapa,this);
			habilidad.aplicarApooglin(mapa,this,terreno);
		}
	}
		
	//Mueve al pooglin y segun sobre que terreno este parado el mismo
	//cambiará de dirección en que se esta moviendo o se le duplicara 
	//la velocidad o puede llegar a quitarle la vida.
    public boolean mover(Mapa mapa){
    	             	
		for(Iterator itColTerrenoContiguo=mapa.obtenerBloquesContiguosAlPooglin(this).iterator(); itColTerrenoContiguo.hasNext();){
			Terreno terreno=(Terreno)itColTerrenoContiguo.next();
			aplicarHabilidadTerrenoYpooglin(mapa,terreno); //metodo de pooglin que le aplica la habilidad a si mismo y al terreno
			if(terreno.getVida()==null||terreno.getVida().hayVida())
			terreno.colisionarPoogling(this);
		}
		
		boolean llegoAnave = mapa.llegoPooglinANaveEscape(this);
				
		if(!llegoAnave && isConVida()){ //Si el pooglin no llego a la nave, seguira moviendose y colisionando con el terreno
			this.asignarPosicion(movimiento.siguientePosicion()); //le pido la siguiente posicion y se la asigno al pooglin 
		return true;
		}else if(llegoAnave)
			mapa.subirPooglinNaveEscape(this);
			
		
		return false;	
	}
    
    public Posicion avanzarEnDireccion(PasosEnDireccion pasosEnDireccion){
    	return movimiento.darPasosEnDireccion(pasosEnDireccion);
    }
	
    public int cantidadDePasosEnDireccion(){
    	return movimiento.cantidadDePasosEnDireccion();
    }
    
    public void invalidarMovimiento(boolean mover){
    	movimiento.movimientoInvalido(mover);
    }
    
    public boolean quieto(){
    	return movimiento.noCambiaSuPosicion();
    }
    
    public void redireccionar(Direccion direccion){
    	movimiento.cambiarDireccion(direccion);
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
	
	public boolean isConHabilidad(){
		return habilidad.isActivada();
	}
	
	public void contarPasos(boolean conteo){
		movimiento.contarPasos(conteo);
	}
	
	public boolean isConDireccion(){
		return movimiento.isConDireccion();
	}

}
