package controlador.botoneshabilidades;

import java.awt.event.ActionEvent;

import modelo.habilidadesPooglins.ContenedorHabilidades;
import modelo.utilitarios.Constants;
import vista.BoardGame;

public class BotonTunel extends BotonHabilidad {

	public BotonTunel(BoardGame boardGame){
		habilidad = ContenedorHabilidades.getInstance().obtenerHabilidad(Constants.NombreHabilidades.TUNEL_ELECTROMAGNETICO);
		this.boardGame = boardGame;
	}
	
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		accion(Constants.NombreHabilidades.TUNEL_ELECTROMAGNETICO);
	}


}
