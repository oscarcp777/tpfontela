package controlador;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.JFrame;

import vista.BoardGame;

public class MouseController extends MouseAdapter {

	private JFrame boardGame;
	
	public	MouseController(JFrame boardGame){
		this.boardGame = boardGame;
	}
	
	public void mouseClicked (MouseEvent event){
		((BoardGame)this.boardGame).find(event.getX(),event.getY());		
	}

}
