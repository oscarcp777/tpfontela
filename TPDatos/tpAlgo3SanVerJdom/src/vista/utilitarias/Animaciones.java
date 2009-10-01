package vista.utilitarias;

import java.util.HashMap;

import vista.componentes.SpriteSimple;
import vista.utilitarias.ListaCircular;

public class Animaciones {
	protected HashMap<Integer, ListaCircular> secuenciaDeImagenes;
	protected static Animaciones instance;
	

	public static Animaciones getInstance(){
		if(instance == null) {
			instance = new Animaciones();
			instance.secuenciaDeImagenes = new HashMap<Integer, ListaCircular>();
		}
		
		return instance;
	}
	
	public ListaCircular<SpriteSimple> getSecuenciaDeImagen(Integer id){
		return this.instance.secuenciaDeImagenes.get(id);
	}
	
	@SuppressWarnings("static-access")
	public void agregarSecuenciaDeImagen(Integer id, ListaCircular secuenciaDeImagenes){
		this.instance.secuenciaDeImagenes.put(id, secuenciaDeImagenes);
	}



}
