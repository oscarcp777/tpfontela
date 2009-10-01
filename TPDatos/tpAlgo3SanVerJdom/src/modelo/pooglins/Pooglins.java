package modelo.pooglins;

import modelo.constantes.Constantes;
import modelo.entornoDeJuego.EstadoPooglin;
import modelo.entornoDeJuego.ServiciosTerreno;
import modelo.excepciones.MuerteDePooglinException;
import modelo.excepciones.PooglinGanadorException;
import modelo.movimientos.Direccion;
/**
 * Clase: Pooglins.
 * Utilidad: Representa a los Pooglins del juego, los cuales entre otras cosas, poseen 
 * 			 un Oficio y una Posicion. 
 * Utilizada por: EquipoPooglins.
 * Colabora con: Oficio, Posicion y ServiciosTerreno.
 * 
 * */
public class Pooglins {
	
	
	private Posicion posicion;
	private int id;
	private ServiciosTerreno terreno;
	private Oficio oficio;
	

	public Pooglins(int id, Oficio oficio){
		this.id = id;
		this.oficio = oficio;
	}
	public  Pooglins(EstadoPooglin estado, ServiciosTerreno terreno) {
		this.id = estado.getId();
		this.oficio = FabricaDeOficio.crearOficioPorId(estado.getOficio(), estado.getDireccion(), FabricaDeHabilidades.crearHabilidad(estado.getHabilidad()));
		this.posicion = new Posicion(estado.getPosicionX(),estado.getPosicionY());
		this.terreno = terreno;
		
	}
	
	public Pooglins(int id){
		this.id = id;
		
	}
	public Pooglins(int id, Posicion posicionInicial, ServiciosTerreno terreno){
		this.id = id;
		this.oficio = FabricaDeOficio.crearCaminante(new Direccion(), new HabilidadNula());
		this.posicion = posicionInicial;
		this.terreno = terreno;
	}
	
	public void mover() throws MuerteDePooglinException, PooglinGanadorException{
		/*
		 * si el oficio retorna finalizado quiere decir que ya no se pobra moverce siendo del
		 * mismo oficio y su movimiento constara en generar un nuevo tipo de oficio
		 */
		if(this.oficio.estaFinalizado()){
			this.oficio = this.oficio.generarOficioSiguiente(this.terreno, this.posicion);
		}
		/*
		 * si mover es false el Pooglin a muerto.
		 */
		this.oficio.mover(this.terreno, this.posicion);
	}
		
	
	
	public void setOficio(int idOficio) {
		if (this.oficio.getId() != Constantes.CAMINANTE_CAYENTE)
		this.oficio = FabricaDeOficio.crearOficioPorId(idOficio, this.oficio.getDireccion(), this.oficio.habilidad);
	}

	public int getId() {
		return id;
	}

	public Posicion getPosicion() {
		return this.posicion;
	}
	
	public boolean equals(Object otroPooglin){
		return this.id == ((Pooglins) otroPooglin).getId();		
	}
	
	//@Override
	/*public String toString() {
	//	String s = "";
	//	s = "Pooglin ID: " + this.id + "\tPosicion: " + this.posicion.toString();
		return s;
	}*/
	public int getOficioID() {
		// TODO Auto-generated method stub
		return this.oficio.getId();
	}
	public int getHabilidadID() {
		// TODO Auto-generated method stub
		return this.oficio.getHabilidad().getID();
	}
	public void setHabilidad(int idHabilidad) {
		// TODO Auto-generated method stub
		this.oficio.setHabilidad(idHabilidad);
	}
	public Direccion getDireccion() {
		// TODO Auto-generated method stub
		return this.oficio.getDireccion();
	}

	
}
