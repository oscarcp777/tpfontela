package vista.manejadores;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import vista.PruebaFlujoVentanas;
import vista.componentes.BotonGrafico;

public class ManejadorBotonPausar extends MouseAdapter implements MouseListener {

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		BotonGrafico b = ((BotonGrafico) e.getComponent());
		b.repaint();
		 if(b.estoyApretado()){
		PruebaFlujoVentanas.flujo.pausar();
		 }else{
			 PruebaFlujoVentanas.flujo.play();
		 }
	}

	
	
}
