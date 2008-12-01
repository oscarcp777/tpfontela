package modelo.movimientoPooglins;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import modelo.propiedadesDeElementos.Posicion;


public class Movimiento {
	private Posicion posicion; //posicion donde esta parado el pooglin
	private Direccion direccion;
	private PasosEnDireccion pasosEnDireccion;
			
	//constructor por defecto
	public Movimiento(){
		
	}
	
	public Movimiento(Posicion posicionInicial){
		posicion = posicionInicial; //le asigna la posicion inicial
		pasosEnDireccion = new PasosEnDireccion();
		direccion = Abajo.getInstance(); //la direccion inicial es abajo
	}
	
	//se delega el movimiento a la direccion, la cual sabe en que direccion moverse
	public Posicion siguientePosicion(){
		if(noCambiaSuPosicion())
			return posicion;
		else{
			if(pasosEnDireccion.contar()) //si se puede contar los pasos en direccion
			pasosEnDireccion.darPasosEnDireccion(1);
			return (posicion=direccion.siguientePosicionEnDireccion(posicion));
		}
		
		
	}
	
	public void inicializarPasosEnDireccion(){
		pasosEnDireccion.inicializarCantidadDePasos();
	}
	
	public Posicion verSiguientePosicion(Posicion posicionActual){
		return direccion.siguientePosicionEnDireccion(posicionActual);
	}
	
	public int cantidadDePasosEnDireccion(){
		return pasosEnDireccion.cantidadDePasosEnDireccion();
	}
	
	public boolean noCambiaSuPosicion(){
		return pasosEnDireccion.getQuietoEnDireccion();
	}
	
	public void movimientoInvalido(boolean movimientoInvalido){
		pasosEnDireccion.setQuietoEnDireccion(movimientoInvalido);
	}
	
	public void cambiarDireccion(){
		if(!direccion.equals(direccion.cambiarDireccion())){
		pasosEnDireccion.inicializarCantidadDePasos();	
		direccion=direccion.cambiarDireccion();
		}
	}
		
	public void cambiarDireccion(Direccion direccion){
		this.direccion = direccion; 
	}
	
	public Posicion darPasosEnDireccion(PasosEnDireccion pasosEnDireccion){
		int cantidadPasos = 0;
		Posicion posicionAux = new Posicion(posicion);
		while(cantidadPasos<pasosEnDireccion.cantidadDePasosEnDireccion()){
			posicionAux = verSiguientePosicion(posicionAux); //actualizo la posicion
			cantidadPasos++;
		}
		return posicionAux;
	}
	
	public void contarPasos(boolean contar){
		pasosEnDireccion.contarPasosEnDireccion(contar);
	}
	
	public boolean isConDireccion(){
		return (direccion!=null);
	}
	
	public boolean isConDireccionAbajo(){
		return direccion==Abajo.getInstance();
	}
	
	public Element toXml(Document doc){
		Element xmlElemento = doc.createElement("Movimiento");
		xmlElemento.setAttribute("direccion", ""+direccion.getClass().getSimpleName()); //uso reflection para saber el nombre de la instancia del singleton
																						//despues mediante una fabrica obtengo la direccion del movimiento mediante este nombre	
		
		xmlElemento.appendChild(pasosEnDireccion.toXml(doc));
						
		return xmlElemento;
	}
	
	//Para cargar la partida guardada
	public void setDireccion(Direccion direccion) {
		this.direccion = direccion;
	}

	//Para cargar la partida guardada
	public void setPasosEnDireccion(PasosEnDireccion pasosEnDireccion) {
		this.pasosEnDireccion = pasosEnDireccion;
	}

	//Para cargar la partida guardada
	public void setPosicion(Posicion posicion) {
		this.posicion = posicion;
	}
	
	public boolean veniaEnEsaDireccion(Posicion posPoogling, Posicion posTerreno){
		return direccion.veniaEnEsaDireccion(posPoogling,posTerreno);
	}
	
}
