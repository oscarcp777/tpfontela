package controlador.botoneshabilidades;

import java.awt.event.ActionEvent;

import vista.BoardGame;

import modelo.habilidadesPooglins.ContenedorHabilidades;
import modelo.utilitarios.Constants;

public class BotonPlatilloVolador extends BotonHabilidad{

	public BotonPlatilloVolador(BoardGame boardGame){
		habilidad = ContenedorHabilidades.getInstance().obtenerHabilidad(Constants.NombreHabilidades.PLATILLO_VOLADOR);
		this.boardGame = boardGame;
	}
	
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		accion(Constants.NombreHabilidades.PLATILLO_VOLADOR);
	}


}
