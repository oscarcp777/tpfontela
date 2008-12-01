package controlador.botoneshabilidades;

import java.awt.event.ActionEvent;

import modelo.habilidadesPooglins.ContenedorHabilidades;
import modelo.utilitarios.Constants;
import vista.BoardGame;

public class BotonTeletransportacion extends BotonHabilidad {

	public BotonTeletransportacion(BoardGame boardGame){
		habilidad = ContenedorHabilidades.getInstance().obtenerHabilidad(Constants.NombreHabilidades.TELETRANSPORTACION);
		this.boardGame = boardGame;
	}
	
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		
		accion(Constants.NombreHabilidades.TELETRANSPORTACION);
	}

}
