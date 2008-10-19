
package Otros;

import TipoHabilidades.Habilidad;
import TipoPosicion.Estatico;
import TipoPosicion.Posicion;
import TipoPosicion.Posicionable;
import TipoPosicion.Velocidad;
import TipoTerrenos.Terreno;

public class Poogling extends Posicionable{

	private Habilidad habilidad;
	private Vida vida;
	private Velocidad velocidad;
	private Direccion direccion;
	
	public Poogling(Posicion posicionInicial){
		asignarPosicion(posicionInicial);
		direccion = new Abajo(posicionInicial);
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
	
	public Direccion getDireccion(){
		return this.direccion;
	}
	
	public void setDireccion(Direccion direccion){
		this.direccion=direccion;
	}
	
	public void mover(Estatico estatico){
		
		if(estatico instanceof Terreno){
	         Terreno terreno = (Terreno)estatico;
	         terreno.aplicarAdinamico(this);
	         
		}
		
	}
	
}
