package vista.paneles;

import java.awt.Graphics;
import java.awt.image.BufferedImage;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JPanel;

import modelo.pooglins.Posicion;
import vista.componentes.BotonGrafico;
import vista.componentes.FondoMapa;
import vista.componentes.SpriteSimple;
import vista.manejadores.MouseListenerInicioGuardados;
import vista.manejadores.MouseListenerInicioJuego;
import vista.manejadores.MouseListenerSalir;
import vista.utilitarias.ConstantesVista;


public class PanelPrincipal extends JPanel {
	
	private FondoMapa fondo; 
	private BufferedImage buffer;
	private BotonGrafico botonInicioJuego;
	private BotonGrafico botonInicioGuardado;
	private BotonGrafico botonCerrar;
	private static final int posBotonesX = 220;
	private static final int posBotonesY = 550;
	
	public PanelPrincipal(){
				
		Posicion dimension = new Posicion(ConstantesVista.ANCHO_VENTANA,ConstantesVista.ALTO_VENTANA);
		this.setLayout(null);
		this.setBounds(0,0,dimension.getX(),dimension.getY());
		this.fondo = new FondoMapa(ConstantesVista.PANEL_PRINCIPAL);
		this.botonInicioJuego = new BotonGrafico(new Posicion(posBotonesX, posBotonesY),"jugar.png");
		this.botonInicioJuego.addMouseListener(new MouseListenerInicioJuego());
		this.botonInicioGuardado = new BotonGrafico(new Posicion(posBotonesX+200, posBotonesY),"cargarPartida.png");
		this.botonInicioGuardado.addMouseListener(new MouseListenerInicioGuardados());
		this.botonCerrar = new BotonGrafico(new Posicion(posBotonesX+400, posBotonesY),"salir.png");
		this.botonCerrar.addMouseListener(new MouseListenerSalir());
		this.buffer = new BufferedImage(dimension.getX(), dimension.getY(), BufferedImage.BITMASK);
		//this.setSize(dimension.getX(), dimension.getY());
		this.add(this.fondo);
		this.add(this.botonInicioGuardado);
		this.add(this.botonInicioJuego);
		this.add(this.botonCerrar);

		
		
			
	}
	
	public void paint(Graphics g) {
		// TODO Auto-generated method stub
		fondo.paint(buffer.getGraphics());
		botonCerrar.paint(buffer.getGraphics());
		botonInicioJuego.paint(buffer.getGraphics());
		botonInicioGuardado.paint(buffer.getGraphics());
		//super.paint(buffer.getGraphics());
		g.drawImage(buffer, 0,0, null);
	}


}
