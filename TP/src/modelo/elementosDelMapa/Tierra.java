package modelo.elementosDelMapa;

import java.awt.Image;
import java.awt.Toolkit;

import modelo.mapaDeJuego.Mapa;
import modelo.propiedadesDeElementos.Posicion;
import modelo.propiedadesDeElementos.Vida;
import modelo.utilitarios.Colores;
import modelo.utilitarios.Constants;

public class Tierra extends Terreno{

	//Constructor por defecto
	public Tierra(){
		image = Toolkit.getDefaultToolkit().getImage("imagenes/tierra.png");	
	}
	
	public Tierra(Posicion posicion){
		asignarPosicion(posicion);
	}
	
	public void cambiarPorAire(Mapa mapa){
		mapa.cambiarTerreno(new Aire(obtenerPosicion()));
	}


	@Override
	public Image getImage() {
		
		return image;
	}

	//Unico tipo de terreno que puede destruir el poogling con 
	//la habilidad de rayo laser o taladro ultrasonico
	@Override
	public boolean isRompible() {
		// TODO Auto-generated method stub
		return true;
	}

	@Override
	public boolean isTraspasable() {
		// TODO Auto-generated method stub
		return false;
	}

}
