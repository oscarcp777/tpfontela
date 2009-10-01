package vista.componentes;


import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Rectangle;
import java.io.IOException;
import java.net.URL;
import javax.imageio.ImageIO;
import javax.swing.JComponent;

import vista.manejadores.MouseListenerActor;


@SuppressWarnings("serial")
public class SpriteSimple implements Sprite{

	private Image i;
	private String path;
	public SpriteSimple(String path, int posx, int posy) {
		//this.addMouseListener(new MouseListenerActor());
		this.path = path;
				URL url;
	//	System.out.println("El path entrante es: "+path);
		try {
			url = getClass().getClassLoader().getResource(this.path);
		//	System.out.println("La URL vale: "+url);
				this.i = ImageIO.read(url);
				
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		/*this.setSize( new Dimension(this.i.getWidth(null),this.i.getHeight(null)));
		this.setLocation(posx, posy);
		this.setBackground(Color.green);*/
		
	}
    public Image getImage(){
    	return this.i;
    	
    }
	public void dibujar(Graphics g) {
		// TODO Auto-generated method stub
		
	}
	//@Override
	/*public void paint(Graphics g) {
		// TODO Auto-generated method stub
		
	}
	public void dibujar(Graphics g) {
		//this.paint(g);
	//	g.drawImage(i, this.getX(),this.getY(), this.i.getWidth(null), this.i.getHeight(null), null);
		
	}*/
	
}
