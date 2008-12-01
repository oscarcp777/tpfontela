package controlador.botonescontroldeljuego;

import interaccion.Juego;

import java.awt.event.ActionEvent;

import vista.BoardTemporizador;

public class BotonPausa extends BotonControladorJuego {

	private Juego juego;
	private BoardTemporizador tempo;
	
	public BotonPausa(Juego juego,BoardTemporizador tempo){
		this.juego = juego;
		this.tempo = tempo;
	}
	
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		juego.suspend();
		tempo.getCronometro().detenerReloj();
	}

}
