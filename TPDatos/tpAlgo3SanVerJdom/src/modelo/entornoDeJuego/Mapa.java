package modelo.entornoDeJuego;

import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import org.jdom.Element;
import modelo.constantes.Constantes;
import modelo.pooglins.HabilidadesDisponibles;
import modelo.control.CantidadDeOficios;
import modelo.control.EstadoDeNivelDescargable;
import modelo.entornoDeJuego.BuilderMaterial;
import modelo.entornoDeJuego.Controlable;
import modelo.entornoDeJuego.ControladorEstadoPooglin;
import modelo.entornoDeJuego.EquipoPooglins;
import modelo.entornoDeJuego.EstadoParcela;
import modelo.entornoDeJuego.EstadoPooglin;
import modelo.entornoDeJuego.MaterialDeTerreno;
import modelo.entornoDeJuego.Observadores;
import modelo.entornoDeJuego.Terreno;
import modelo.entornoDeJuego.VisorEstados;
import modelo.persistencia.SerializableJDOM;
import modelo.pooglins.Observador;
import modelo.pooglins.Pooglins;
import modelo.pooglins.Posicion;
/**
 * Clase: Mapa.
 * Utilidad: Clase principal del juego, la cual contiene todos los elementos necesarios
 * 			 para representar el juego, implementa las Interfaces Observador, Controlable
 *           y VisorEstados.
 * Colabora Con: EquipoPooglins, Terreno.
 * */
public class Mapa implements Observador, Controlable, VisorEstados, ControladorEstadoPooglin, SerializableJDOM{
	


	private EquipoPooglins pooglins;
	private Terreno terreno;
	private LinkedList<EstadoParcela> estadoTerreno;
	private LinkedList<EstadoPooglin> estadoPooglins;
	private Observadores observadores;
	private Posicion puertaEntrada;
	private HabilidadesDisponibles habilidadesDiponibles;
	private int porcentajeParaGanar;
	private int tiempoInicial;
	
	

	
	public Mapa(EstadoDeNivelDescargable atributos){
		/*
		 *ACA tenemos que laventar las reglas del nivel. Para el TERRENO!!!!
		 *
		 */
		
		this.pooglins = equipoPooglins();
		
		this.estadoPooglins = new LinkedList<EstadoPooglin>();
		this.estadoTerreno = new LinkedList<EstadoParcela>();
		this.terreno = terreno(atributos);
		this.pooglins.suscribirObservador(this);
		this.terreno.suscribrirObservador(this);
		this.terreno.inicializarTerreno();
		this.actualizarEstadoInicialTerreno(atributos);
		this.observadores = new Observadores();
		Iterator<CantidadDeOficios> iterador = atributos.getCantidadDeOficiosPorNivel().iterator();
		this.habilidadesDiponibles = new HabilidadesDisponibles();
		HashMap<Integer, Integer> habilidades = new HashMap<Integer, Integer>();
		while (iterador.hasNext()) {
			CantidadDeOficios aux = iterador.next();
			habilidades.put(aux.getIdOficio(), aux.getCantidad());
		}
		this.habilidadesDiponibles.setOficios(habilidades);
		this.pooglins.setCantidadDePooglins(atributos.getCantidadDePooglins());
		this.setPorcentajeParaGanar(atributos.getPorcentajeGanadores());
		this.setTiempoInicial(atributos.getTiempo());
	}
	
	public int getTiempoInicial() {
		return tiempoInicial;
	}

	public void setTiempoInicial(int tiempoInicial) {
		this.tiempoInicial = tiempoInicial;
	}

	
	public void suscribirObservador(Observador obs){
		this.pooglins.suscribirObservador(obs);
		this.terreno.suscribrirObservador(obs);
		//this.observadores.suscribirObservador(obs);
	}
	
	public EstadoPooglin getEstadoPooglinXId(int id){
		Pooglins p = this.pooglins.obtenerPooglin(id);
		return new EstadoPooglin(p.getId(),p.getPosicion(),p.getOficioID(),p.getHabilidadID(), p.getDireccion());
	}
	
	private int getPorcentajeParaGanar() {
		return porcentajeParaGanar;
	}

	private void setPorcentajeParaGanar(int porcentajeParaGanar) {
		this.porcentajeParaGanar = porcentajeParaGanar;
	}
	
	public EstadoParcela getEstadoParcelaXPosicion(Posicion pos){
		return new EstadoParcela( pos, this.terreno.getMaterialActual(pos));
	}
	
