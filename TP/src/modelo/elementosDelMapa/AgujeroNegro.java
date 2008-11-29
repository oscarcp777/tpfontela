package modelo.elementosDelMapa;

import java.awt.Image;
import java.awt.Toolkit;
import java.lang.annotation.*;
import modelo.habilidadesPooglins.Habilidad;
import modelo.mapaDeJuego.Mapa;
import modelo.propiedadesDeElementos.Posicion;
import modelo.propiedadesDeElementos.Vida;
import modelo.utilitarios.Colores;
import modelo.utilitarios.Constants;

public class AgujeroNegro extends Terreno{

	//Constructor por defecto
	public AgujeroNegro(){
	   image = Toolkit.getDefaultToolkit().getImage("imagenes/aire.png");
	}
	
	public AgujeroNegro(Posicion posicion){
		asignarPosicion(posicion);
		
	}
	
	//hace lo mismo que fuego
	@Override
	public void colisionarPoogling(Poogling poogling) {
		poogling.quitarVida();
	}


	@Override
	public void aplicar(Habilidad habilidad, Mapa mapa, Poogling poogling) {
		// TODO Auto-generated method stub
		
	}


	@Override
	public Image getImage() {
		// TODO Auto-generated method stub
		return image;
	}

	@Override
	public boolean isRompible() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean isTraspasable() {
		// TODO Auto-generated method stub
		return false;
	}
	
}
