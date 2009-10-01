package vista.manejadores;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import modelo.constantes.Constantes;

import vista.componentes.Actor;

import controlador.ControladorDePooglin;
import controlador.excepciones.HabilidadInactivaException;


public class MouseListenerActor extends MouseAdapter implements MouseListener {

    private ControladorDePooglin controladorDePooglin;
	
	public MouseListenerActor(ControladorDePooglin controladorDePooglin){
		this.controladorDePooglin  = controladorDePooglin;
	}
	
	@Override
	public void mouseClicked(MouseEvent e) {
		Actor actor = (Actor)e.getComponent();
		System.out.println("CLICK SOBRE POOGLIN");
		try {
			this.controladorDePooglin.setHabilidad(actor.getIdPooglin());
		} catch (HabilidadInactivaException e1) {
			// TODO Auto-generated catch block
			//this.controladorDePooglin.activarHabilidad(Constantes.HABILIDAD_NULA);
		}
	}
}
