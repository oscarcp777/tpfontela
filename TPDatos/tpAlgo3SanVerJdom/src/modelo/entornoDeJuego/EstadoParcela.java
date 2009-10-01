package modelo.entornoDeJuego;

import org.jdom.Element;


import modelo.persistencia.SerializableJDOM;
import modelo.pooglins.Posicion;
/**
 * Clase: EstadoParcela.
 * Utilidad: Permite hacer consultas al MaterialDeTerreno y a la Posicion.
 * Colabora con: Posicion, MaterialDeTerreno.
 * */
public class EstadoParcela implements SerializableJDOM{

	

	private Posicion posicion;
	private MaterialDeTerreno material;
	
	
	public void setMaterial(MaterialDeTerreno material) {
		this.material = material;
	}

	public EstadoParcela(Posicion pos, MaterialDeTerreno mat){
		this.material = mat;
		this.posicion = pos;
	}
 
	public int getPosX(){
		return this.posicion.getX();
	}

	public int getPosY(){
		return this.posicion.getY();
	}

	public int getTipoMaterial(){
		return this.material.getTipoDeMaterial();
	}


	public Element serializarJDOM() {
		Element raiz = new Element("EstadoParcela");
		raiz.addContent(this.posicion.serializarJDOM());
		raiz.addContent(this.material.serializarJDOM());
		//raiz.setText("\n");
		return raiz;
	}

	public void hidratarJDOM(Element desde) {
		Element posicion = (Element)(desde.getChild("Posicion"));
		Posicion pos = new Posicion(0,0);
		pos.hidratarJDOM(posicion);
		this.posicion = pos;
		Element material = (Element)(desde.getChild("MaterialDeTerreno"));
		MaterialDeTerreno mat = new MaterialDeTerreno(true,true,true,true,0);
		mat.hidratarJDOM(material);
		this.material = mat;
		
	}

	@Override
	public String toString() {
		// TODO Auto-generated method stub
		String s = new String();
		s = s + this.getPosX() + " " + this.getPosY() + " Material: " + this.getTipoMaterial();
		return s;
	}

	public MaterialDeTerreno getMaterial() {
		return material;
	}



}
