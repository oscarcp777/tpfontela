package vista.componentes;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.image.BufferedImage;

import javax.swing.JComponent;

import controlador.ControladorPersistencia;

import vista.PruebaFlujoVentanas;
import vista.manejadores.ManejadorBotonGuardar;
import vista.manejadores.ManejadorBotonPausar;
import vista.manejadores.ManejadorBotonRegresar;
import vista.manejadores.MouseListenerButtonRecuperar;

import modelo.pooglins.Posicion;

public class BotoneraOpcionesMenu extends JComponent {
	
	private BotonGrafico botonGuardar;
	private BotonGrafico botonCargar;
	private BotonGrafico botonRegresar;
	private BotonGrafico botonPausar;
	
	public BotoneraOpcionesMenu(Posicion posicion){
		this.setLocation(posicion.getX(),posicion.getY());
		crearBotones();
		posicionarBotones();
		setearHandlers();
		agregarComponentes();
	}

	private void setearHandlers() {
		// TODO Auto-generated method stub
		//this.botonCargar.addMouseListener(new ManejadorBotonCargar(new ControladorPersistencia(PruebaFlujoVentanas.mapa)));
		this.botonPausar.addMouseListener(new ManejadorBotonPausar());
		this.botonRegresar.addMouseListener(new ManejadorBotonRegresar());
		this.botonGuardar.addMouseListener(new ManejadorBotonGuardar(new ControladorPersistencia(PruebaFlujoVentanas.flujo.getMapa())));
	}

	private void posicionarBotones() {
		this.botonGuardar.setLocation(20, 20);
		//this.botonCargar.setLocation(20, this.botonGuardar.getHeight() + 20);
		this.botonRegresar.setLocation(25 + this.botonGuardar.getWidth(), 20);
		this.botonPausar.setLocation(25 + this.botonGuardar.getWidth(), this.botonGuardar.getHeight()+ 20);
		this.setSize(this.botonGuardar.getWidth()*2+45,this.botonGuardar.getHeight()*2 +30 );
	}

	private void crearBotones() {
		this.botonGuardar = new BotonGrafico(new Posicion(0, 0),"guardar.png");
		//this.botonCargar = new BotonGrafico(new Posicion(0, 0),"cargar.png");
		this.botonRegresar = new BotonGrafico(new Posicion(0, 0),"volver.png");
		this.botonPausar = new BotonGrafico(new Posicion(0,0),"jugar.png","pausar.png",0,true);
	}

	private void agregarComponentes() {
		this.add(this.botonGuardar);
		//this.add(this.botonCargar);
		this.add(this.botonRegresar);
		this.add(this.botonPausar);
	}

	@Override
	public void paint(Graphics g) {
		// TODO Auto-generated method stub
		BufferedImage b = new BufferedImage(this.getWidth(),this.getHeight(),BufferedImage.BITMASK);
		//this.botonCargar.paint(b.getGraphics());
		this.botonGuardar.paint(b.getGraphics());
		this.botonRegresar.paint(b.getGraphics());
		this.botonPausar.paint(b.getGraphics());
		g.drawImage(b, this.getX(), this.getY(), null);
	}
	

	
	
}

