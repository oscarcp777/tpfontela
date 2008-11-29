package controlador;

import interaccion.Juego;

import java.awt.event.ActionListener;

import modelo.habilidadesPooglins.Habilidad;
import modelo.mapaDeJuego.Mapa;
import modelo.mapaDeJuego.Planeta;
import modelo.xml.XMLcarga;
import vista.BoardGame;
import vista.BoardLoadGame;
import controlador.botonescontroldeljuego.BotonComenzar;
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



public class ControlDeJuego {

	private BoardGame boardGame;
	private BoardLoadGame boardLoadGame;
	private Juego juego;
	private Mapa mapa;
	private Habilidad habilidad;
	
	public Mapa getMapa() {
		return mapa;
	}

	public void setMapa(Mapa mapa) {
		this.mapa = mapa;
	}

	public BoardGame getBoardGame() {
		return boardGame;
	}

	public BoardLoadGame getBoardLoadGame() {
		return boardLoadGame;
	}

	public ControlDeJuego(Mapa mapa){
		//juego = new Juego();
		//juego.inicializarJuego(mapa);
		this.mapa = mapa;
		boardLoadGame = new BoardLoadGame(this);
		//juego.setControladorDeJuego(this);
		boardLoadGame.show();
		
	}
	
	public void closeFrameJuego(){
		boardGame.setVisible(false);
	}
	
	public Juego getJuego(){
		return juego;
	}
	
	public void nuevoJuego(){
		juego = new Juego();
		juego.setControladorDeJuego(this);
	}
	
	public void iniciarPartida(){
		boardGame = new BoardGame(juego.getMapa(),this);
		boardGame.cargarBotones();//carga la botonera del frame(los botones de las habilidades, y los del control de juego
		boardGame.setVisible(true);
	}
	
	public void lanzarJuego(){
		nuevoJuego();
		juego.inicializarJuego(mapa);
		juego.setControladorDeJuego(this);
		boardGame = new BoardGame(juego.getMapa(),this);
		boardGame.cargarBotones();//carga la botonera del frame(los botones de las habilidades, y los del control de juego
		boardGame.setVisible(true);
		juego.start();
	}
	
	public void cargarNivel(String nivel){
		boardGame.setVisible(false);
		XMLcarga xmlcarga = new XMLcarga(nivel);
		Planeta planeta = new Planeta(xmlcarga.getInfoNivel());
		mapa = planeta.obtenerMapaDeJuego();
		int nivelJuego = juego.getNivel();
		lanzarJuego();
		juego.setNivel(nivelJuego);
		juego.setReloj(boardGame.getReloj());
	}
	
	/*Actions Listener de botones de habilidades*/
	public ActionListener getListenerBotonTaladro(){
		return new BotonTaladro(boardGame);
	}
	
	public ActionListener getListenerBotonCongelamiento(){
		return new BotonCongelamiento(boardGame);
	}
	
	public ActionListener getListenerBotonRayoLaser(){
		return new BotonRayoLaser(boardGame);
	}
	
	public ActionListener getListenerBotonPlatilloVolador(){
		return new BotonPlatilloVolador(boardGame);
	}
	
	public ActionListener getListenerBotonTunel(){
		return new BotonTunel(boardGame);
	}
	
	public ActionListener getListenerBotonTeletransportacion(){
		return new BotonTeletransportacion(this.boardGame);
	}
	
	/*Actions Listener de botones controlador del juego*/
	
	public ActionListener getListenerBotonComenzar(){
		BotonComenzar botonComenzar = new BotonComenzar(this);
		
		return botonComenzar;
	}
	
	public ActionListener getListenerBotonSalir(){
		return new BotonSalir();
	}
	
	public ActionListener getListenerBotonGuardar(){
		return new BotonGuardar(juego);
	}
	
	public ActionListener getListenerBotonRecuperar(){
		return new BotonRecuperar(this);
	}
	
	public ActionListener getListenerBotonContinuar(){
		return new BotonContinuar(juego);
	}
	
	public ActionListener getListenerBotonPausa(){
		return new BotonPausa(juego);
	}
	
