package modelo.elementosDelMapa;

import java.awt.Image;
import java.awt.Toolkit;

import modelo.habilidadesPooglins.Habilidad;
import modelo.mapaDeJuego.Mapa;
import modelo.propiedadesDeElementos.Posicion;
import modelo.propiedadesDeElementos.Velocidad;
import modelo.propiedadesDeElementos.Vida;
import modelo.utilitarios.Colores;
import modelo.utilitarios.Constants;



public class Hielo extends Terreno{

	//Constructor por defecto
	public Hielo(){
		image = Toolkit.getDefaultToolkit().getImage("imagenes/hielo.png");	
	}
	
	public Hielo(Posicion posicion){
		asignarPosicion(posicion);
		setVida(new Vida(5));
		image = Toolkit.getDefaultToolkit().getImage("imagenes/hielo.png");	
		
	}
	
	@Override
	public void colisionarPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		if(this.obtenerPosicion().compareTo(poogling.siguientePosicion())==
			Constants.ValorComparador.IGUAL) //el pooglin choca con el hielo frontalmente

			poogling.cambiarDireccionDeMovimiento();

		else if(this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteAbajo())==
			Constants.ValorComparador.IGUAL){ //el pooglin pisa el hielo y por ende duplica su velocidad

			Velocidad velocidadPoogling=poogling.getVelocidad();
			velocidadPoogling.aumentarVelocidad();
		}
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

