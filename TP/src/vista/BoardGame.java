package vista;

import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Panel;
import java.awt.Toolkit;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.util.Iterator;
import java.util.Observable;
import java.util.Observer;

import javax.swing.JButton;
import javax.swing.JFrame;



import modelo.elementosDelMapa.Poogling;
import modelo.habilidadesPooglins.Habilidad;
import modelo.mapaDeJuego.Mapa;
import modelo.nivelDeJuego.ColPooglins;
import modelo.nivelDeJuego.Reloj;
import modelo.propiedadesDeElementos.Posicion;
import controlador.ControlDeJuego;
import controlador.MouseController;
import controlador.botonescontroldeljuego.BotonContinuar;
import controlador.botonescontroldeljuego.BotonGuardar;
import controlador.botonescontroldeljuego.BotonPausa;
import controlador.botonescontroldeljuego.BotonRecuperar;
import controlador.botonescontroldeljuego.BotonSalir;
import controlador.botoneshabilidades.BotonCongelamiento;
import controlador.botoneshabilidades.BotonPlatilloVolador;
import controlador.botoneshabilidades.BotonRayoLaser;
import controlador.botoneshabilidades.BotonTaladro;
import controlador.botoneshabilidades.BotonTeletransportacion;
import controlador.botoneshabilidades.BotonTunel;

public class BoardGame extends JFrame implements Observer, MouseMotionListener{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private Mapa mapa; 
	private Panel botonera;
	private Habilidad habilidad;
	private ControlDeJuego controlador;
	private BoardTemporizador boardTemporizador;
	private int height;
	private int width;
			

	public BoardTemporizador getBoardTemporizador() {
		return boardTemporizador;
	}

	public int getHeight() {
		return height;
	}

	public int getWidth() {
		return width;
	}

	public BoardGame(Mapa mapa,ControlDeJuego controlador){
		setTitle("Game Pooglins");
		this.mapa = mapa;
		setPreferredSize(new Dimension(200, 200));
		height = mapa.getDimension().getAlto();
		width = mapa.getDimension().getAncho();
		setSize(width, height);
		this.setResizable(false);
		centrarFrame();
		addMouseListener(new MouseController(this));
		addMouseMotionListener(this);		
		botonera = new Panel();
			
		this.add("South", botonera); //agrego los botones abajo del frame
		this.controlador = controlador;
		
		boardTemporizador = new BoardTemporizador(botonera,mapa);
		boardTemporizador.mostrarReloj();
	}
	
	public void centrarFrame(){
		Toolkit kit = getToolkit();
	    Dimension screenSize = kit.getScreenSize();
	    int screenWidth = screenSize.width;
	    int screenHeight = screenSize.height;
	    Dimension windowSize = getSize();
	    int windowWidth = windowSize.width;
	    int windowHeight = windowSize.height;
	    
	    int upperLeftX = (screenWidth - windowWidth)/2;
	    int upperLeftY = (screenHeight - windowHeight)/2;
	    
	    setLocation(upperLeftX, upperLeftY);    
	}
	
	public void paint (Graphics g){
		
		g.translate(getInsets().left, getInsets().top);
		BoardTerreno boardTerreno = new BoardTerreno(this);
		BoardNave boardNave = new BoardNave(this);
		BoardPooglin boardPooglin = new BoardPooglin(this);
		boardTerreno.pintarTerreno(mapa);
		boardPooglin.pintarPooglin(mapa);
		boardNave.pintarNave(mapa);
				
	}
	
	public void find(int x, int y) {    	
		
		ColPooglins colPooglins = controlador.getJuego().getPooglingsEnPlaneta();
		Posicion posicionMouse = new Posicion(x,y);
		Iterator<Poogling> it = colPooglins.iterator();
		boolean encontroAlpooglin = false;
		
		do{
			Poogling pooglingClick = it.next();
			Posicion posicionPooglingClick = new Posicion(pooglingClick.obtenerPosicion().getPosicionX()*30,pooglingClick.obtenerPosicion().getPosicionY()*30-5);
			if((posicionPooglingClick.diferenciaEnX(posicionMouse)<=20)&&(posicionPooglingClick.diferenciaEnY(posicionMouse)<=20)){//si el rango en donde clickeo es menor o igual a 10 seteo la habilidad
			pooglingClick.setHabilidad(habilidad);
			encontroAlpooglin=true; //para que no le aplique la habilidad a 2 pooglins superpuestos, se la aplica al primero que encuentre.
			}
		}while(it.hasNext()&&!encontroAlpooglin);
		
	}
	