	/*
	 * 	public void cargarSiguienteNivel(){
		this.vista.setVisible(false);
		this.terreno = this.dios.getPlanetaActual().getTerreno();
		this.temporizador = new TemporizadorDeLanzadaDePooglins(3500,
				terreno.getPlaneta(),terreno.getPlaneta().getCantidadPooglinsPlaneta());
		this.vista = new Ventana(terreno,terreno.getPlaneta().getPooglins(),this);
		this.vista.setVisible(true);
		this.dios.run();
		this.dios.continuarDios();
	}
	
	public void LanzarAplicacion(){
		this.vista = new Ventana(terreno,terreno.getPlaneta().getPooglins(),this);
		this.vista.setVisible(false);
		this.temporizador = new TemporizadorDeLanzadaDePooglins(3500,
				terreno.getPlaneta(),terreno.getPlaneta().getCantidadPooglinsPlaneta());
	
	}
		
	private class EscuchaBotonTaladro implements ActionListener
	{	public void actionPerformed(ActionEvent e)
		{	
			habilidad = new TaladroUltraSonico();    
			((Ventana) vista).setHabilidad(habilidad);			

	       	
		}
	}
	
	public ActionListener getListenerBotonTaladro() {
		return new EscuchaBotonTaladro();
	}
	
	private class EscuchaBotonRayoLaser implements ActionListener
	{	public void actionPerformed(ActionEvent e)
		{
			habilidad = new RayoLaser();   
			((Ventana) vista).setHabilidad(habilidad);			

		}
	}

	public ActionListener getListenerBotonRayoLaser() {
		return new EscuchaBotonRayoLaser();

	}	
		
	private class EscuchaBotonPausar implements ActionListener
	{	@SuppressWarnings("deprecation")
	public void actionPerformed(ActionEvent e)
		{
			dios.suspend();
			temporizador.suspend();
			temporizador.pararTemporizador();
			((Ventana)vista).getReloj().detenerReloj();
		}

	}

	public ActionListener getListenerBotonPausar() {
		return new EscuchaBotonPausar();

	}	
	
	
	private class EscuchaBotonTeletransportacion implements ActionListener
	{	public void actionPerformed(ActionEvent e)
		{
			habilidad = new Teletransportacion();   
			((Ventana) vista).setHabilidad(habilidad);			

		}
	}

	public ActionListener getListenerBotonTeletransportacion() {
		return new EscuchaBotonTeletransportacion();

	}	
	
	private class EscuchaBotonIniciarJuego implements ActionListener
	{	public void actionPerformed(ActionEvent e)
		{
			LanzarAplicacion();
			vista.setVisible(true);
			ventanaPrincipal.setVisible(false);
			dios.start();
			dios.setReloj(((Ventana)vista).getReloj());
		}
	}

	public ActionListener getListenerBotonIniciarJuego() {
		return new EscuchaBotonIniciarJuego();

	}
	
	private class EscuchaBotonCongelamiento implements ActionListener
	{	public void actionPerformed(ActionEvent e)
		{
			habilidad = new Congelamiento();   
			((Ventana) vista).setHabilidad(habilidad);			

		}
	}

	public ActionListener getListenerBotonCongelamiento() {
		return new EscuchaBotonCongelamiento();

	}
	
	private class EscuchaBotonPlatilloVolador implements ActionListener
	{	public void actionPerformed(ActionEvent e)
		{
			habilidad = new PlatilloVolador();    	
			((Ventana) vista).setHabilidad(habilidad);			

		}
	}

	public ActionListener getListenerBotonPlatilloVolador() {
		return new EscuchaBotonPlatilloVolador();

	}
	
	private class EscuchaBotonTunelElectroMagnetico implements ActionListener
	{	public void actionPerformed(ActionEvent e)
		{
			habilidad = new TunelElectromagnetico();  
			((Ventana) vista).setHabilidad(habilidad);			
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
	{	@SuppressWarnings("deprecation")
	public void actionPerformed(ActionEvent e)
		{
		terreno.getPlaneta().quitarPooglinsMuertos();
		terreno.getPlaneta().quitarPooglinsSalvados();
		((Ventana)vista).getReloj().detenerReloj();
		dios.suspend();
		temporizador.suspend();
		
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
	
	private class EscuchaBotonRecuperar implements ActionListener
	{	public void actionPerformed(ActionEvent e)
		{
		// Aca recupero el estado de la partida guardada //
		try {
			Partida otraPartida;
			otraPartida = PersistidorDePartidas.cargarPartida("Partida.xml");
			// Recupero el planeta //
			Planeta otroPlaneta = otraPartida.getPlaneta();
			Controlador controlador = ((Ventana) vista).getControlador();
			vista.setVisible(false);
			dios = new Dios();
			dios.cargarPlanetaActual(otroPlaneta);			
			vista = new Ventana(otraPartida.getPlaneta().getTerreno(),otraPartida.getPlaneta().getPooglins(),controlador);
			vista.setVisible(true);
			dios.start();
			

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
	
	private class EscuchaBotonPlay implements ActionListener{
		@SuppressWarnings("deprecation")
		public void actionPerformed(ActionEvent e)
		{
			dios.resume();
			temporizador.resume();
			temporizador.continuarTemporizador();
			((Ventana)vista).getReloj().continuarReloj();
		}
	}
	
	public ActionListener getListenerBotonPlay() {
		return new EscuchaBotonPlay();

	}
	 */
	
	
}
