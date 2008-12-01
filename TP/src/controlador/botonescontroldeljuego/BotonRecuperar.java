package controlador.botonescontroldeljuego;

import interaccion.Juego;

import java.awt.event.ActionEvent;

import modelo.mapaDeJuego.Mapa;
import modelo.mapaDeJuego.Planeta;
import modelo.utilitarios.Constants;
import modelo.xml.XMLcarga;
import controlador.ControlDeJuego;

public class BotonRecuperar extends BotonControladorJuego {

	private ControlDeJuego controlJuego;
	
	public BotonRecuperar(ControlDeJuego controlDeJuego){
		this.controlJuego = controlDeJuego;
	}
	
	
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		controlJuego.nuevoJuego();
		Juego juego = controlJuego.getJuego();
		controlJuego.getBoardGame().setVisible(false);
		XMLcarga xmlcarga = new XMLcarga(Constants.MapasDeJuego.PARTIDA_GUARDADA);
		Planeta planeta = new Planeta(xmlcarga.getInfoNivel());
		Mapa mapaDeJuego = planeta.obtenerMapaDeJuego();
		juego.inicializarJuego(mapaDeJuego);
		controlJuego.setMapa(mapaDeJuego);
		controlJuego.iniciarPartida();
		juego.start();
	}
}
