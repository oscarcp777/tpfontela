package modelo.pooglins;


import org.jdom.Element;

import modelo.persistencia.SerializableJDOM;
import modelo.movimientos.Direccion;
/**
 * Clase: Posicion.
 * Utilidad: Permite identificar la posicion actual, con respecto al Terreno que puede
 *           ocupar un elemento en particular, como un Pooglin o un tipo de terreno por
 *           ejemplo.
 * Utilizada por: Pooglin.
 * Colabora con: Direccion.
 * */
public class Posicion implements SerializableJDOM {
	
	private int x;
	private int y;
	
	public Posicion(int x, int y){
		this.x = x;
		this.y = y;
	}

	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}

	public int getY() {
		return y;
	}

	public void moverEnDireccion(Direccion direccion){
		this.x = this.x + direccion.getDireccionX();
		this.y = this.y + direccion.getDireccionY();
	}
	
	public void moverEnDireccion(Direccion direccion, int cantidadPosiciones){
		this.x = this.x + direccion.getDireccionX()*cantidadPosiciones;
		this.y = this.y + direccion.getDireccionY()*cantidadPosiciones;
	}
	
    public void setY(int y) {
		this.y = y;
	}
	
	/* testear que funcione*/
	public boolean equals(Object posicion) {
		return ((Posicion) posicion).getX() == this.getX() && (((Posicion) posicion).getY() == this.getY());
			
	}

	@Override
	public String toString() {
		String salida = ((Integer)this.x).toString().concat(", ").concat(((Integer)this.y).toString());
		return salida;
	}
	
	
	public int hashCode() {
		// TODO Auto-generated method stub
		return ((Integer)this.getX()).hashCode() + ((Integer)this.getY()).hashCode();
	}
	
	public Posicion copiar(){
		return new Posicion(this.getX(), this.getY());
	}
	
	
	public Element serializarJDOM() {
		Element raiz = new Element("Posicion");
		raiz.setAttribute("PosX", (new Integer(this.x).toString()));
		raiz.setAttribute("PosY", new Integer(this.y).toString());
		return raiz;
	}
		
	public void hidratarJDOM(Element desde) {
			this.x = Integer.parseInt(desde.getAttributeValue("PosX"));
			this.y = Integer.parseInt(desde.getAttributeValue("PosY"));
			
			
	}



}
