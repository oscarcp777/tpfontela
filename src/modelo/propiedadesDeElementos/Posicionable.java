package modelo.propiedadesDeElementos;


public abstract class Posicionable {
	private Posicion posicion;
	
	public Posicion obtenerPosicion(){
		return posicion;
	}
	
	public void asignarPosicion(Posicion posicion){
		this.posicion = posicion;
	}


}
