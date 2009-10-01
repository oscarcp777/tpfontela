package vista.paneles;

import java.awt.Graphics;
import java.awt.image.BufferedImage;

import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JPanel;

import controlador.ControladorPersistencia;

import modelo.pooglins.Posicion;

import vista.PruebaFlujoVentanas;
import vista.componentes.BotonGrafico;
import vista.componentes.FondoMapa;
import vista.componentes.SpriteSimple;
import vista.manejadores.ItemListenerNiveles;
import vista.manejadores.ManejadorBotonCargar;
import vista.manejadores.ManejadorBotonGuardar;
import vista.manejadores.MouseListenerVolverAMenu;
import vista.manejadores.Niveles;
import vista.utilitarias.ConstantesVista;

public class PanelDeNiveles extends JPanel{
	
	private FondoMapa fondo; 
	private BufferedImage buffer;
	private BotonGrafico botonVolver;
	//private BotonGrafico botonCargar;
	private JComboBox comboNiveles;
	private static final int posBotonesX = 700;
	private static final int posBotonesY = 600;
	
	public PanelDeNiveles(Integer niveles){
		
		Posicion dimension = new Posicion(ConstantesVista.ANCHO_VENTANA,ConstantesVista.ALTO_VENTANA);
		this.fondo = new FondoMapa(ConstantesVista.PANEL_NIVELES);
		this.setLayout(null);
		Niveles[] nivelesString = new Niveles[niveles];
		for (int i = 0; i < niveles; i++) {
			if(i != 0){	
				Niveles nivel = new Niveles();
				nivel.setIdNivel(i);
				nivel.setNombreNivel("Nivel "+(i));
				nivelesString[i] = nivel;
			}
		}
		this.setBounds(0, 0, dimension.getX(), dimension.getY());
		this.comboNiveles = new JComboBox(nivelesString);
		this.comboNiveles.setBounds(posBotonesX-400, posBotonesY-300, 300, 30);
		this.comboNiveles.addItemListener(new ItemListenerNiveles());
		this.botonVolver = new BotonGrafico(new Posicion(posBotonesX, posBotonesY),"volver.png");
		this.botonVolver.addMouseListener(new MouseListenerVolverAMenu());
		this.buffer = new BufferedImage(dimension.getX(), dimension.getY(), BufferedImage.BITMASK);
		/*this.botonCargar = new BotonGrafico(new Posicion(40,  400),"cargar.png");
		this.botonCargar.setLocation(40,  400);
		this.botonCargar.addMouseListener(new ManejadorBotonCargar(new ControladorPersistencia(PruebaFlujoVentanas.mapa)));*/
		
		//this.add(this.botonCargar);
		this.add(this.botonVolver);
		this.add(this.comboNiveles);
		this.add(this.fondo);
		
		
	}
	
	public void paint(Graphics g) {
		// TODO Auto-generated method stub
		fondo.paint(buffer.getGraphics());
		super.paint(buffer.getGraphics());
		g.drawImage(buffer, 0, 0, null);
		botonVolver.paint(buffer.getGraphics());
		//botonCargar.paint(buffer.getGraphics());
		g.drawImage(buffer, 0, 0, null);
	}

}
