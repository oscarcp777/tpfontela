package vista.manejadores;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import vista.componentes.BotonGrafico;

public class ManejadorBotonActivable extends MouseAdapter {

@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		BotonGrafico b = (BotonGrafico) e.getSource();
		b.swich();
		
	}

	
}
