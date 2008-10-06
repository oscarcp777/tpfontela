package TipoPosicion;

public abstract class Posicionable implements Comparable{
	private Posicion posicion;
	private Propiedad propiedades;
	
	public void asignarPosicion(Posicion posicion){
		this.posicion=posicion;
	}
	
	public Posicion obtenerPosicion(){
		return posicion;
	}

	public void setPropiedades(Propiedad propiedades) {
		this.propiedades = propiedades;
	}

	public Propiedad getPropiedades() {
		return propiedades;
	}
}
