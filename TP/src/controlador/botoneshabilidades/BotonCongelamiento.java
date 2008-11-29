package controlador.botoneshabilidades;

import java.awt.event.ActionEvent;

import modelo.habilidadesPooglins.ContenedorHabilidades;
import modelo.utilitarios.Constants;

import vista.BoardGame;

public class BotonCongelamiento extends BotonHabilidad {

	public BotonCongelamiento(BoardGame boardGame){
		habilidad = ContenedorHabilidades.getInstance().obtenerHabilidad(Constants.NombreHabilidades.CONGELAMIENTO);
		this.boardGame = boardGame;
	}
	
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		accion(Constants.NombreHabilidades.CONGELAMIENTO);
	}





}