	public void cargarTamanioYfuente(JButton button){
		Font fuenteBoton = new Font("Times New Roma",Font.ITALIC,9);
		Dimension dimensionBoton = new Dimension(100,20);
		botonera.setPreferredSize(new Dimension(300,100));
		button.setPreferredSize(dimensionBoton);
		button.setFont(fuenteBoton);
	}
	
	
	public void cargarBotones(){
			
		//cargo los botones de las habilidades
		BotonTaladro botonTaladro = new BotonTaladro(this);
		cargarTamanioYfuente(botonTaladro);
		botonTaladro.setLabel("Taladro");
		botonera.add(botonTaladro);
		botonTaladro.addActionListener(controlador.getListenerBotonTaladro());
		BotonRayoLaser botonRayoLaser = new BotonRayoLaser(this);
		cargarTamanioYfuente(botonRayoLaser);
		botonRayoLaser.setLabel("Rayo Laser");
		botonera.add(botonRayoLaser); 
		botonRayoLaser.addActionListener(controlador.getListenerBotonRayoLaser());
		BotonCongelamiento botonCongelamiento = new BotonCongelamiento(this);
		cargarTamanioYfuente(botonCongelamiento);
		botonCongelamiento.setLabel("Congelamiento");
		botonera.add(botonCongelamiento);
		botonCongelamiento.addActionListener(controlador.getListenerBotonCongelamiento());
		BotonPlatilloVolador botonPlatilloVolador = new BotonPlatilloVolador(this);
		cargarTamanioYfuente(botonPlatilloVolador);
		botonPlatilloVolador.setLabel("Platillo");
		botonera.add(botonPlatilloVolador);
		botonPlatilloVolador.addActionListener(botonPlatilloVolador);
		BotonTunel botonTunel = new BotonTunel(this);
		cargarTamanioYfuente(botonTunel);
		botonTunel.setLabel("Tunel");
		botonera.add(botonTunel);
		botonTunel.addActionListener(controlador.getListenerBotonTunel());
		BotonTeletransportacion botonTeletransportacion = new BotonTeletransportacion(this);
		cargarTamanioYfuente(botonTeletransportacion);
		botonTeletransportacion.setLabel("Teletransportar");
		botonera.add(botonTeletransportacion);
		botonTeletransportacion.addActionListener(controlador.getListenerBotonTeletransportacion());
		
		//cargo los botones del primer frame (BoardLoadGame)
		BotonGuardar botonGuardar = new BotonGuardar(controlador.getJuego());
		cargarTamanioYfuente(botonGuardar);
		botonGuardar.setLabel("Guardar");
		botonera.add(botonGuardar);
		botonGuardar.addActionListener(controlador.getListenerBotonGuardar());
		
		BotonRecuperar botonRecuperar = new BotonRecuperar(controlador);
		cargarTamanioYfuente(botonRecuperar);
		botonRecuperar.setLabel("Recuperar");
		botonera.add(botonRecuperar);
		botonRecuperar.addActionListener(controlador.getListenerBotonRecuperar());
		
		
		BotonContinuar botonContinuar = new BotonContinuar(controlador.getJuego(),boardTemporizador);
		cargarTamanioYfuente(botonContinuar);
		botonContinuar.setLabel("Continuar");
		botonera.add(botonContinuar);
		botonContinuar.addActionListener(controlador.getListenerBotonContinuar());
		
		BotonPausa botonPausa = new BotonPausa(controlador.getJuego(),boardTemporizador);
		cargarTamanioYfuente(botonPausa);
		botonPausa.setLabel("Pausa");
		botonera.add(botonPausa);
		botonPausa.addActionListener(controlador.getListenerBotonPausa());
		
		BotonSalir botonSalir = new BotonSalir();
		cargarTamanioYfuente(botonSalir);
		botonSalir.setLabel("Salir");
		botonera.add(botonSalir);
		botonSalir.addActionListener(controlador.getListenerBotonSalir());
	}
	
	public Habilidad getHabilidad() {
		return habilidad;
	}

	public void setHabilidad(Habilidad habilidad) {
		this.habilidad = habilidad;
	}
	
	public void update (Graphics g){
		repaint(500);
	}
	
	public Reloj getReloj (){
		return this.boardTemporizador.getCronometro();
	}
		
	public void update(Observable o, Object arg) {
		// TODO Auto-generated method stub
	}

	public void mouseDragged(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	public void mouseMoved(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	public ControlDeJuego getControlador() {
		return controlador;
	}

}