	private void actualizarEstadoInicialTerreno(EstadoDeNivelDescargable atributos) {
		// TODO Auto-generated method stub
		for (int j = 0; j < atributos.getAltoTerreno(); j++) {
			for (int i = 0; i < atributos.getAnchoTerreno(); i++) {
				Posicion posi = new Posicion(i,j);
				MaterialDeTerreno mate = this.terreno.getMaterialActual(posi);
				this.agregarEstadoParcela(new EstadoParcela(posi,mate));
				if (mate.esPuertaDeEntrada()){
					this.puertaEntrada = posi;
				}
			}
		}
	}
	
	public void actualizarEstadoTerreno(EstadoParcela a) {
		// TODO Auto-generated method stub
		Iterator<EstadoParcela> iter = this.estadoTerreno.iterator();
		boolean encontrado = false;
		while (iter.hasNext() && !encontrado){
			EstadoParcela parcela = iter.next();
			if (parcela.getPosX() == a.getPosX() && parcela.getPosY() == a.getPosY()){
				encontrado = true;
				parcela.setMaterial(a.getMaterial());
				Posicion pos = new Posicion(a.getPosX(),a.getPosY());
				this.terreno.agregarElementoTerreno(pos, a.getMaterial());
			}
			
			
		}
	}

	private Terreno terreno(EstadoDeNivelDescargable atributos) {
		Terreno terreno= new Terreno(atributos.getAnchoTerreno(),atributos.getAltoTerreno());
		
		//La Matriz int[][] definida para las pruebas en ControlDeJuego, asi definida tiene
		//como dimensiones int[ALTO][ANCHO] que es lo contrario a nuestra logica (x,y), la cargo invertida
		for (int j = 0; j < atributos.getAltoTerreno(); j++) {
			for (int i = 0; i < atributos.getAnchoTerreno(); i++) {
				
				terreno.agregarElementoTerreno(new Posicion(i,j), crearMaterial(atributos.getTerreno()[j][i]));
			}
		}
		
		return terreno;
	}

	private EquipoPooglins equipoPooglins() {
		return new EquipoPooglins();
	}

	private Pooglins obtenerPooglinPorId(int id){
		return this.pooglins.obtenerPooglin(id);
	}
	
	private void agregarEstadoParcela(EstadoParcela estado){
		this.estadoTerreno.add(estado);
	}
	
	/**
	 * Implementacion Controlable
	 * */
	public void setearOficioAPooglin(int id, int idOficio){
		this.pooglins.setOficio(id, idOficio);
	}
	
	public void correrRondaMovimientosPooglin( ){
		//this.estadoPooglins.clear();
		//this.estadoTerreno.clear();
		this.pooglins.correrRondaMovimientosPooglin();
	}
	public boolean hayPooglins(){
		return this.pooglins.hayPooglins();
	}
	public void agregarPooglin(Posicion posInicial) {
		
		this.pooglins.agregarPooglin(posInicial, terreno);
		
		
	}
	/**
	 * Implementacion VisorEstados
	 * */	
	public List<EstadoParcela> getEstadoTerreno(){
		return this.estadoTerreno;
	}
	
	public List<EstadoPooglin> getEstadoPooglins(){
		return this.estadoPooglins;
	}
	
	/**
	 * Implementacion Observador
	 * */
	public void actualizar(Posicion posicion) {
		// TODO Auto-generated method stub
		this.modificarEstadoParcela(posicion);
		this.observadores.actualizar(posicion);
	}

	private void modificarEstadoParcela(Posicion pos) {
		// 
		Iterator<EstadoParcela> iter = this.estadoTerreno.iterator();
		boolean encontrado = false;
		while (iter.hasNext() && !encontrado){
			EstadoParcela parcela = iter.next();
			if (parcela.getPosX() == pos.getX() && parcela.getPosY() == pos.getY()){
				encontrado = true;
				parcela.setMaterial(this.terreno.getMaterialActual(pos));
			}
			
		}
		
	}

	public void eventoMuertePooglin(int id) {
		// TODO Auto-generated method stub
		//this.pooglins.eliminarPooglin(id);
		this.estadoPooglins.remove(this.getEstadoPooglinXId(id));
		this.observadores.eventoMuertePooglin(id);
	}
	
	public void eventoPooglinGanador(int id) {
		// TODO Auto-generated method stub
		//this.pooglins.eliminarPooglin(id);
		this.estadoPooglins.remove(this.getEstadoPooglinXId(id));
		this.pooglins.aumentarGanadores();
		//this.observadores.eventoPooglinGanador(id);
	}
	
