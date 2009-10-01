package vista.manejadores;


import modelo.control.Nivel;
import modelo.entornoDeJuego.Mapa;
import modelo.persistencia.Persistidor;

public class LevantaMapas {

	private static LevantaMapas instance;
	
	private LevantaMapas() {
		
	}
	
	public static LevantaMapas getIntance() {
		if(instance == null)instance = new LevantaMapas();
		return instance;
	}

	public Mapa cargarMapa(int idNivel) {
		Nivel nivel = new Nivel();
		try{
			Persistidor.recuperar("XMLPersistencia/" + idNivel +".xml", nivel);

		}catch (Exception e) {
			// TODO: handle exception
		}
		Mapa mapa = new Mapa(nivel); 
		return mapa;
	}
	
	public Mapa cargarMapa(String nombreArchivo) {
		
		//ESTO NO ES ASI! VER COMO SE HACE!
		
		Nivel nivel = new Nivel();
		try{
			Persistidor.recuperar("XMLPersistencia/" + nombreArchivo +".xml", nivel);

		}catch (Exception e) {
			// TODO: handle exception
		}
		Mapa mapa = new Mapa(nivel); 
		return mapa;
	}

}
