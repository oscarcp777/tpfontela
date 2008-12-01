package modelo.elementosDelMapa;

import java.awt.Image;
import java.awt.Toolkit;

import modelo.habilidadesPooglins.Habilidad;
import modelo.mapaDeJuego.Mapa;
import modelo.movimientoPooglins.Abajo;
import modelo.propiedadesDeElementos.Colisionable;
import modelo.propiedadesDeElementos.Posicion;
import modelo.propiedadesDeElementos.Vida;
import modelo.utilitarios.Colores;
import modelo.utilitarios.Constants;

public class Aire extends Terreno{
	
	//Constructor por defecto
	public Aire(){
		setVida(new Vida(5)); //se setea la vida por default, pues 
		image = Toolkit.getDefaultToolkit().getImage("imagenes/aire.png");									//al hacer un cambio de tierra por aire debe definirse esta propiedad
	}
		
	public Aire(Posicion posicion){
		image = Toolkit.getDefaultToolkit().getImage("imagenes/aire.png");
		asignarPosicion(posicion);
		setVida(new Vida(5));//se setea la vida por default, pues 
	}						 //al hacer un cambio de tierra por aire debe definirse esta propiedad
		
	
	
	//con aire este metodo no hace nada, dado que el pooglin puede moverse
	//libremente sobre este tipo de terreno.
	@Override
	public void colisionarPoogling(Poogling poogling) {
		
		if((this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteAbajo())==
			Constants.ValorComparador.IGUAL))
			poogling.redireccionar(Abajo.getInstance());
			
	}

	public void cambiarPorHielo(Mapa mapa){
		mapa.cambiarTerreno(new Hielo(obtenerPosicion()));
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

	/*
	 * El pooglin puede atravesar este tipo de terreno
	 * 
	 * (non-Javadoc)
	 * @see modelo.elementosDelMapa.Terreno#isTraspasable()
	 */
	@Override
	public boolean isTraspasable() {
		// TODO Auto-generated method stub
		return true;
	}

}
