package vista.utilitarias;

import java.awt.image.BufferedImage;
import java.util.HashMap;
import java.util.LinkedList;

import javax.swing.JComponent;
import javax.swing.JPanel;

/*RODOLFO*/
import javax.swing.JFrame;
/*RODOLFO*/


import modelo.entornoDeJuego.EstadoPooglin;
import modelo.entornoDeJuego.Mapa;
import modelo.pooglins.Observador;
import modelo.pooglins.Posicion;
import vista.PruebaFlujoVentanas;
import vista.paneles.PanelDeJuego;
import vista.paneles.PanelDeNiveles;
import vista.paneles.PanelDePartidasGuardadas;
import vista.paneles.PanelDeResultado;

import vista.paneles.PanelPrincipal;
import vista.paneles.VentanaPrincipal;

public class NavegadorDeVentanas  implements Observador{
	
	
	private static NavegadorDeVentanas instance;
	private JFrame ventana;
	private Mapa mapa;
	private HashMap<Integer, JPanel> paneles;
	private final int PANEL_PRINCIPAL = 1;
	private final int PANEL_NIVELES = 2;
	private final int PANEL_JUEGOS_GUARDADOS = 3;
	private final int PANEL_DE_JUEGO = 4;
	private final int PANEL_RESULTADOS = 5;
	
	private NavegadorDeVentanas(){
		paneles = new HashMap<Integer, JPanel>();
	}
	
	public static NavegadorDeVentanas getInstance() {
		if(instance == null){
			instance = new NavegadorDeVentanas();
			instance.ventana = new JFrame();
		}
		return instance;
	}
	
	public JFrame getVentana() {
		return instance.ventana;
	}

	public void crearPanelPrincipal(){
		if(instance.paneles.get(instance.PANEL_PRINCIPAL)==null){
			instance.paneles.put(instance.PANEL_PRINCIPAL, new PanelPrincipal());
		}
		setPanelNuevo(instance.paneles.get(instance.PANEL_PRINCIPAL));
	}
	
	public void crearPanelDeNiveles(){
		if(instance.paneles.get(instance.PANEL_NIVELES)==null){
			ControladorPanelNivel controlador = new ControladorPanelNivel();
			String cantidadNiveles = controlador.leerArchivo();;
			Integer canNiveles = new Integer(Integer.parseInt(cantidadNiveles));
			instance.paneles.put(instance.PANEL_NIVELES, new PanelDeNiveles(canNiveles));
		}
		setPanelNuevo(instance.paneles.get(instance.PANEL_NIVELES));
	}
	
	public void crearPanelDePartidasGuardadas(){
		if(instance.paneles.get(instance.PANEL_JUEGOS_GUARDADOS)==null){
			ControladorPanelGuardados controlador = new ControladorPanelGuardados();
			LinkedList<String> juegosGuardados = controlador.leerArchivo();
			instance.paneles.put(instance.PANEL_JUEGOS_GUARDADOS, new PanelDePartidasGuardadas(juegosGuardados,this.mapa));
		}
		setPanelNuevo(instance.paneles.get(instance.PANEL_JUEGOS_GUARDADOS));
	}
	
	public void crearPanelDeResultados(){
		if(instance.paneles.get(instance.PANEL_RESULTADOS)==null){	
			instance.paneles.put(instance.PANEL_RESULTADOS, new PanelDeResultado());
		}
		setPanelNuevo(instance.paneles.get(instance.PANEL_RESULTADOS));
	}

	public void crearPanelDeJuego(Mapa mapaModelo) {
		if(instance.paneles.get(instance.PANEL_DE_JUEGO)== null){	
			instance.paneles.put(instance.PANEL_DE_JUEGO, new PanelDeJuego(PruebaFlujoVentanas.mapa));			
		}else{
			
			JPanel panel = instance.paneles.get(instance.PANEL_DE_JUEGO);
			PanelDeJuego juego = (PanelDeJuego)panel;
			juego.reinicializar(PruebaFlujoVentanas.mapa);
				
		}
		setPanelNuevo(instance.paneles.get(instance.PANEL_DE_JUEGO));
		mapaModelo.suscribirObservador(this);
	}

	private void setPanelNuevo(JPanel panelDeJuego) {
		instance.ventana.getContentPane().removeAll();
		instance.ventana.getContentPane().add(panelDeJuego);
		instance.ventana.setDefaultCloseOperation(instance.ventana.EXIT_ON_CLOSE);
		instance.ventana.setLayout(null);
		instance.ventana.setSize(panelDeJuego.getWidth(), panelDeJuego.getHeight());
		instance.ventana.setVisible(true);
		instance.ventana.repaint();
		
	}
	

	/*public void refrescarVentana(){
		this.instance.ventana.repaint();
	}*/
	public void actualizar(EstadoPooglin estado) {
		this.instance.ventana.repaint();
	}

	public void actualizar(Posicion posicion) {
		// TODO Auto-generated method stub
		this.instance.ventana.repaint();
	}

	public void eventoMuertePooglin(int id) {
		// TODO Auto-generated method stub
		this.instance.ventana.repaint();
	}

	public void eventoPooglinGanador(int id) {
		// TODO Auto-generated method stub
		this.instance.ventana.repaint();
	}


	public void actualizarAgregarPooglin(EstadoPooglin estado) {
		// TODO Auto-generated method stub
		//this.instance.ventana.repaint();	
	}

	
}
