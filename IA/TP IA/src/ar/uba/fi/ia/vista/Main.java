package ar.uba.fi.ia.vista;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
/**
 * 
 * @author oscar
 *
 */
public class Main {
	public static void main(String args[])
	   {
		  final VentanaPrincipal mainEntry= new VentanaPrincipal();
		  mainEntry.setVisible(true);
		   WindowListener wndListenEvt = new WindowAdapter() {
				public void windowClosing(WindowEvent e) {
					mainEntry.setVisible(false);
					System.exit(0);
				}
			};
			mainEntry.addWindowListener(wndListenEvt);
	   
	   }

}
