package vista.utilitarias;

import vista.componentes.TableroPuntuacion;

public class ContadorTiempo extends Thread {
	private TableroPuntuacion tablero;
	
	public ContadorTiempo(TableroPuntuacion tablero) {
		super();
		this.tablero = tablero;
	}

	@Override
	public void run() {
    	tablero.correrContador();	
		
	}

	
}
