package vista.manejadores;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import vista.PruebaFlujoVentanas;
import vista.utilitarias.NavegadorDeVentanas;

public class ManejadorBotonRegresar extends MouseAdapter implements
		MouseListener {

	@Override
	public void mouseClicked(MouseEvent e) {
		PruebaFlujoVentanas.flujo.pausar();
		PruebaFlujoVentanas.flujo.finalizarJuego();
		NavegadorDeVentanas.getInstance().crearPanelPrincipal();
	}

	
	
}
