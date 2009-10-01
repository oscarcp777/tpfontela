package vista.utilitarias;

import java.util.HashMap;

import vista.componentes.SpriteSimple;

public class ImagenesParcela {
	private HashMap<Integer, SpriteSimple> imagenes;
	private static ImagenesParcela instance;
	
		
	public static ImagenesParcela getInstance(){
		if(instance == null) {
			instance = new ImagenesParcela();
			instance.imagenes = new HashMap<Integer, SpriteSimple>();
		}
		
		return instance;
	}
	public SpriteSimple getImagen(Integer id){
		if (this.instance.imagenes.get(id) == null){
			this.cargarImagen(id);
			}
		
		return ImagenesParcela.instance.imagenes.get(id);
	}

	private void cargarImagen(Integer id) {
		// TODO Auto-generated method stub
		ImagenesParcela.getInstance().agregarImagen(id, CargadorImagenesTerreno.crearImagen(id));		
	}

	
	@SuppressWarnings("static-access")
	public void agregarImagen(Integer id, SpriteSimple i){
		this.instance.imagenes.put(id, i);
	}
}
