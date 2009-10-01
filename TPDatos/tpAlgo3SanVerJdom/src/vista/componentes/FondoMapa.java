package vista.componentes;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;

import java.awt.Component;
import java.util.Iterator;

import javax.swing.JComponent;

import modelo.pooglins.Posicion;
import vista.manejadores.MouseListenerActor;
import vista.utilitarias.AnimacionesFondos;
import vista.utilitarias.AnimacionesOficios;
import vista.utilitarias.ListaCircular;

public class FondoMapa extends JComponent {


	private ListaCircular<SpriteSimple> sprites;
	private Iterator<SpriteSimple> iteradorSprites;
			
	public FondoMapa(int idFondo) {
		
		AnimacionesFondos animaciones = AnimacionesFondos.getInstance();
		this.sprites = animaciones.getSecuenciaDeImagen(idFondo);
		this.iteradorSprites = this.sprites.iterator();
		//this.setVisible(true);
		Image i = this.sprites.iterator().next().getImage();
		this.setBounds(0,0,i.getWidth(null),i.getHeight(null));
		
		
	}

	@Override
	public void paint(Graphics g) {
		// TODO Auto-generated method stub
			g.drawImage(this.iteradorSprites.next().getImage(),0, 0, null);

	}

	public Image getImage() {
		// TODO Auto-generated method stub
		return this.iteradorSprites.next().getImage();
	}
	
}
