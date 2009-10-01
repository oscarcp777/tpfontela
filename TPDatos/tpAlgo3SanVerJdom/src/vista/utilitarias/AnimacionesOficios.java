package vista.utilitarias;

import java.awt.Image;
import java.util.HashMap;

import vista.componentes.SpriteSimple;
import vista.utilitarias.ListaCircular;



public class AnimacionesOficios{
	
	private HashMap<Integer, ListaCircular> secuenciaDeImagenes;
	private static AnimacionesOficios instance;
	
	public static AnimacionesOficios getInstance(){
		if(instance == null) {
			instance = new AnimacionesOficios();
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
		AnimacionesOficios.getInstance().agregarSecuenciaDeImagen(id, CargadorDeListasImagenes.crearListaDeSecuencias(id));		
	}
	@SuppressWarnings("static-access")
	public void agregarSecuenciaDeImagen(Integer id, ListaCircular secuenciaDeImagenes){
		this.instance.secuenciaDeImagenes.put(id, secuenciaDeImagenes);
	}
}
