package controlador.botonescontroldeljuego;

import interaccion.Juego;

import java.awt.event.ActionEvent;

import vista.BoardTemporizador;

public class BotonContinuar extends BotonControladorJuego {

	private Juego juego;
	private BoardTemporizador tempo;
	
	public BotonContinuar(Juego juego,BoardTemporizador tempo){
		this.juego = juego;
		this.tempo = tempo;
	}
	
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		juego.resume();
		tempo.getCronometro().continuarReloj();
	}

}
