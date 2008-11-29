package controlador.botonescontroldeljuego;

import java.awt.event.ActionEvent;

import controlador.ControlDeJuego;

public class BotonComenzar extends BotonControladorJuego{

	private ControlDeJuego control;
		
	public BotonComenzar(ControlDeJuego control){
		this.control = control;
	}

	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		control.lanzarJuego();
		control.getJuego().setReloj(control.getBoardGame().getReloj());
		control.getBoardLoadGame().setVisible(false);
	}

}
