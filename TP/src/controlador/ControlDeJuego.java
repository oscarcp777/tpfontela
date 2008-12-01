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
		return new BotonContinuar(juego,boardGame.getBoardTemporizador());
	}
	
	public ActionListener getListenerBotonPausa(){
		return new BotonPausa(juego,boardGame.getBoardTemporizador());
	}
	
}
