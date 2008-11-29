package controlador.botoneshabilidades;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;

import vista.BoardGame;

import modelo.habilidadesPooglins.ContenedorHabilidades;
import modelo.habilidadesPooglins.Habilidad;
import modelo.utilitarios.Constants;

public abstract class BotonHabilidad extends JButton implements ActionListener{

	protected BoardGame boardGame;
	protected Habilidad habilidad;
	
	public void accion(String nombreHabilidad){
		habilidad=ContenedorHabilidades.getInstance().obtenerHabilidad(nombreHabilidad);
		boardGame.setHabilidad(habilidad);
	}
}
