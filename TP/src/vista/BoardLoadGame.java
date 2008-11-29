package vista;

import java.awt.Dimension;
import java.awt.Panel;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;

import javax.swing.JButton;
import javax.swing.JFrame;

import controlador.ControlDeJuego;
import controlador.MouseController;

public class BoardLoadGame extends JFrame implements MouseMotionListener{

	private JButton botonComenzarJuego = new JButton("Comenzar a jugar");
	private JButton botonSalir = new JButton("Salir");
	
	public BoardLoadGame (ControlDeJuego controlDeJuego){
        super("The Pooglins");
		setPreferredSize(new Dimension(300, 300));
		setSize(350,300);
		setLocationRelativeTo(null);
		Panel panelBotones = new Panel(); 
		panelBotones.add(botonComenzarJuego);
		panelBotones.add(botonSalir);
		botonComenzarJuego.setPreferredSize(new Dimension(300, 100));
		botonSalir.setPreferredSize(new Dimension(300, 100));

		botonComenzarJuego.addActionListener(controlDeJuego.getListenerBotonComenzar());
		botonSalir.addActionListener(controlDeJuego.getListenerBotonSalir());
	
		this.add(panelBotones);
		
		addMouseListener(new MouseController(this));
		addMouseMotionListener(this);

	}
	
	public void mouseDragged(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	public void mouseMoved(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

}
