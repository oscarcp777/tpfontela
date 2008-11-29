package modelo.elementosDelMapa;

import java.awt.Image;
import java.awt.Toolkit;

import modelo.habilidadesPooglins.Habilidad;
import modelo.mapaDeJuego.Mapa;
import modelo.propiedadesDeElementos.Posicion;
import modelo.utilitarios.Colores;
import modelo.utilitarios.Constants;

public class Roca extends Terreno{

	
	//Constructor por defecto
	public Roca(){
		image = Toolkit.getDefaultToolkit().getImage("imagenes/roca.png");
	}
	
	public Roca(Posicion posicion){
		asignarPosicion(posicion);
	
	}

	@Override
	public void aplicar(Habilidad habilidad, Mapa mapa, Poogling poogling) {
		// TODO Auto-generated method stub
		
	}
	/*
	public void colisionarPoogling(Poogling poogling) {
		
		if((this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteAbajo())==
			Constants.ValorComparador.IGUAL) && (poogling.isConDireccionAbajo()) && (poogling.cantidadDePasosEnDireccion()==Constants.PooglinAlVacio.CANTIDAD_PASOS_AIRE_MUERE)) 
						
			poogling.quitarVida();
	
		if(this.obtenerPosicion().compareTo(poogling.siguientePosicion())==
			Constants.ValorComparador.IGUAL)
				
		    poogling.cambiarDireccionDeMovimiento();
		
		
		/*el if anterior seguido de esto && !poogling.isConHabilidad()||
		(poogling.isConHabilidad()&& 
		!poogling.habilidadAplicada().equalsIgnoreCase(Constants.NombreHabilidades.RAYO_LASER) &&
		!poogling.habilidadAplicada().equalsIgnoreCase(Constants.NombreHabilidades.TALADRO_ULTRASONICO)))
	}*/


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
