package vista.paneles;

import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.util.Iterator;
import java.util.LinkedList;

import javax.swing.JComboBox;
import javax.swing.JPanel;

import controlador.ControladorPersistencia;

import modelo.entornoDeJuego.Mapa;
import modelo.pooglins.Posicion;
import vista.componentes.BotonGrafico;
import vista.componentes.FondoMapa;
import vista.manejadores.ItemListenerNiveles;
import vista.manejadores.ItemListenerRecuperarNiveles;
import vista.manejadores.MouseListenerVolverAMenu;
import vista.manejadores.Niveles;
import vista.utilitarias.ConstantesVista;

public class PanelDePartidasGuardadas extends JPanel{
	
	private FondoMapa fondo; 
	private BufferedImage buffer;
	private BotonGrafico botonVolver;
	private JComboBox comboJuegosGuardados;
	private static final int posBotonesX = 700;
	private static final int posBotonesY = 600;

	
	public PanelDePartidasGuardadas(LinkedList<String> listaDeGuardados, Mapa mapa){
		
		Posicion dimension = new Posicion(ConstantesVista.ANCHO_VENTANA,ConstantesVista.ALTO_VENTANA);
		this.fondo = new FondoMapa(ConstantesVista.PANEL_GUARDADOS);
		this.setLayout(null);
		Niveles[] nivelesString = new Niveles[listaDeGuardados.size()];
		Iterator<String> iterador = listaDeGuardados.iterator();
		for (int i = 0; i < listaDeGuardados.size(); i++) {
			if(i != 0){	
				Niveles nivel = new Niveles();
				nivel.setIdNivel(i);
				nivel.setNombreNivel(iterador.next());
				nivelesString[i] = nivel;
			}
		}
		this.setBounds(0, 0, dimension.getX(), dimension.getY());
		this.comboJuegosGuardados = new JComboBox(nivelesString);
		this.comboJuegosGuardados.setBounds(posBotonesX-400, posBotonesY-300, 300, 30);
		this.comboJuegosGuardados.addItemListener(new ItemListenerRecuperarNiveles(new ControladorPersistencia(mapa)));
		this.botonVolver = new BotonGrafico(new Posicion(posBotonesX, posBotonesY),"volver.png");
		this.botonVolver.addMouseListener(new MouseListenerVolverAMenu());
		this.buffer = new BufferedImage(dimension.getX(), dimension.getY(), BufferedImage.BITMASK);
		
		this.add(this.botonVolver);
		this.add(this.comboJuegosGuardados);
		this.add(this.fondo);
		
		
	}
	
	public void paint(Graphics g) {
		// TODO Auto-generated method stub
		fondo.paint(buffer.getGraphics());
		super.paint(buffer.getGraphics());
		g.drawImage(buffer, 0, 0, null);
		botonVolver.paint(buffer.getGraphics());
		g.drawImage(buffer, 0, 0, null);
	}


}
