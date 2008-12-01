package vista;

import java.awt.Panel;
import java.util.Observable;
import java.util.Observer;

import javax.swing.JLabel;

import modelo.mapaDeJuego.Mapa;
import modelo.nivelDeJuego.Reloj;


public class BoardTemporizador implements Observer{
	
	private Reloj reloj;
	private JLabel cronometro;
	private Panel panel;

	
	public BoardTemporizador (Panel panel, Mapa mapa){

		this.reloj = new Reloj(this,mapa);
		this.cronometro = new JLabel();
		this.cronometro.setFocusable(true);
		this.panel = panel;
	}
	
	public void mostrarReloj (){
		this.cronometro.setText( this.reloj.mostrarTiempo() );
		this.panel.add(cronometro);        	
	}

	public Reloj getCronometro() {		
		return this.reloj;		
	}
	
	@Override
	public void update(Observable o, Object arg) {		
		mostrarReloj();		
	}
}
