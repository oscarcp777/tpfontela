package modelo.movimientos;

import org.jdom.Element;

import modelo.persistencia.SerializableJDOM;

/**
 * Clase: Direccion
 * Utilidad: Utilizada para representar la Direccion actual del Pooglin, se utiliza 
 * 			 la Direccion como un versor (i,j) donde Derecha es (1,0), Izquierda (-1,0), 
 * 			 Arriba(0,1) y Abajo (0,-1).
 *           Utiliza un metodo invertir para pasar de Derecha a Izquierda y de 
 *           Arriba a Abajo.
 * Utilizada por: Oficio.
 * */
public class Direccion implements SerializableJDOM{
	
	

	private int x;
	private int y;
	/*
	 * la direeccion se expresa como versores 
	 */
	public Direccion(){
		this.x = 1;
		this.y = 0;
	}
	public Direccion(int dirX, int dirY){
		this.x = dirX;
		this.y = dirY;
	}
	public int getDireccionX() {
		return x;
	}
	public int getDireccionY() {
		return y;
	}
	public void setAbajo(){
		this.y = 1;
		this.x = 0;
	}
	
	public void setDerecha(){
		this.y = 0;
		this.x = 1;
	}
	
	public void setHorizontal(){
		this.y = 0;
	}
	public void setVertical(){
		this.x = 0;
	}
	
	public void setIzquierda(){
		this.y = 0;
		this.x = -1;
	}
	
	public void invertir(){
		this.x = this.x * -1;
		this.y = this.y * -1;
	}

	public void subirDireccion(){
		if(this.y>=0)this.y--;
	}
	public void bajarDireccion(){
		if(this.y<=0)this.y++;
	}
	public void modificarDireccion(){
		if(this.esDireccionDerecha()) this.setDerecha();
		if(this.esDireccionIzquierda()) this.setIzquierda();
	}

	public Direccion copiar(){
		return new Direccion(this.x, this.y);
	}
	@Override
	protected Object clone() throws CloneNotSupportedException {
		// TODO Auto-generated method stub
		return super.clone();
	}
	
	public boolean esDireccionDerecha(){
		return this.getDireccionX() == 1;
	}
	
	public boolean esDireccionIzquierda(){
		return this.getDireccionX() == -1;
	}

	public Element serializarJDOM() {
		Element raiz = new Element("Direccion");
		raiz.setAttribute("DirX", (new Integer(this.x).toString()));
		raiz.setAttribute("DirY", new Integer(this.y).toString());
		return raiz;
	}
		
	public void hidratarJDOM(Element desde) {
			this.x = Integer.parseInt(desde.getAttributeValue("DirX"));
			this.y = Integer.parseInt(desde.getAttributeValue("DirY"));
			
			
	}
}
