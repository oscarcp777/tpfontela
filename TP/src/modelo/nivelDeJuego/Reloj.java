package modelo.nivelDeJuego;

import java.util.Observable;
import java.util.Timer;
import java.util.TimerTask;

import modelo.mapaDeJuego.Mapa;
import vista.BoardTemporizador;

public class Reloj extends Observable {
	
	private Integer minutos;
	private Integer segundos;
	private Mapa mapa;
	private boolean continuar;

	public Reloj(BoardTemporizador reloj, Mapa mapa){
		this.minutos = 05;
		this.mapa=mapa;
		segundos = 00;
		Timer t = new Timer();
		t.schedule(new Temporizador(), 100,1000);
		this.addObserver(reloj);
		continuar=true;
	}
	
	public synchronized void actualizarTiempo(){
		if(this.segundos==00 && this.minutos==00){
			this.mapa.matarPooglins();
		}else{
		    if(this.segundos==00){
		    	this.minutos--;
		    	this.segundos=59;
		    }else{
			    this.segundos--;
		    }			
		}			

	    setChanged();
		notifyObservers();
	}	
	
	public String mostrarTiempo(){
		return this.minutos.toString()+"min"+""+this.segundos.toString()+
		"seg"+" "+"para llegar a la nave";
	}
	
	public void detenerReloj(){
		this.continuar=false;
	}
	
	public void continuarReloj(){
		this.continuar=true;
	}
	
	private class Temporizador extends TimerTask {
		
		public void run() {
			if(continuar){
				actualizarTiempo();
				mostrarTiempo();
			}
		}        
	}

}
