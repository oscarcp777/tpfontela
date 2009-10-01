package vista.componentes;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.io.IOException;
import java.net.URL;
import java.util.Iterator;
import java.util.List;

import javax.imageio.ImageIO;
import javax.swing.JComponent;

import vista.manejadores.MouseListenerActor;
import vista.utilitarias.ListaCircular;

public class SpriteSecuencia extends JComponent implements Sprite {
	private ListaCircular<Image> imagenes;
	private Iterator<Image> iteradorImagenes;
	public SpriteSecuencia(List<String> listaImagenes, int posx, int posy) {
		this.setLocation(posx, posy);
		this.imagenes = new ListaCircular<Image>();
		Iterator<String> iter = listaImagenes.iterator();
		URL url;
		while (iter.hasNext()) {
			try {
				url = getClass().getClassLoader().getResource(iter.next());
					this.imagenes.add(ImageIO.read(url));
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		this.iteradorImagenes = this.imagenes.iterator(); 
		this.setSize( new Dimension(this.iteradorImagenes.next().getWidth(null),this.iteradorImagenes.next().getHeight(null)));
	}
	
	public Image getImage() {
		// TODO Auto-generated method stub
		return this.iteradorImagenes.next();
	}

	@Override
	public void paint(Graphics g) {
		// TODO Auto-generated method stub
		g.drawImage(this.iteradorImagenes.next(), 0,0, this.getWidth(), this.getHeight(), null);
	}

	public void dibujar(Graphics g) {
		this.paint(g);
		
	}

}
