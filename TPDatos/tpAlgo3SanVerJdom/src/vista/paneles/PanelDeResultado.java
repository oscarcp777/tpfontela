package vista.paneles;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.image.BufferedImage;

import javax.swing.BorderFactory;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.Border;

import modelo.pooglins.Posicion;
import vista.PruebaFlujoVentanas;
import vista.componentes.BotonGrafico;
import vista.componentes.FondoMapa;
import vista.manejadores.MouseListenerVolverAMenu;
import vista.utilitarias.ConstantesVista;

public class PanelDeResultado extends JPanel{
	
	private FondoMapa fondo; 
	private BufferedImage buffer;
	private BotonGrafico botonVolver;
	private BotonGrafico botonSalir;
	private JLabel ganadores;
	private JLabel perdedores;
	private JLabel resultado;
	private JLabel ganadoresText;
	private JLabel perdedoresText;
	private static final int posBotonesX = 650;
	private static final int posBotonesY = 600;
	private final int posTextosChicos = posBotonesX-330;
	private final int posNro = posBotonesX -50;
	private final int textoGrande = posBotonesX-500;
	
	public PanelDeResultado(){
		
		Posicion dimension = new Posicion(ConstantesVista.ANCHO_VENTANA,ConstantesVista.ALTO_VENTANA);
		this.fondo = new FondoMapa(ConstantesVista.PANEL_RESULTADOS);
		this.setLayout(null);
		this.setBounds(0, 0, dimension.getX(), dimension.getY());
		this.botonVolver = new BotonGrafico(new Posicion(posBotonesX, posBotonesY),"volver.png");
		this.botonVolver.addMouseListener(new MouseListenerVolverAMenu());
		this.botonSalir = new BotonGrafico(new Posicion(posBotonesX, posBotonesY),"volver.png");
		this.botonSalir.addMouseListener(new MouseListenerVolverAMenu());
		this.buffer = new BufferedImage(dimension.getX(), dimension.getY(), BufferedImage.BITMASK);
		ganadores = crearLabel(new Posicion(posNro,posBotonesY-270),((Integer)PruebaFlujoVentanas.mapa.getCantidadGanadores()).toString());
		ganadoresText= crearLabel(new Posicion(posTextosChicos,posBotonesY-300),"El numero de Pooglins ganadores es: ");
		ganadoresText.setBounds(posTextosChicos, posBotonesY-300, 250, 30);
		perdedores = crearLabel(new Posicion(posNro,posBotonesY-210),((Integer)(PruebaFlujoVentanas.mapa.getMaximaCantidadDePooglins()-PruebaFlujoVentanas.mapa.getCantidadGanadores())).toString());
		perdedoresText= crearLabel(new Posicion(posTextosChicos,posBotonesY-240),"El numero de Pooglins muertos es: ");
		perdedoresText.setBounds(posTextosChicos, posBotonesY-240, 250, 30);
		String result = "Ha perdido vualva a intentarlo.";
		if(PruebaFlujoVentanas.mapa.gane()) result = "Felicitaciones ha ganado este nivel.";
		resultado = crearLabel(new Posicion(posBotonesX-300,posBotonesY-100),result);
		resultado.setFont(new Font("Times New Roman",Font.BOLD,40));
		resultado.setBounds(textoGrande, posBotonesY-150, 700, 50);	
		resultado.setBorder(BorderFactory.createBevelBorder(5));
		this.add(perdedoresText);
		this.add(ganadoresText);
		this.add(ganadores);
		this.add(perdedores);
		this.add(resultado);
		this.add(this.botonVolver);
		this.add(botonSalir);
		this.add(this.fondo);
		
		
	}
	
	private JLabel crearLabel(Posicion pos, String texto) {
		JLabel l1 = new JLabel();
		l1.setText(texto);
		
		l1.setBackground(Color.blue);
		l1.setFont(new Font("Times New Roman",Font.BOLD,16));
		l1.setForeground(Color.GREEN);
		l1.setHorizontalAlignment(JLabel.CENTER);
		pos.setY(pos.getY()-25);
		l1.setBounds(pos.getX(),pos.getY(), 30, 20);
		return l1;
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
