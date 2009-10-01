package vista.componentes;


import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Rectangle;
import java.util.Iterator;

import javax.swing.Box;
import javax.swing.JComponent;
import javax.swing.JLabel;

import controlador.ControladorDePooglin;
import vista.manejadores.MouseListenerActor;
import vista.utilitarias.AnimacionesOficios;
import vista.utilitarias.ConstantesVista;
import vista.utilitarias.ConversorDeEscalas;
import modelo.constantes.Constantes;
import modelo.entornoDeJuego.EstadoPooglin;
import modelo.movimientos.Direccion;
import modelo.pooglins.Posicion;

public class Actor extends JComponent{


	private Iterator<SpriteSimple> iteradorSpritesIzq;
	private Iterator<SpriteSimple> iteradorSpritesDer;
	private int idPooglin;
	private int oficio;
	private Direccion direccion;
	private Image imagenActual;			
		
	public Actor(int idPooglin, int idOficio, Posicion p,Direccion dir, ControladorDePooglin controlador){
		if (dir != null){
		this.direccion = dir;
		}else{
			this.direccion = new Direccion();
		}
		this.oficio = idOficio;
		this.idPooglin = idPooglin;
		AnimacionesOficios animaciones = AnimacionesOficios.getInstance();
		this.iteradorSpritesIzq = animaciones.getSecuenciaDeImagen(idOficio+100).iterator();
		this.iteradorSpritesDer = animaciones.getSecuenciaDeImagen(idOficio).iterator();
		Image i = this.iteradorSpritesIzq.next().getImage();
		this.setBounds(p.getX(),p.getY(),i.getWidth(null),i.getHeight(null));
		this.addMouseListener(new MouseListenerActor(controlador));
	}

	
	public String toString() {
		String s = "";
		s = this.idPooglin+" "+oficio+" "+this.getX()+","+this.getY();
		return s;
	}

	public void paint(Graphics g){
		
		g.drawImage(this.imagenActual, this.getX(), this.getY(), null); 
	}

	public int getOficio() {
		return oficio;
	}

	public int getIdPooglin() {
		return idPooglin;
	}
	
	public Image getImage() {
		// TODO Auto-generated method stub
		return null;
	}

	public void setEstado(EstadoPooglin estado){
		this.idPooglin = estado.getId();
		if ( ( estado.getOficio() == Constantes.CAMINANTE_CAYENTE && estado.getHabilidad() == Constantes.PARACAIDISTA_ESPACIAL) 
				|| ( estado.getOficio() == ConstantesVista.CAMINANTE_CAYENTE_IZQ && estado.getHabilidad() == ConstantesVista.PARACAIDISTA_ESPACIAL_IZQ) ){
			this.oficio = estado.getHabilidad();	
		}else{
			this.oficio = estado.getOficio();	
		}
		this.iteradorSpritesIzq = AnimacionesOficios.getInstance().getSecuenciaDeImagen(this.oficio+100).iterator();
		this.iteradorSpritesDer = AnimacionesOficios.getInstance().getSecuenciaDeImagen(this.oficio).iterator();
		this.direccion = estado.getDireccion();
		
	}
	
	public void setPosicion(Posicion posicionRelativaMapa){
	/* 
	 * La posicion relativa al mapa del modelo no coincide con la posicion de dibujo. Uno arranca en la esquina inferior
	 * derecha y el otro en la esquina superior izquierda.
	 */
		Posicion p = ConversorDeEscalas.ajustarEscala(posicionRelativaMapa);
		//this.setVisible(false);
		this.setLocation(p.getX(), p.getY()- ConstantesVista.ALTURA_POOLGIN + ConstantesVista.ALTO_PARCELA); 
		
	}


	public void animar() {
		// TODO Auto-generated method stub
		if (this.direccion.getDireccionX( )== -1 ){
			this.imagenActual = this.iteradorSpritesIzq.next().getImage();
		}else{
			this.imagenActual = this.iteradorSpritesDer.next().getImage();
		}
	}

	
}
