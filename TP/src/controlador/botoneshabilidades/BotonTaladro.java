package controlador.botoneshabilidades;

import java.awt.event.ActionEvent;

import vista.BoardGame;

import modelo.habilidadesPooglins.ContenedorHabilidades;
import modelo.utilitarios.Constants;

public class BotonTaladro extends BotonHabilidad {

	
	public BotonTaladro(BoardGame boardGame){
		habilidad = ContenedorHabilidades.getInstance().obtenerHabilidad(Constants.NombreHabilidades.TALADRO_ULTRASONICO);
		this.boardGame = boardGame;
	}
	
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		accion(Constants.NombreHabilidades.TALADRO_ULTRASONICO);
	}



}
