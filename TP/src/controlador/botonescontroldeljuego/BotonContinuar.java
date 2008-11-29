package controlador.botonescontroldeljuego;

import interaccion.Juego;

import java.awt.event.ActionEvent;

public class BotonContinuar extends BotonControladorJuego {

	private Juego juego;
	
	public BotonContinuar(Juego juego){
		this.juego = juego;
	}
	
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		juego.resume();
	}

}
