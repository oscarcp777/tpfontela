package modelo.entornoDeJuego;

import java.util.Iterator;
import java.util.LinkedList;
import modelo.excepciones.MuerteDePooglinException;
import modelo.excepciones.PooglinGanadorException;
import modelo.pooglins.Observador;
import modelo.pooglins.Pooglins;
import modelo.pooglins.Posicion;

public class EquipoPooglins implements EjecutadorDeRondas{

	
	private LinkedList<Pooglins> equipo;
	private int ganadores;
	private int ultimoId;
	private int cantidadDePooglins;
	public int getGanadores() {
		return ganadores;
	}

	private Observadores observadores;
	
	public EquipoPooglins(){
		this.ganadores = 0;
		this.equipo =new LinkedList<Pooglins>();
		this.observadores = new Observadores();
		this.ultimoId = 0;
	}
	
	public void aumentarGanadores(){
		this.ganadores++;
	}
	
	public Pooglins obtenerPooglin(int id){
		Pooglins pooglinActual = null;
		Iterator<Pooglins> iterador = this.equipo.iterator();
		while (iterador.hasNext()){
			pooglinActual = iterador.next();
			if( pooglinActual.getId() == id){
				return pooglinActual;
			}
		}
		return pooglinActual;
	}
	public void setOficio(int idPooglin, int idOficio){
		this.obtenerPooglin(idPooglin).setOficio(idOficio);
		this.observadores.actualizar(new EstadoPooglin(this.obtenerPooglin(idPooglin)));
	}
	
	public void setHabilidad(int id, int idHabilidad){
		this.obtenerPooglin(id).setHabilidad(idHabilidad);
		this.observadores.actualizar(new EstadoPooglin(this.obtenerPooglin(id)));
	}
	private void add(Pooglins pooglin){
		this.equipo.add(pooglin);
	}
	
	public void eliminarPooglin(int id){
		Pooglins aux = new Pooglins(id);
		this.equipo.remove(aux);
		
	}

	private Iterator<Pooglins> iterator(){
		return this.equipo.iterator();
	}
	
	public void correrRondaMovimientosPooglin() {
		
		// TODO Auto-generated method stub
		Iterator<Pooglins> iteradorPooglins = this.iterator();
		while(iteradorPooglins.hasNext() && !(this.equipo.size() == 0)){
			Pooglins pooglinActual = iteradorPooglins.next();
			try {
		    	pooglinActual.mover();
		    	this.observadores.actualizar(new EstadoPooglin(pooglinActual));
		    	//System.out.println(pooglinActual);
		    }catch (MuerteDePooglinException e) {
			    System.out.println("pooglin "+pooglinActual+" muerto");
		    	this.observadores.eventoMuertePooglin(pooglinActual.getId());
		    	iteradorPooglins.remove();
		    	
		    	
		    }catch (PooglinGanadorException e) {
		    	System.out.println("pooglin "+pooglinActual+" ganador");
		    	this.observadores.eventoPooglinGanador(pooglinActual.getId());
		    	//this.aumentarGanadores();
		    	iteradorPooglins.remove();
		    }
		}
		    
	}
	
	public void suscribirObservador(Observador obs){
		this.observadores.suscribirObservador(obs);
	}
public void agregarPooglinDesdeEstado(EstadoPooglin estado, ServiciosTerreno terreno){
	Pooglins p = new Pooglins(estado, terreno);
	this.add(p);
	this.ultimoId = estado.getId();
}
	
	public void agregarPooglin(Posicion posPooglin, ServiciosTerreno terreno){
		Pooglins p = new Pooglins(ultimoId+1,posPooglin, terreno);
		this.add(p);	
		this.observadores.actualizarAgregarPooglin(new EstadoPooglin(p));
		this.ultimoId++;
	}

	public int getCantidadPooglins(){
		return this.equipo.size();
	}
	
	public boolean hayPooglins() {
		// TODO Auto-generated method stub
		return !(this.equipo.size() == 0);
	}

	public int getCantidadDePooglins() {
		return cantidadDePooglins;
	}

	public void setCantidadDePooglins(int cantidadDePooglins) {
		this.cantidadDePooglins = cantidadDePooglins;
	}
}	

