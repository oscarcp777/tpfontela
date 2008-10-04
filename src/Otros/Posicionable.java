package Otros;

public abstract class Posicionable {
	private Posicion posicion;
	
	public void asignarPosicion(Posicion posicion){
		this.posicion=posicion;
	}
	
	public Posicion obtenerPosicion(){
		return posicion;
	}
}
