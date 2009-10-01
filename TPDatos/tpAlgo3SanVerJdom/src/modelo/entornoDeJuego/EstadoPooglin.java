package modelo.entornoDeJuego;

import org.jdom.Element;


import modelo.movimientos.Direccion;
import modelo.persistencia.SerializableJDOM;
import modelo.pooglins.Pooglins;
import modelo.pooglins.Posicion;
/**
 * Clase: EstadoPooglin.
 * Utilidad: Clase de consulta, utilizada para obtener el estado de un Pooglin en un 
 *           determinado momento. Podremos obtener el id y las posiciones x,y de 
 *           un Pooglin en particular.
 * Colabora con: Posicion.
 * 
 * */
public class EstadoPooglin implements SerializableJDOM{

	private int id;
	private Posicion posicion;
	private int oficio;
	private int habilidad;
	private Direccion direccion;
	
	public EstadoPooglin(int id, Posicion pos, int oficio, int habilidad, Direccion dir){
		this.posicion = pos;
		this.id = id;
		this.oficio = oficio;
		this.habilidad = habilidad;
		this.direccion = dir;
		}
	public EstadoPooglin(){
		this.posicion = new Posicion(0,0);
		this.id = 0;
		this.oficio = 0;
		this.habilidad =0;
		this.direccion = new Direccion (0,0);
	}
	public EstadoPooglin(Pooglins p){
		this.posicion = p.getPosicion();
		this.id = p.getId();
		this.oficio = p.getOficioID();
		this.habilidad = p.getHabilidadID();
		this.direccion = p.getDireccion();
	}
	
	
	public int getPosicionX() {
		return this.posicion.getX();
	}
	public int getPosicionY() {
		return this.posicion.getY();
	}
	public int getId() {
		return id;
	}

	public int getOficio() {
		return oficio;
	}

	public int getHabilidad() {
		return habilidad;
	}
	
	
	public Direccion getDireccion() {
		return direccion;
	}
	
	public void setDireccion(Direccion direccion) {
		this.direccion = direccion;
	}
	
	public Element serializarJDOM() {
		Element raiz = new Element("EstadoPooglin");
		raiz.setAttribute("ID", new Integer(this.id).toString());
		raiz.setAttribute("Oficio", new Integer(this.oficio).toString());
		raiz.setAttribute("Habilidad", new Integer(this.habilidad).toString());
		raiz.addContent(this.posicion.serializarJDOM());
		raiz.addContent(this.direccion.serializarJDOM());
		return raiz;
	}
	
	public void hidratarJDOM(Element desde) {
		this.id = Integer.parseInt(desde.getAttributeValue("ID"));
		this.oficio = Integer.parseInt(desde.getAttributeValue("Oficio"));
		this.habilidad = Integer.parseInt(desde.getAttributeValue("Habilidad"));
		Element posicion = (Element)(desde.getChild("Posicion"));
		Posicion pos = new Posicion(0,0);
		pos.hidratarJDOM(posicion);
		this.posicion = pos;
		Element direccion = (Element)(desde.getChild("Direccion"));
		Direccion dir = new Direccion();
		dir.hidratarJDOM(direccion);
		if (dir.getDireccionY()==1)
			if (dir.getDireccionX()==0) dir.setDerecha(); else dir.subirDireccion();
		this.direccion = dir;
		
		
	}
	@Override
	public boolean equals(Object obj) {
		// TODO Auto-generated method stub
		return (((EstadoPooglin) obj).getId() == this.getId());
	}

	

	
}
