package vista;

import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class BoardFinJuego extends JPanel{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public void perdio(){
		JOptionPane.showMessageDialog( this,"Ha perdido","The Pooglins",JOptionPane.WARNING_MESSAGE );		
	}
	
	public void gano(){
		JOptionPane.showMessageDialog( this,"Ha pasado de nivel","The Pooglins",JOptionPane.WARNING_MESSAGE );		
	}
	
	public void pasoTodosLosNiveles(){
		JOptionPane.showMessageDialog( this,"Ha pasado todos los niveles. \n Ha ganado el juego!!!","The Pooglins",JOptionPane.WARNING_MESSAGE );
	}
}
