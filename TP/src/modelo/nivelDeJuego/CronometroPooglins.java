package modelo.nivelDeJuego;

import interaccion.Juego;

import java.util.Timer;
import java.util.TimerTask;

import modelo.mapaDeJuego.Mapa;

public class CronometroPooglins {

	private int duracionTurno;
	private Mapa mapa;
	private Juego juego;
	private Tempo temporizador;
	private boolean continuar;
		
	public CronometroPooglins(int turno,Mapa mapa,Juego juego){
		this.duracionTurno = turno;
        Timer t = new Timer();
        this.mapa=mapa;
        this.juego = juego;
        this.temporizador = new Tempo();
        continuar = true;
        t.schedule(temporizador, duracionTurno,4070);
        
	}
	
	public void pararTemporizador(){		
		this.continuar=false;	
	}
	
	public void continuarTemporizador(){		
		this.continuar=true;	
	}
	
	private class Tempo extends TimerTask {
			
		public void run() {
			
				if(continuar){
					
				}
			}
        }
	}
	

