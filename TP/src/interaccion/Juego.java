package interaccion;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import modelo.elementosDelMapa.Poogling;
import modelo.mapaDeJuego.Mapa;
import modelo.nivelDeJuego.ColPooglins;
import modelo.nivelDeJuego.Reloj;
import modelo.utilitarios.Constants;
import vista.BoardFinJuego;
import controlador.ControlDeJuego;

public class Juego extends Thread{
	
	private Mapa mapa;
	private int indexListPooglins;
	private ColPooglins pooglingsAmover;
	private ColPooglins pooglingsEnPlaneta;
	private Poogling poogling=null;
	private int cantpooglinsMuertos,cantpooglinsAux;
	private ControlDeJuego controladorDeJuego;
	private int nivel;
	private List<String> nombresArchNiveles;
	private Reloj reloj;
	private boolean next;
	
	public ColPooglins getPooglingsEnPlaneta() {
		return pooglingsEnPlaneta;
	}

	public Juego(){
		indexListPooglins=cantpooglinsMuertos=cantpooglinsAux=0; //inicializo las variables en 0
		pooglingsAmover = new ColPooglins();
		next = true;
		nombresArchNiveles = new ArrayList<String>();
		nombresArchNiveles.add(Constants.MapasDeJuego.NIVEL_1);
		nombresArchNiveles.add(Constants.MapasDeJuego.NIVEL_2); //arranco del nivel 1
	}														    //como solo tengo 2 niveles agrego uno solo
	
	public ControlDeJuego getControladorDeJuego() {
		return controladorDeJuego;
	}

	public void setControladorDeJuego(ControlDeJuego controladorDeJuego) {
		this.controladorDeJuego = controladorDeJuego;
	}
	
	public void setNivel(int nivel){
		this.nivel = nivel;
	}
	
	public int getNivel(){
		return nivel;
	}
	
	public String getNivelDeJuego(){
		return nombresArchNiveles.get(nivel);
	}
	
	public void setReloj(Reloj reloj){
		this.reloj = reloj;
	}
	
	public void inicializarJuego(Mapa mapa){
		this.mapa = mapa;
		setNivel(mapa.getNivel()-1);//el nivel 1 es el indice 0 para obtener la ruta de los niveles
		pooglingsEnPlaneta = new ColPooglins(mapa.obtenerPooglinsNaveIngreso().obtenerTodos()); //obtengo todos los pooglins de la nave de ingreso
		//	pooglins = mapa.obtenerPooglinsNaveIngreso();
	}
	
	//este metodo hace que se obtenga de a un poogling, para lograr de que x pooglins se muevan en fila india.
	private void agregarAcolPooglingsAmover(){
			
	 	poogling = pooglingsEnPlaneta.obtenerPoogling(indexListPooglins);
	 	
		pooglingsAmover.agregarPoogling(poogling);
		
		indexListPooglins++;
	}
	

	public boolean moverPooglins(){
			
			if((poogling==null || poogling.cantidadDePasosEnDireccion()==2)&&(pooglingsAmover.tamanio()+cantpooglinsAux)!=pooglingsEnPlaneta.tamanio()/*y si no se movieron todos los pooglins*/) //distancia minima entre cada poogling (2 pasos)
			agregarAcolPooglingsAmover(); //cuando cumpla la distancia minima que debe haber entre cada pooglin, lo agrego a la coleccion de pooglinsAmover pues este se movera con el resto.	
		
			
			for(Iterator<Poogling> it = pooglingsAmover.iterator();it.hasNext();){
				Poogling pooglingAmover = it.next();
				if(!pooglingAmover.mover(mapa)){//{ //si el pooglin no se puede mover, porque llego a la nave de salida o porque no tiene vida, lo agrego a la coleccion de pooglins a borrar
				//pooglinsAborrar.add(pooglingAmover);
					if(!pooglingAmover.isConVida()){
						pooglingsEnPlaneta.borrarPoogling(pooglingAmover); //lo borro del planeta porque murio.
						cantpooglinsMuertos++;
					}
						 
				//}
				cantpooglinsAux++;
				}
			}
			
			
			if(pooglingsEnPlaneta.tamanio()==0){ //significa que se murieron todos los pooglins
				BoardFinJuego boardFinJuego = new BoardFinJuego();
				controladorDeJuego.getBoardGame().getReloj().detenerReloj();
				boardFinJuego.perdio();
				return false;
			}else if(pooglingsEnPlaneta.tamanio()==mapa.obtenerPooglinsNaveEscape().tamanio()){ //todos los pooglins que estaban vivos en el planeta subieron a la nave de salida
				BoardFinJuego boardFinJuego = new BoardFinJuego();
				controladorDeJuego.getBoardGame().getReloj().detenerReloj();
				nivel++;
				if(nivel==2){
				boardFinJuego.pasoTodosLosNiveles();
				controladorDeJuego.closeFrameJuego();
				stop();
				}else{
				boardFinJuego.gano();
				controladorDeJuego.cargarNivel(getNivelDeJuego());
				}
				
				return false; 
			}else return true; //continuan moviendose los pooglins
	}
		
	public void run(){
		
		try {
			while (moverPooglins()) //si la coleccion de pooglins de la nave ingreso no esta vacia
				sleep(400);          //es porque quedo alg�n poogling vivo para moverse en el mapa de juego
		} catch( InterruptedException e ) {
			System.err.println("Interrupcion");
		}

	}

	public Mapa getMapa() {
		return mapa;
	}
		
	
}
