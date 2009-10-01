package modelo.entornoDeJuego;

import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;

import controlador.ConstantesControlador;

import vista.utilitarias.ConstantesVista;
import modelo.constantes.Constantes;
import modelo.movimientos.Direccion;
import modelo.pooglins.Observador;
import modelo.pooglins.Posicion;
/**
 * Clase: Terreno (implementa la Interfaz ServiciosTerreno).
 * Utilidad: Clase utilizada para representar el Mapa del juego, permite agregar
 * 			 elementos de Terreno en este, por medio de una Posicion.
 * 			 Tambien permite crear Puentes, Pooglins Congelados y romper el Terreno. *  
 * Utilizada por: Mapa.
 * Colabora con: Observadores, HashMap.
 * */
public class Terreno implements ServiciosTerreno{
	
	private HashMap<Posicion, MaterialDeTerreno> mapa;
	private Observadores observadores;
	private int alturaMapa;
	private int anchoMapa;
	private LinkedList<Posicion> agujerosNegros;
	
	private HashMap<Posicion, MaterialDeTerreno> mapa(){
		return new HashMap<Posicion, MaterialDeTerreno>();
	}
	


	public Terreno(int ancho, int altura){ 
		mapa= mapa();
		this.anchoMapa = ancho;
		this.alturaMapa= altura;
		this.observadores = new Observadores();
		this.agujerosNegros = new LinkedList<Posicion>();
	}
		
	public int getAlturaMapa() {
		return alturaMapa;
	}

	public int getAnchoMapa() {
		return anchoMapa;
	}
	
	public void agregarElementoTerreno(Posicion llave, MaterialDeTerreno material){
		mapa.put(llave , material);
		if (material.getTipoDeMaterial() == Constantes.AGUJERO_NEGRO){
			this.agujerosNegros.add(llave);
		}
		this.observadores.actualizar(llave);
	}
	public void inicializarTerreno(){
		Iterator<Posicion> iterator = this.agujerosNegros.iterator();
		while (iterator.hasNext()) {
			this.setEntornoMortal(iterator.next());		
		}
	}
	public MaterialDeTerreno getElementoTerreno(Posicion posicion){
		return mapa.get(posicion);
	}
	
	public int getCantidadDeElementos(){
		return mapa.size();
	}
	
	public MaterialDeTerreno getSiguienteMaterial(Direccion direccion, Posicion posicion){
		Posicion siguientePosicion = new Posicion(posicion.getX() + direccion.getDireccionX(), posicion.getY() + direccion.getDireccionY());
		return (getElementoTerreno(siguientePosicion));
	}
	
	public MaterialDeTerreno getMaterialAnterior(Direccion direccion, Posicion posicion){
		Posicion siguientePosicion = new Posicion(posicion.getX() - direccion.getDireccionX(), posicion.getY() - direccion.getDireccionY());
		return (getElementoTerreno(siguientePosicion));
	}
	
	public MaterialDeTerreno getSiguienteMaterialTeleportador(Direccion direccion, Posicion posicion){
		Posicion siguientePosicion = new Posicion(0,0);
		siguientePosicion.setX(posicion.getX() + (direccion.getDireccionX()*Constantes.CANTIDAD_POSICION_TELETRANSPORTACION));
		siguientePosicion.setY(posicion.getY() + direccion.getDireccionY());
		
		MaterialDeTerreno materialSiguiente = getElementoTerreno(siguientePosicion);
		if (materialSiguiente == null){
			return BuilderMaterial.crearParedPiedra();
		}else{
			return materialSiguiente;
		}
		
	}
	
	public void crearPiso(Posicion miPosicion){
		agregarElementoTerreno(miPosicion,  BuilderMaterial.crearPiso());
	}
	
	public MaterialDeTerreno getMaterialActual( Posicion posicion){
		return (getElementoTerreno(posicion));
	}
	
