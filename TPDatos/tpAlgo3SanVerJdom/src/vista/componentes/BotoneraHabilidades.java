package vista.componentes;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;
import java.util.LinkedList;

import javax.swing.ButtonGroup;
import javax.swing.JComponent;
import javax.swing.JLabel;

import controlador.ControladorDePooglin;

import modelo.constantes.Constantes;
import modelo.pooglins.HabilidadesDisponibles;
import modelo.pooglins.Posicion;
import vista.manejadores.ManejadorEventosBotonesHabilidad;
import vista.manejadores.ManejadorGrupoBotones;
import vista.utilitarias.ObservadorLabels;


/*
 * SOLO CAMBIE LOS NOMBRES DE MAYUS MINUS A todo minusculas
 * para que no hay problemas en otros S.O.
 * */
public class BotoneraHabilidades extends JComponent implements ObservadorLabels {
	
	private LinkedList<BotonGrafico> listaBotones;
	private LinkedList<JLabel> listaLabel;
	private ControladorDePooglin controlador;
	private ManejadorEventosBotonesHabilidad handler;
	private ManejadorGrupoBotones grupoBotones;
	
	
	public BotoneraHabilidades(ControladorDePooglin controlador, Posicion pos, HabilidadesDisponibles disponibles){
		this.setLocation(new Point(pos.getX(),pos.getY()));
		this.setSize(600, 150);
		this.controlador = controlador;
		this.controlador.suscribirObservador(this);
		this.listaBotones = new LinkedList<BotonGrafico>();
		this.listaLabel = new LinkedList<JLabel>();
		this.handler = ManejadorEventosBotonesHabilidad.getInstance(this.controlador);
		this.agregarBotones();
		this.crearLabels(disponibles);
		this.grupoBotones = new ManejadorGrupoBotones(this.listaBotones);
		for (BotonGrafico b : this.listaBotones) {
			b.addMouseListener(this.grupoBotones);			
		}
		
	}
	
	private void agregarBotones() {
	
		
	/*Cambie las imagenes de los botones de habilidades*/
		Posicion pos = new Posicion(this.getX()+20,this.getY()+60);
		BotonGrafico b1 = new BotonGrafico(pos,"boton_presionado_plato_30x45.png","boton_plato_30x45.png", Constantes.PARACAIDISTA_ESPACIAL,true);
		b1.addMouseListener(this.handler);
		this.listaBotones.add(b1);
		this.add(b1);
		BotonGrafico b2 = new BotonGrafico(new Posicion(this.getX()+100,this.getY()+60),"boton_presionado_camina_30x45.png","boton_camina_30x45.png", Constantes.TELEPORTER,true);
		b2.addMouseListener(this.handler);
		this.listaBotones.add(b2);
		this.add(b2);
		BotonGrafico b3 = new BotonGrafico(new Posicion(this.getX()+180,this.getY()+60),"boton_presionado_tunelelectro_30x45.png","boton_tunelelectro_30x45.png", Constantes.CONSTRUCTOR,true);
		b3.addMouseListener(this.handler);
		this.listaBotones.add(b3);
		this.add(b3);
		BotonGrafico b4 = new BotonGrafico(new Posicion(this.getX()+260,this.getY()+60),"boton_presionado_taladrador_30x45.png","boton_taladrador_30x45.png", Constantes.TALADRADOR,true);
		b4.addMouseListener(this.handler);
		this.listaBotones.add(b4);
		this.add(b4);
		BotonGrafico b5 = new BotonGrafico(new Posicion(this.getX()+340,this.getY()+60),"boton_presionado_laser_30x45.png","boton_laser_30x45.png", Constantes.LASERMAN,true);
		b5.addMouseListener(this.handler);
		this.listaBotones.add(b5);
		this.add(b5);
		BotonGrafico b6 = new BotonGrafico(new Posicion(this.getX()+420,this.getY()+60),"boton_presionado_congelado_30x45.png","boton_congelado_30x45.png", Constantes.CONGELADO,true);
		b6.addMouseListener(this.handler);
		this.listaBotones.add(b6);
		this.add(b6);
	}

	private void crearLabels(HabilidadesDisponibles disponibles){
		JLabel label = new JLabel();
		for (BotonGrafico b : this.listaBotones) {
		    label = crearLabel(new Posicion(b.getX(),b.getY()),b.getIdBoton(),((Integer)disponibles.obtenerDisponiblesPorIdDeNivel(b.getIdBoton())).toString());
			this.listaLabel.add(label);
			this.add(label);
		    
		}
	}
	private JLabel crearLabel(Posicion pos, int id, String texto) {
		JLabel l1 = new JLabel();
		l1.setName(((Integer)id).toString());
		l1.setText(texto);
		l1.setOpaque(true);
		l1.setBackground(null);
		l1.setFont(new Font("Times New Roman",Font.BOLD,16));
		l1.setForeground(Color.BLUE);
		l1.setHorizontalAlignment(JLabel.CENTER);
		pos.setY(pos.getY()-25);
		l1.setBounds(pos.getX(),pos.getY(), 30, 20);
		return l1;
	}
	

	public LinkedList<BotonGrafico> getBotones(){
		return this.listaBotones;
	}
	
	public LinkedList<JLabel> getLabels(){
		return this.listaLabel;
	}
	
	@Override
	public void paint(Graphics g) {
		// TODO Auto-generated method stub
		
		//g.fill3DRect(this.getX(), this.getY(), this.getWidth(), this.getHeight(), true);
		
		for (BotonGrafico b : this.listaBotones) {
			b.paint(g);			
		}
		for (JLabel l : this.listaLabel) {
		BufferedImage labelBuffer = new BufferedImage(l.getWidth(),l.getHeight(),BufferedImage.BITMASK);
			l.paint(labelBuffer.getGraphics());
			g.drawImage(labelBuffer, l.getX(), l.getY(), null);
		}
		
	
	}

	public void actualizar(int id, int cantidad) {
		// TODO Auto-generated method stub
		for (JLabel l : this.listaLabel) {
			if(l.getName().equals(((Integer)id).toString())){
				l.setText(((Integer) cantidad).toString());
			}
					}
	}
}
