package vista.utilitarias;

import java.util.Iterator;
import java.util.LinkedList;

import vista.componentes.SpriteSimple;

public class IteradorListaCircular<SpriteSimple> implements Iterator<SpriteSimple> {

	Iterator<SpriteSimple> iterator;
	LinkedList<SpriteSimple> lista;
	 
	public IteradorListaCircular(LinkedList<SpriteSimple> lista){
		this.lista = lista;
		this.iterator = this.lista.iterator();
	}
	
	public boolean hasNext() {
		// TODO Auto-generated method stub
		return true;
	}

	public SpriteSimple next() {
		if(!this.iterator.hasNext()) this.iterator = this.lista.iterator();
		return this.iterator.next();
	}

	public void remove() {
		// TODO Auto-generated method stub
		this.iterator.remove();
	}

}
