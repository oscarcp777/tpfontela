package modelo.pooglins;

import modelo.entornoDeJuego.ServiciosTerreno;
import modelo.movimientos.Direccion;

/**
 * Clase: Oficio.
 * Utilidad: Utilizada para delegar las cuestiones propias de cada oficio que podria 
 * 			 tener un Pooglin en esta clase.
 * 			 Posee la logica del comportamiento de los Oficios que podra realizar
 * 			 un Pooglin.  
 * Utilizadad por: Pooglin.
 * Colabora con: Direccion, Habilidad, Posicion, ServiciosTerreno.
 * */
public abstract class Oficio{
	
	protected Direccion direccion;
	protected Direccion direccionAnterior;
	protected Habilidad habilidad;
	protected boolean finalizado;
	protected int idOficio;

	
	
	public Oficio(){
		this.finalizado = false;
	}
	public Oficio(Direccion direccion, Direccion direccionAnterior){
		this.finalizado = false;
		this.direccionAnterior = direccionAnterior;
		this.direccion = direccion;
	}
	public Direccion getDireccion() {
		return direccion;
	}
	public Direccion getDireccionAnterior() {
		return direccionAnterior;
	}
	public boolean estaFinalizado(){
		return this.finalizado;
	}
	public abstract Oficio generarOficioSiguiente(ServiciosTerreno terreno, Posicion posicion);
	
	public abstract void mover(ServiciosTerreno terreno, Posicion miPosicion);
	
	protected void setDireccion(Direccion direccion) {
		this.direccion = direccion;
	}
	protected abstract boolean tePuedesMover(ServiciosTerreno terreno, Posicion miPosicion);
	
	/*protected abstract void setDireccionAnterior(Direccion direccion);*/

	public Habilidad getHabilidad() {
		return habilidad;
	}
	
	/*protected MaterialDeTerreno getSiguienteMaterial(Matriz terreno, Posicion posicion){
		return terreno.getSiguienteMaterial(this.direccion, posicion);
	}
	
	protected MaterialDeTerreno getMaterialActual(Matriz terreno, Posicion posicion){
		return terreno.getMaterialActual(this.direccion, posicion);
	}*/
	protected void avanzar(Posicion miPosicion){
		 miPosicion.moverEnDireccion(this.direccion);
	}
	
	public int getId(){
		return this.idOficio;
	}
	public void setHabilidad(int habilidad) {
		// TODO Auto-generated method stub
		this.habilidad = FabricaDeHabilidades.crearHabilidad(habilidad);
	}
	
}
