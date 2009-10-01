package vista.manejadores;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.LinkedList;

import vista.componentes.BotonGrafico;

public class ManejadorGrupoBotones extends MouseAdapter {
	private LinkedList<BotonGrafico> botones;
	
	public ManejadorGrupoBotones(LinkedList<BotonGrafico> botones){
		this.botones = botones;
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		BotonGrafico boton = (BotonGrafico)e.getSource();
		if(!boton.estoyApretado()){
			for (BotonGrafico b : this.botones) {
				if (b.estoyApretado()) b.swich();			
			}
		}
		else{
			for (BotonGrafico b : this.botones) {
				if (b.estoyApretado()) b.swich();			
			}
			boton.swich();
		}
	}

	
}
