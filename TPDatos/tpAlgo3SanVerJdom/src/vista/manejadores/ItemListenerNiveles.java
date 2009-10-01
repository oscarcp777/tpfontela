package vista.manejadores;

import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;

import vista.PruebaFlujoVentanas;
import vista.utilitarias.NavegadorDeVentanas;

import modelo.entornoDeJuego.Mapa;

public class ItemListenerNiveles implements ItemListener {

	public void itemStateChanged(ItemEvent e) {
		
		Niveles nivel = (Niveles)e.getItem(); 
		if(e.getStateChange() != 2){
			
			try {
				nivel.guardarIdNivel("XMLPersistencia/NroNivel.prs");
				
			} catch (Exception f) {System.out.println("No guardo nronivel");	}
			
			PruebaFlujoVentanas.newGame(nivel.getIdNivel());
		    //NavegadorDeVentanas.getInstance().crearPanelDeJuego(PruebaFlujoVentanas.mapa);
			//PruebaFlujoVentanas.jugando = true;
		 //  NavegadorDeVentanas.getInstance().crearPanelDePrueba(mapaModelo);

		}
	}
}
