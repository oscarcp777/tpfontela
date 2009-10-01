package vista.utilitarias;

import java.util.Iterator;
import java.util.LinkedList;

public class ListaCircular<SpriteSimple> extends LinkedList<SpriteSimple> {
	
	private LinkedList<SpriteSimple> lista;
	
	public ListaCircular(){
		this.lista = new LinkedList<SpriteSimple>();
	}

	@Override
	public boolean add(SpriteSimple o) {
		// TODO Auto-generated method stub
		return lista.add(o);
	}

	@Override
	public Iterator<SpriteSimple> iterator() {
		// TODO Auto-generated method stub
		return new IteradorListaCircular<SpriteSimple>(lista);
	}
	
	

}