	public void crearPuente(Posicion miPosicion, Direccion direccion){
		if(direccion.esDireccionDerecha()){
			agregarElementoTerreno(miPosicion,  BuilderMaterial.crearTunelElectromagneticoDerecha());
		}else agregarElementoTerreno(miPosicion,  BuilderMaterial.crearTunelElectromagneticoIzquierda());
	}

	public void romperTerreno(Posicion pos, Direccion dirMovimiento) {
		  for (int j = 0; j < ConstantesControlador.ALTURA_POOLGIN; j++){
			   Posicion aModificar =  new Posicion(pos.getX()+dirMovimiento.getDireccionX() , pos.getY() - j );
			   if (this.getMaterialActual(aModificar).esRompible()&& !this.getMaterialActual(aModificar).esPiso()) agregarElementoTerreno(aModificar,  BuilderMaterial.crearVacio());
			   if (j == 0) this.crearPiso(aModificar);
		  }

	}

	public void cavarTerreno(Posicion pos, Direccion dirMovimiento) {
		//agregarElementoTerreno(pos,  BuilderMaterial.crearVacio());
			  for (int j = 0; j < ConstantesVista.ANCHO_POOGLIN; j++){
			   Posicion aModificar =  new Posicion(pos.getX() + j*dirMovimiento.getDireccionX(), pos.getY());
			   Posicion aModificarAnterior =  new Posicion(pos.getX() + j*dirMovimiento.getDireccionX(), pos.getY()-1);
			   if (this.getMaterialActual(aModificarAnterior).esRompible())agregarElementoTerreno(aModificarAnterior ,  BuilderMaterial.crearVacio());
     		   if (this.getMaterialActual(aModificar).esRompible()) crearPiso(aModificar);
				}
	}

	public void crearPooglinCongelado(Posicion miPosicion) {
		agregarElementoTerreno(miPosicion, BuilderMaterial.crearPooglinCongelado());
		
	}
	
	public void crearRampaDerecha(Posicion miPosicion){
		agregarElementoTerreno(miPosicion,  BuilderMaterial.crearRampaDerecha());
	}

	
	public void crearRampaIzquierda(Posicion miPosicion){
		agregarElementoTerreno(miPosicion,  BuilderMaterial.crearRampaIzquierda());
	}


	public void suscribrirObservador( Observador observador){
		this.observadores.suscribirObservador(observador);
	}

	@Override
	public String toString() {
		String s = new String();
		for (int j = 0; j < this.alturaMapa; j++) {
			for (int i = 0; i < this.anchoMapa; i++) {
				MaterialDeTerreno mat = this.getMaterialActual(new Posicion(i ,j));
				/*boolean bool = this.mapa.containsKey(new Posicion(4,5));*/
				int tipoMaterial = mat.getTipoDeMaterial();
				s = s + " " + ((Integer)tipoMaterial).toString();
			}
			s+="\n";
		}
		return s;
		
		
	}

	public void generarTunel(Posicion miPosicion) {
		// TODO Auto-generated method stub
		
	}

	public void generarVacio(Posicion miPosicion) {
		// TODO Auto-generated method stub
		
	}
	
	private void setEntornoMortal(Posicion posicion){
		LinkedList<MaterialDeTerreno> entorno = this.obtenerEntorno(posicion);
		Iterator<MaterialDeTerreno> iterador = entorno.iterator();
		while (iterador.hasNext()){
			iterador.next().setMortal();
		}
	}

	private LinkedList<MaterialDeTerreno> obtenerEntorno(Posicion posicion) {
		// TODO Auto-generated method stub
		LinkedList<MaterialDeTerreno> entorno = new LinkedList<MaterialDeTerreno>();
		MaterialDeTerreno material = this.getMaterialActual(posicion);
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				Posicion pos = new Posicion(posicion.getX()+ i,posicion.getY() + j);
				
			 material = this.getMaterialActual(pos);
			 if (!(material == null)){
					entorno.add(material);
				}
			}
		}
		
		
		return entorno;
	}



	public void crearVacio(Posicion modificar) {
		// TODO Auto-generated method stub
		agregarElementoTerreno(modificar,  BuilderMaterial.crearVacio());		
	}
	
}