	public void actualizar(EstadoPooglin estado) {
		// TODO Auto-generated method stub
		if (this.estadoPooglins.remove(estado))
		{this.estadoPooglins.add(estado);}
		//this.observadores.actualizar(estado);}
		
	}
	
	private MaterialDeTerreno crearMaterial(int idMaterial){
		switch (idMaterial) {
		case Constantes.PISO_PIEDRA: return BuilderMaterial.crearPiedra();
		case Constantes.PARED_PIEDRA: return BuilderMaterial.crearParedPiedra();
		case Constantes.PISO: return BuilderMaterial.crearPiso();
		case Constantes.RAMPA_DERECHA: return BuilderMaterial.crearRampaDerecha();
		case Constantes.RAMPA_IZQUIERDA: return BuilderMaterial.crearRampaIzquierda();
		case Constantes.HIELO: return BuilderMaterial.crearHielo();
		case Constantes.PARED: return BuilderMaterial.crearPared();
		case Constantes.FUEGO: return BuilderMaterial.crearFuego();
		case Constantes.AGUJERO_NEGRO: return BuilderMaterial.crearAgujeroNegro();
		case Constantes.PUERTA_ENTRADA: return BuilderMaterial.puertaEntrada();
		case Constantes.PUERTA_SALIDA: return BuilderMaterial.puertaSalida();			
		default: return BuilderMaterial.crearVacio();
			
		}
		
	}

	public String toString() {
		return terreno.toString();
	}

	//Este metodo esta solo para los Test Unitarios
	public Terreno getTerreno() {
		return terreno;
	}

	public int getCantidadGanadores() {
		// TODO Auto-generated method stub
		return this.pooglins.getGanadores();
	}
	
	public int getCantidadPooglins() {
		return this.pooglins.getCantidadPooglins();
	}
	public void setearHabilidadAPooglin(int id, int habilidad) {
		// TODO Auto-generated method stub
		this.pooglins.setHabilidad(id, habilidad);
	}

	public Element serializarJDOM() {
		Element raiz = new Element("Mapa");
		Iterator i = this.estadoPooglins.iterator();
		while (i.hasNext()){
			raiz.addContent(((EstadoPooglin)i.next()).serializarJDOM());
		}
		Iterator f = this.estadoTerreno.iterator();
		while (f.hasNext()){
			raiz.addContent(((EstadoParcela)f.next()).serializarJDOM());
		}
		return raiz;
	}
	
	public void hidratarJDOM(Element desde) {
		
		this.estadoPooglins.clear();
		//List<Element> estadoPooglins =desde.getChildren();
		Iterator i = desde.getChildren().iterator();
		//this.estadoTerreno = new LinkedList<EstadoParcela>();
		while (i.hasNext()){
			Element a = (Element)i.next();
			if (a.getName()== "EstadoPooglin"){
				EstadoPooglin b = new EstadoPooglin();
				b.hidratarJDOM(a);
				this.estadoPooglins.add(b);
			}
			if (a.getName()== "EstadoParcela"){
					EstadoParcela c = new EstadoParcela(null,null);
					c.hidratarJDOM(a);
					actualizarEstadoTerreno(c);
					//this.estadoTerreno.add(c);
			}
				
		}		
	}

	public int getAnchoTerreno() {
		// TODO Auto-generated method stub
		return this.terreno.getAnchoMapa();
	}

	public int getAltoTerreno() {
		// TODO Auto-generated method stub
		return this.terreno.getAlturaMapa();
	}

	public Posicion getPuertaEntrada() {
		// TODO Auto-generated method stub
		return puertaEntrada;
	}

	public HabilidadesDisponibles obtenerHabilidades() {
		return this.habilidadesDiponibles;
	}

	public void agregarPooglin() {
		// TODO Auto-generated method stub
		this.agregarPooglin(this.getPuertaEntrada().copiar());
	}


	public void actualizarAgregarPooglin(EstadoPooglin estado) {
		// TODO Auto-generated method stub
		this.estadoPooglins.add(estado);
		this.observadores.actualizarAgregarPooglin(estado);
	}

	public int getMaximaCantidadDePooglins() {
		return this.pooglins.getCantidadDePooglins();
	}
	
	public boolean gane() {
		int porcentajeDeGanadores = this.getCantidadGanadores()*100/this.getMaximaCantidadDePooglins();
		return porcentajeDeGanadores>=this.getPorcentajeParaGanar();
	}

	public void agregarPooglinPorEstado( EstadoPooglin estado){
		this.pooglins.agregarPooglinDesdeEstado(estado, this.terreno);
	}
	
}
