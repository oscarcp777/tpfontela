package vista.manejadores;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import vista.utilitarias.NavegadorDeVentanas;

public class MouseListenerInicioGuardados extends MouseAdapter{
	
	public MouseListenerInicioGuardados() {
		// TODO Auto-generated constructor stub
	}
	
    public void mouseClicked(MouseEvent e) {
		
		NavegadorDeVentanas.getInstance().crearPanelDePartidasGuardadas();
	}
}
