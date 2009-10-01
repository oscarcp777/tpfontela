package vista.paneles;

import java.awt.Graphics;
import java.awt.Transparency;
import java.awt.image.BufferedImage;
import java.util.HashMap;
import java.util.Iterator;
import javax.swing.JPanel;

import com.sun.org.apache.bcel.internal.generic.NEW;

import modelo.constantes.Constantes;
import modelo.entornoDeJuego.EstadoPooglin;
import modelo.entornoDeJuego.Mapa;
import modelo.pooglins.Observador;
import modelo.pooglins.Posicion;
import vista.PruebaFlujoVentanas;
import vista.componentes.Actor;
import vista.componentes.BotonGrafico;
import vista.componentes.BotoneraHabilidades;
import vista.componentes.BotoneraOpcionesMenu;
import vista.componentes.FondoMapa;
import vista.componentes.SpriteSimple;
import vista.componentes.TableroPuntuacion;
import vista.componentes.TerrenoNivel;
import vista.utilitarias.ConstantesVista;
import vista.utilitarias.ContadorTiempo;
import vista.utilitarias.ConversorDeEscalas;
import vista.utilitarias.ImagenesParcela;
import controlador.ControladorDePooglin;

public class PanelDeJuego extends JPanel implements Observador {

	private HashMap<Integer, Actor> actores;
	private TerrenoNivel terreno;
	private FondoMapa fondo;
	private TableroPuntuacion tableroTiempo;
    private Mapa mapa;
	private ControladorDePooglin controlador;
	private BotoneraHabilidades botones;
	private BufferedImage bufferEstatico;
	private BotoneraOpcionesMenu opcionesMenu;
	

	public PanelDeJuego(Mapa mapa){
		Posicion dimension = new Posicion(ConstantesVista.ANCHO_VENTANA,ConstantesVista.ALTO_VENTANA);
		this.mapa = mapa;
		this.setBounds(0,0,dimension.getX(),dimension.getY());
		this.setLayout(null);
		//this.setSize(getDimension(mapa).getX()+10, getDimension(mapa).getY()+50);
		this.controlador = new ControladorDePooglin(mapa);
	 	crearActores();
    	crearBotonera();
    	crearTablero();
    	crearOpcionesMenu();
    	if(PruebaFlujoVentanas.nivelEnJuego != 0) this.fondo = new FondoMapa(PruebaFlujoVentanas.nivelEnJuego);
    	else this.fondo = new FondoMapa(ConstantesVista.NIVEL_UNO);
     	this.terreno = new TerrenoNivel(mapa.getEstadoTerreno(), mapa.getAnchoTerreno(), mapa.getAltoTerreno()+200);
     	this.bufferEstatico = new BufferedImage(dimension.getX(), dimension.getY(), Transparency.BITMASK);
    	mapa.suscribirObservador(this);
       	System.out.println("dimencion de pantalla: "+getDimension(mapa).getX()+"  "+getDimension(mapa).getY());
	}

	public void reinicializar(Mapa mapa){
		Posicion dimension = new Posicion(ConstantesVista.ANCHO_VENTANA,ConstantesVista.ALTO_VENTANA);
		this.mapa = mapa;
		this.setBounds(0,0,dimension.getX(),dimension.getY());
		this.setLayout(null);
		this.controlador = new ControladorDePooglin(mapa);
		this.removeAll();
	 	crearActores();
    	crearBotonera();
    	crearTablero();
    	crearOpcionesMenu();
     	this.fondo = new FondoMapa(ConstantesVista.NIVEL_SIETE);
     	this.terreno = new TerrenoNivel(mapa.getEstadoTerreno(), mapa.getAnchoTerreno(), mapa.getAltoTerreno()+200);
     	this.bufferEstatico = new BufferedImage(dimension.getX(), dimension.getY(), Transparency.BITMASK);
    	mapa.suscribirObservador(this);
       	System.out.println("dimencion de pantalla: "+getDimension(mapa).getX()+"  "+getDimension(mapa).getY());
	}
	
	private void crearTablero() {
		// TODO Auto-generated method stub
		this.tableroTiempo = new TableroPuntuacion(new Posicion(500,640),this.mapa.getTiempoInicial());
		this.add(this.tableroTiempo);
		ContadorTiempo c = new ContadorTiempo(this.tableroTiempo);
		c.start();
	}

