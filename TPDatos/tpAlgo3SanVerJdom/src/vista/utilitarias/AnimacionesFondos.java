package vista.utilitarias;

import java.util.HashMap;

import vista.componentes.SpriteSimple;
import vista.utilitarias.ListaCircular;

public class AnimacionesFondos{
	
	private HashMap<Integer, ListaCircular> secuenciaDeImagenes;
	private static AnimacionesFondos instance;
	
	public static AnimacionesFondos getInstance(){
		if(instance == null) {
			instance = new AnimacionesFondos();
			instance.secuenciaDeImagenes = new HashMap<Integer, ListaCircular>();
		}
		
		return instance;
	}
	public ListaCircular<SpriteSimple> getSecuenciaDeImagen(Integer id){
		
		if (this.instance.secuenciaDeImagenes.get(id) == null){
		this.cargarImagen(id);
		}
		return this.instance.secuenciaDeImagenes.get(id);
	}
	
	private void cargarImagen(Integer id) {
		// TODO Auto-generated method stub
		AnimacionesFondos.getInstance().agregarSecuenciaDeImagen(id, CargadorImagenesDeFondo.crearImagen(id));		
	}
	@SuppressWarnings("static-access")
	public void agregarSecuenciaDeImagen(Integer id, ListaCircular<SpriteSimple> secuenciaDeImagenes){
		this.instance.secuenciaDeImagenes.put(id, secuenciaDeImagenes);
	}
}
