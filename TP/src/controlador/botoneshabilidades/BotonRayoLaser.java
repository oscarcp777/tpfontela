package controlador.botoneshabilidades;

import java.awt.event.ActionEvent;

import vista.BoardGame;

import modelo.habilidadesPooglins.ContenedorHabilidades;
import modelo.utilitarios.Constants;

public class BotonRayoLaser extends BotonHabilidad {

	public BotonRayoLaser(BoardGame boardGame){
		habilidad = ContenedorHabilidades.getInstance().obtenerHabilidad(Constants.NombreHabilidades.RAYO_LASER);
		this.boardGame = boardGame;
	}
	
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		accion(Constants.NombreHabilidades.RAYO_LASER);
	}

	

}