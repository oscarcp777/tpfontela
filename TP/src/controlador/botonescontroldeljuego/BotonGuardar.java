package controlador.botonescontroldeljuego;

import interaccion.Juego;

import java.awt.event.ActionEvent;
import java.io.IOException;

import javax.xml.parsers.ParserConfigurationException;

import modelo.utilitarios.Constants;
import modelo.xml.XMLguarda;

public class BotonGuardar extends BotonControladorJuego{

	private Juego juego;
	
	public BotonGuardar(Juego juego){
		this.juego = juego;
	}
	
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		juego.suspend();
		
			try {
				XMLguarda.guardarPartida(Constants.MapasDeJuego.PARTIDA_GUARDADA, juego.getMapa()); //guardo el estado del mapa
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (ParserConfigurationException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		
		
		
	}

}
