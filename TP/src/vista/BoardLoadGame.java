package vista;

import java.awt.Dimension;
import java.awt.Panel;
import java.awt.TextArea;
import java.awt.TextField;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;

import javax.swing.JButton;
import javax.swing.JFrame;

import modelo.utilitarios.Constants;

import com.sun.xml.internal.bind.v2.runtime.reflect.Accessor.SetterOnlyReflection;

import controlador.ControlDeJuego;
import controlador.MouseController;

public class BoardLoadGame extends JFrame implements MouseMotionListener{

	private JButton botonComenzarJuego = new JButton("Comenzar a jugar");
	private JButton botonSalir = new JButton("Salir");
	
	public BoardLoadGame (ControlDeJuego controlDeJuego){
        super("The Pooglins");
		setPreferredSize(new Dimension(500, 400));
		setSize(new Dimension(500,400));
		setLocationRelativeTo(null);
		setResizable(false);
		Panel panelBotones = new Panel();
		panelBotones.add(botonComenzarJuego);
		panelBotones.add(botonSalir);
		botonComenzarJuego.setPreferredSize(new Dimension(150, 50));
		botonSalir.setPreferredSize(new Dimension(150,50 ));
		
		botonComenzarJuego.addActionListener(controlDeJuego.getListenerBotonComenzar());
		botonSalir.addActionListener(controlDeJuego.getListenerBotonSalir());
		add("South",panelBotones);
		
		addMouseListener(new MouseController(this));
		addMouseMotionListener(this);
		
		TextArea text=new TextArea(Constants.MensajeBienvenida.MENSAJE);
		text.setBackground(getBackground().BLACK);
		text.setForeground(getForeground().WHITE);
		
		text.setPreferredSize(new Dimension(200,300));
		
		add("North", text);
	

	}
	
	public void mouseDragged(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	public void mouseMoved(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

}
