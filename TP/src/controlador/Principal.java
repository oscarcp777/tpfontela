package controlador;
import modelo.mapaDeJuego.Mapa;
import modelo.mapaDeJuego.Planeta;
import modelo.utilitarios.Constants;
import modelo.xml.XMLcarga;


public class Principal {
  
	public static void main(String[] args){		
		
		XMLcarga xmlcarga = new XMLcarga(Constants.MapasDeJuego.NIVEL_1);
		Planeta planeta = new Planeta(xmlcarga.getInfoNivel()); 		
		Mapa mapaDeJuego = planeta.obtenerMapaDeJuego();
		ControlDeJuego controladorDeJuego = new ControlDeJuego(mapaDeJuego);
	}

}