	private void crearOpcionesMenu() {
		// TODO Auto-generated method stub
		this.opcionesMenu = new BotoneraOpcionesMenu(new Posicion(615,600));
		this.add(opcionesMenu);
	}

	private void crearBotonera() {
		this.botones = new BotoneraHabilidades(this.controlador,new Posicion(12,620),this.mapa.obtenerHabilidades());
     	this.add(this.botones);
		for (BotonGrafico b : this.botones.getBotones()) {
			this.add(b);
			
		}
	}

	private Posicion getDimension(Mapa mapa) {
		Posicion dimension = ConversorDeEscalas.ajustarEscala(new Posicion(mapa.getAnchoTerreno(), mapa.getAltoTerreno()));
		return dimension;
	}

	private void crearActores() {
		this.actores = new HashMap<Integer, Actor>();
		if (this.mapa.hayPooglins()){
			for (EstadoPooglin e : this.mapa.getEstadoPooglins()) {
				Actor act = new Actor(e.getId(),e.getOficio(),new Posicion(e.getPosicionX(),e.getPosicionY()),e.getDireccion(),this.controlador);
				this.actores.put(e.getId(), act);
				this.add(act);
				
			}
		}
	}

	public void actualizar(Posicion posicion) {
		//
		Posicion pos = ConversorDeEscalas.ajustarEscala(posicion);
		SpriteSimple s = ImagenesParcela.getInstance().getImagen(this.mapa.getTerreno().getMaterialActual(posicion).getTipoDeMaterial());
		if( s.getImage().getHeight(null) > ConstantesVista.ALTO_PARCELA){
			this.terreno.dibujarParcela(new Posicion(pos.getX(), pos.getY()-ConstantesVista.ALTURA_POOLGIN + ConstantesVista.ALTO_PARCELA ), this.mapa.getTerreno().getMaterialActual(posicion).getTipoDeMaterial());

		}else{
			this.terreno.dibujarParcela(pos, this.mapa.getTerreno().getMaterialActual(posicion).getTipoDeMaterial());

		} 
		
	}
	
	public void actualizar(EstadoPooglin estado) {
		// TODO Auto-generated method stub
		Actor act =  this.actores.get(estado.getId());
		if (act.getOficio() != estado.getOficio()) {
				act.setEstado(estado);
			}	
			act.setPosicion(new Posicion(estado.getPosicionX(), estado.getPosicionY()));
			act.animar();
			this.actores.put(estado.getId(), act);		
		}
	
	public void eventoMuertePooglin(int id) {
		this.remove(this.actores.get(id));
		this.actores.remove(id);

	}

	public void eventoPooglinGanador(int id) {
		this.remove(this.actores.get(id));
		this.actores.remove(id);
	}

	@Override
	public void paint(Graphics g) {
		//TODO Auto-generated method stub
		BufferedImage bufferDinamico = new BufferedImage(getDimension(mapa).getX(), getDimension(mapa).getY(), Transparency.BITMASK);
		this.fondo.paint(bufferEstatico.getGraphics());
		this.terreno.paint(bufferEstatico.getGraphics());
	    Iterator<EstadoPooglin> i = this.mapa.getEstadoPooglins().iterator();
		while (i.hasNext() && this.actores.size() >0) {
				this.actores.get(i.next().getId()).paint(bufferDinamico.getGraphics());
		}
		this.botones.paint(bufferEstatico.getGraphics());
		this.opcionesMenu.paint(bufferEstatico.getGraphics());
		this.tableroTiempo.paint(bufferEstatico.getGraphics());
		g.drawImage(bufferEstatico, 0, 0, null);
		g.drawImage(bufferDinamico, 0, 0, null);
		
				
		//super.paint(g);
		
	}

	public void actualizarAgregarPooglin(EstadoPooglin estado) {
		// TODO Auto-generated method stub
		Actor act = new Actor(estado.getId(),estado.getOficio(),new Posicion(estado.getPosicionX(),estado.getPosicionY()),estado.getDireccion(),this.controlador);
		this.actores.put(estado.getId(), act);
		this.add(act);
	}

	
	
}
