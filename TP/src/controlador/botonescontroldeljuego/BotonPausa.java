package controlador.botonescontroldeljuego;

import interaccion.Juego;

import java.awt.event.ActionEvent;

public class BotonPausa extends BotonControladorJuego {

	private Juego juego;
	
	public BotonPausa(Juego juego){
		this.juego = juego;
	}
	
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		juego.suspend();
	}

}
