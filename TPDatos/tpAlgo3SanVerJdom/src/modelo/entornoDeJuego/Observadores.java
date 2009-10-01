package modelo.entornoDeJuego;

import java.util.Iterator;
import java.util.LinkedList;

import modelo.pooglins.Observador;
import modelo.pooglins.Posicion;

public class Observadores implements Observador {
	
	private LinkedList<Observador> observadores;
	
	public Observadores() {
		this.observadores = new LinkedList<Observador>();
	}
	
    public synchronized void actualizar(Posicion posicion){
    	Iterator<Observador> iterador = observadores.iterator();
    	while (iterador.hasNext()){
    		iterador.next().actualizar(posicion);
    	}
    }
	public synchronized void eventoMuertePooglin(int id) {
    	Iterator<Observador> iterador = observadores.iterator();
    	while (iterador.hasNext()){
    		iterador.next().eventoMuertePooglin(id);
    		}
	}
	public synchronized void eventoPooglinGanador(int id) {
    	Iterator<Observador> iterador = observadores.iterator();
    	while (iterador.hasNext()){
    		iterador.next().eventoPooglinGanador(id);
    	}
	}
	public synchronized void suscribirObservador( Observador obs){
		this.observadores.add(obs);
	}
	public synchronized void actualizar(EstadoPooglin estado) {
    	Iterator<Observador> iterador = observadores.iterator();
    	while (iterador.hasNext()){
    		iterador.next().actualizar(estado);
    	}
	}

	
	public synchronized void actualizarAgregarPooglin(EstadoPooglin estado) {
		// TODO Auto-generated method stub
		for (Observador o : this.observadores) {
			o.actualizarAgregarPooglin(estado);
		}
	}
}
