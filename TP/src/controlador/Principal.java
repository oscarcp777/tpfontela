package controlador;
import modelo.mapaDeJuego.Mapa;
import modelo.mapaDeJuego.Planeta;
import modelo.utilitarios.Constants;
import modelo.xml.XMLcarga;


public class Principal {
  
	public static void main(String[] args){		
		
		XMLcarga xmlcarga = new XMLcarga(Constants.MapasDeJuego.NIVEL_1);
		Planeta planeta = new Planeta(xmlcarga.getInfoNivel()); 		
		Mapa mapaDeJuego = planeta.obtenerMapaDeJuego();
		ControlDeJuego controladorDeJuego = new ControlDeJuego(mapaDeJuego);
	}
		
	
	/*
	 *
	 * public static void main(String[] args) throws 
		IOException, ParserConfigurationException, ClassNotFoundException{		
		Partida otraPartida;		
		otraPartida = PersistidorDePartidas.cargarPartida("Partida.xml");
			// Recupero el planeta //
		Planeta otroPlaneta = otraPartida.getPlaneta();	
		//Planeta otroPlaneta = new Planeta("archivo.txt");
		Dios miDios = new Dios();
		
		Terreno miTerreno = otroPlaneta.getTerreno();		
		miDios.jugar(otroPlaneta);
		otroPlaneta.agregarPooglin();
		Frame f = new Ventana(otroPlaneta.getTerreno(),otroPlaneta.getPooglins());
		Controlador controlador = new Controlador((Ventana)f,otroPlaneta.getTerreno(),otroPlaneta.getPooglins(),miDios);
		f.show();
		miDios.start();	    
		/*Partida miPartida = new Partida (otroPlaneta.getTerreno().getPlaneta(),otroPlaneta.getTerreno());
		// Aca guardo el estado de la partida //
		PersistidorDePartidas.guardarPartida("Partida.xml", miPartida);
	}*
	 * 
	 * 
	 *
	 * private Ventana vista;
	private Dios dios;
	private Terreno terreno;
	private List <Pooglin> pooglins;
	private Habilidad habilidad;
	
	public Controlador(Ventana vista, Terreno terreno,
			List <Pooglin> pooglins)
	{   		
		this.vista = vista;
		this.terreno = terreno;
		this.pooglins=pooglins;
		this.dios=dios;
	}
	
	public Controlador(Ventana vista, Terreno terreno,
			List <Pooglin> pooglins,Dios dios)
	{   		
		this.vista = vista;
		this.terreno = terreno;
		this.pooglins=pooglins;
		this.dios=dios;
	}
	
	private class EscuchaBotonTaladro implements ActionListener
	{	public void actionPerformed(ActionEvent e)
		{	
			habilidad = new TaladroUltraSonico();    
			vista.setHabilidad(habilidad);			

	       	
		}
	}
	
	public ActionListener getListenerBotonTaladro() {
		return new EscuchaBotonTaladro();
	}
	
	private class EscuchaBotonRayoLaser implements ActionListener
	{	public void actionPerformed(ActionEvent e)
		{
			habilidad = new RayoLaser();   
			vista.setHabilidad(habilidad);			

		}
	}

	public ActionListener getListenerBotonRayoLaser() {
		return new EscuchaBotonRayoLaser();

	}
	
	private class EscuchaBotonCongelamiento implements ActionListener
	{	public void actionPerformed(ActionEvent e)
		{
			habilidad = new Congelamiento();   
			vista.setHabilidad(habilidad);			

		}
	}

	public ActionListener getListenerBotonCongelamiento() {
		return new EscuchaBotonCongelamiento();

	}
	
	private class EscuchaBotonPlatilloVolador implements ActionListener
	{	public void actionPerformed(ActionEvent e)
		{
			habilidad = new PlatilloVolador();    	
			vista.setHabilidad(habilidad);			

		}
	}

	public ActionListener getListenerBotonPlatilloVolador() {
		return new EscuchaBotonPlatilloVolador();

	}
	
	private class EscuchaBotonTunelElectroMagnetico implements ActionListener
	{	public void actionPerformed(ActionEvent e)
		{
			habilidad = new TunelElectromagnetico();  
			vista.setHabilidad(habilidad);			
		}
	}

	public ActionListener getListenerBotonTunelElectroMagnetico() {
		return new EscuchaBotonTunelElectroMagnetico();

	}
	
	private class EscuchaBotonSalir implements ActionListener
	{	public void actionPerformed(ActionEvent e)
		{
			System.exit(0);
		}
	}

	public ActionListener getListenerBotonSalir() {
		return new EscuchaBotonSalir();

	}
	
	private class EscuchaBotonGuardar implements ActionListener
	{	public void actionPerformed(ActionEvent e)
		{
		Partida miPartida = new Partida (terreno.getPlaneta(),terreno);

			try {
				// Aca guardo el estado de la partida //
				PersistidorDePartidas.guardarPartida("Partida.xml", miPartida);
				
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			} catch (ParserConfigurationException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}		
		}
	}

	public ActionListener getListenerBotonGuardar() {
		return new EscuchaBotonGuardar();

	}
	
	private class EscuchaBotonReiniciar implements ActionListener
	{	public void actionPerformed(ActionEvent e)
		{
			//Falta Implementar
		}
	}

	public ActionListener getListenerBotonReiniciar() {
		return new EscuchaBotonReiniciar();

	}
	
	private class EscuchaBotonRecuperar implements ActionListener
	{	public void actionPerformed(ActionEvent e)
		{
		// Aca recupero el estado de la partida guardada //
		Partida otraPartida;
		try {
			otraPartida = PersistidorDePartidas.cargarPartida("Partida.xml");
			// Recupero el planeta //
			Planeta otroPlaneta = otraPartida.getPlaneta();
			vista.setVisible(false);
			vista = new Ventana(otroPlaneta.getTerreno(),otroPlaneta.getPooglins());			
			vista.show();
			dios.stop();
			Dios miDios = new Dios();			
			Terreno miTerreno = otroPlaneta.getTerreno();
			miDios.jugar(otroPlaneta);
			miDios.run();
			

		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (ClassNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		}
	}

	public ActionListener getListenerBotonRecuperar() {
		return new EscuchaBotonRecuperar();

	}
	
	
	 
	
	
	
	/*
	 * 
	
	public static void main(String[] args) {
		
		XMLnivel xmlNivel = new XMLnivel(Constants.NivelesDeJuego.NIVEL_1);
		InfoNivel infoNivel = new InfoNivel(xmlNivel.datosNaveIngreso(),xmlNivel.datosNaveEscape(),xmlNivel.listaStringTerrenos(),xmlNivel.listaStringHabilidades());
		Planeta planeta = new Planeta(infoNivel); 		
		
		BoardLoadLevel boardLoadLevel = new BoardLoadLevel(infoNivel,planeta);
		boardLoadLevel.repaintPanel();
		boardLoadLevel.setVisible(true);
		
		/*
		Juego juego = new Juego();
		
		
		XMLnivel xmlNivel = new XMLnivel(Constants.NivelesDeJuego.NIVEL_1);
		InfoNivel infoNivel = new InfoNivel(xmlNivel.datosNaveIngreso(),xmlNivel.datosNaveEscape(),xmlNivel.listaStringTerrenos(),xmlNivel.listaStringHabilidades());
		Planeta planeta = new Planeta(infoNivel); 		
		
		Panel panel= new Panel();
		panel.setSize(300,300);
		BoardPrincipal board = new BoardPrincipal(panel,planeta);
		BotonCargar botonCargar = new BotonCargar(juego, infoNivel, planeta, board);
        botonCargar.addActionListener( new AccionBoton(botonCargar));
        BotonHF botonHF = new BotonHF(board);
        botonHF.addActionListener ( new AccionBoton(botonHF));
        BotonTerminar botonTerminar = new BotonTerminar(juego,board);
        botonTerminar.addActionListener(new AccionBoton(botonTerminar));
        BotonComenzar botonComenzar = new BotonComenzar(juego,board);
        botonComenzar.addActionListener(new AccionBoton(botonComenzar));
       
        //board.setVisible(true);
        panel.add(botonComenzar);
        
        panel.add(botonCargar);
        
        
        panel.add(botonTerminar);
        panel.add(botonHF);
       
        board.setLayout(new BorderLayout());
        panel.setLayout(new FlowLayout());
        
        board.add("North", panel);
      
        
        board.setVisible(true);

        
        
	    //Fin agregado
        /*Mientras hayan vidas: Mientras hayan vidas y no haya pausa: todo*/
/*
        board.requestFocus();
        
        while (board.isDisplayable()){
        	juego.setPausado(false);
        	if (juego.getValido()==true){
				juego.jugar(planeta,board);
        	}
        }
	*	
	}*/
}
