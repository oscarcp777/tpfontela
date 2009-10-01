package vista.paneles;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.image.BufferedImage;

import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JPanel;

import modelo.entornoDeJuego.Mapa;
import modelo.pooglins.Posicion;

public class VentanaPrincipal extends JFrame {
	
	//private JComponent componente;
	public VentanaPrincipal() {
		//this.setResizable(false);
	}


	public void setPanel(JComponent componente) {
		/*if(this.componente != null)	this.remove(this.componente);
		this.componente = componente;*/
		this.getContentPane().removeAll();
		this.getContentPane().add(componente);
		
		/*this.componente.setFocusable(true);
		//this.setComponentZOrder(this.componente, 0);*/
		
	}
	
	public void iniciarRonda(Mapa mapa, PanelDeJuego panel){
		while (mapa.hayPooglins()) {
			
			BufferedImage b = new BufferedImage(this.getWidth(), this.getHeight(),BufferedImage.BITMASK);
			mapa.correrRondaMovimientosPooglin();
			System.out.println("lala");
			//panel.dibujar((b.getGraphics()));
			//this.getGraphics().drawImage(b, 4,30, null);
			try {
				Thread.sleep(150);
			} catch (InterruptedException e1) {
				// TODO Auto-generated catch block

				e1.printStackTrace();

			}
		}
	}

	
}
