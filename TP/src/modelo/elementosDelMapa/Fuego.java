package modelo.elementosDelMapa;

import java.awt.Image;
import java.awt.Toolkit;

import modelo.habilidadesPooglins.Habilidad;
import modelo.mapaDeJuego.Mapa;
import modelo.propiedadesDeElementos.Posicion;
import modelo.propiedadesDeElementos.Vida;
import modelo.utilitarios.Colores;
import modelo.utilitarios.Constants;

public class Fuego extends Terreno{

	//Constructor por defecto
	public Fuego(){
		image = Toolkit.getDefaultToolkit().getImage("imagenes/fuego.png");
	}
	
	public Fuego(Posicion posicion){
		asignarPosicion(posicion);
		
	}
	
	//En caso de que el pooglin colisione con este
	//tipo de terreno, el mismo morira de manera
	//instantanea.
	@Override
	public void colisionarPoogling(Poogling poogling) {
		if(this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteAbajo())==
			Constants.ValorComparador.IGUAL || this.obtenerPosicion().compareTo(poogling.obtenerPosicion())==Constants.ValorComparador.IGUAL)		
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

