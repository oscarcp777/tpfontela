package vista.utilitarias;


import modelo.entornoDeJuego.Mapa;

public class FlujoDeJuego {

private static final int INTERVALO_AGREGADO_POOGLIN = 10;
private boolean pausa;
private boolean onPlay;
private Mapa mapaDeJuego;
private int framesSpeed;
private int cantidadPooglinsEnJuego;
private int cantidadMaximaPooglins;
private int intervaloEntrepooglins;
private boolean quedaTiempo;


public FlujoDeJuego(Mapa mapa, int framesSpeed){
	this.mapaDeJuego = mapa;
	this.framesSpeed = framesSpeed;
	this.quedaTiempo = true;
	if (mapa != null){
		this.cantidadPooglinsEnJuego = mapa.getCantidadPooglins();
		this.cantidadMaximaPooglins = mapa.getMaximaCantidadDePooglins();
		this.intervaloEntrepooglins = 0;
		this.comenzarJuego();
		this.play();	
	}else{
		this.finalizarJuego();
		this.pausar();
	}
	
}
private boolean hayJugadores(){
	return this.mapaDeJuego.hayPooglins();
}

private boolean sigoJugando(){
	return this.hayJugadores() && onPlay && this.quedaTiempo;
}

public void CorrerHiloJuego(){
		if(!this.hayJugadores()){
			this.agregarJugador();
		}
		while (this.sigoJugando()) {
			if(!this.pausa){
				if (this.puedoAgregarJugador())
				this.agregarJugador();
			
	     		mapaDeJuego.correrRondaMovimientosPooglin();
				this.intervaloEntrepooglins++;
			try {
					Thread.sleep(this.framesSpeed);
				} catch (InterruptedException e1) {
					e1.printStackTrace();
				}
			}	
		 }
		
		System.out.println("Fin de juego");
}


public boolean terminoPartidaCompleta(){
	return onPlay;
}

private boolean puedoAgregarJugador() {
	// TODO Auto-generated method stub
	return (this.intervaloEntrepooglins == FlujoDeJuego.INTERVALO_AGREGADO_POOGLIN && this.cantidadPooglinsEnJuego<this.cantidadMaximaPooglins);
}
private void agregarJugador() {

	this.mapaDeJuego.agregarPooglin();	
	this.cantidadPooglinsEnJuego++;
	this.reiniciarContadorIntervalo();
	
}

private void reiniciarContadorIntervalo() {
	this.intervaloEntrepooglins = 0;	
}

public void play(){
	this.pausa = false;
}

public void pausar(){
	this.pausa = true;
}

public void comenzarJuego(){
	this.onPlay = true;
}

public void finalizarJuego(){
	this.onPlay = false;
}
public Mapa getMapa() {
	// TODO Auto-generated method stub
	return this.mapaDeJuego;
}
public void finDelTiempo() {
	this.quedaTiempo = false;
	
}
public boolean estoyPausado() {
	// TODO Auto-generated method stub
	return this.pausa;
}
}
