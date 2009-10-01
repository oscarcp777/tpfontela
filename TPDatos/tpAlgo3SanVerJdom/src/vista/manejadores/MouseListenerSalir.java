package vista.manejadores;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;


public class MouseListenerSalir extends MouseAdapter {

	public void mouseClicked(MouseEvent e) {
		System.exit(0);
	}

}
