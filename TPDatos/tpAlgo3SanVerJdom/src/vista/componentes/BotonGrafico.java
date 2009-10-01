package vista.componentes;

import java.awt.Graphics;
import java.awt.Image;
import java.awt.event.MouseAdapter;

import javax.swing.JComboBox;
import javax.swing.JComponent;

import org.w3c.dom.views.AbstractView;

import vista.manejadores.ManejadorBotonActivable;

import modelo.pooglins.Posicion;

public class BotonGrafico extends JComponent {

	private Image imagenOn;
	private Image imagenOff;
	private boolean estoyPresionado;
	private int idBoton;

	
	public BotonGrafico(Posicion pos, String imagenOn, String imagenOff, int idBoton,boolean esActivable){
		this.idBoton = idBoton;
		this.estoyPresionado = false;
		setActivable(esActivable);
		cargarImagenes(pos, imagenOn, imagenOff);
		this.setSize(this.imagenOff.getWidth(null),this.imagenOff.getHeight(null));
		this.setLocation(pos.getX(),pos.getY());
		this.setBounds(pos.getX(),pos.getY(),this.imagenOff.getWidth(null),this.imagenOff.getHeight(null));
		
	}

	public BotonGrafico(Posicion pos, String imagenOff){
		this.idBoton = 0;
		this.estoyPresionado = false;
		this.imagenOff= new SpriteSimple(imagenOff,pos.getX(),pos.getY()).getImage();
		this.setSize(this.imagenOff.getWidth(null),this.imagenOff.getHeight(null));
		this.setLocation(pos.getX(),pos.getY());
		this.setBounds(pos.getX(),pos.getY(),this.imagenOff.getWidth(null),this.imagenOff.getHeight(null));

	}


	
	private void setActivable(boolean esActivable) {
		if (esActivable) this.addMouseListener(new ManejadorBotonActivable());
	}

	private void cargarImagenes(Posicion pos, String imagenOn, String imagenOff) {
		this.imagenOff= new SpriteSimple(imagenOff,pos.getX(),pos.getY()).getImage();
		this.imagenOn= new SpriteSimple(imagenOn,pos.getX(),pos.getY()).getImage();
	}

	public Image getImagenOn() {
		return imagenOn;
	}

	public Image getImagenOff() {
		return imagenOff;
	}

	public int getIdBoton() {
		return idBoton;
	}
	
	public boolean estoyApretado(){
		return this.estoyPresionado;
	}
	@Override
	public void paint(Graphics g) {
		// TODO Auto-generated method stub
		g.drawImage(this.getImagenEstado(), this.getX(), this.getY(), null);
	}
    public void setImagenOff(String imagen){
    	this.imagenOff = new SpriteSimple(imagen, 0, 0).getImage();
    }
/*	public void dibujar(Graphics g){
		g.drawImage(this.getImagenEstado(), this.getX(), this.getY(), null);
	}*/
	private Image getImagenEstado(){
		if (estoyPresionado)return this.imagenOn;
		return this.imagenOff;
	}
	public void swich(){
		this.estoyPresionado = !this.estoyPresionado;
	}

}