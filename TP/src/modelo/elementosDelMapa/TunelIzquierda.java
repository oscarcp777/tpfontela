package modelo.elementosDelMapa;

import java.awt.Image;
import java.awt.Toolkit;

import modelo.habilidadesPooglins.Habilidad;
import modelo.mapaDeJuego.Mapa;
import modelo.movimientoPooglins.DiagonalAbajoDerecha;
import modelo.movimientoPooglins.DiagonalArribaIzquierda;
import modelo.propiedadesDeElementos.Posicion;
import modelo.propiedadesDeElementos.Vida;
import modelo.utilitarios.Constants;

public class TunelIzquierda extends Terreno {

	public TunelIzquierda(){
		setVida(new Vida(5));
		image = Toolkit.getDefaultToolkit().getImage(Constants.PathImages.IMAGE_TUNEL_IZQUIERDA);
	}
	
	public TunelIzquierda(Posicion posicion){
		asignarPosicion(posicion);
		setVida(new Vida(5));
		image = Toolkit.getDefaultToolkit().getImage(Constants.PathImages.IMAGE_TUNEL_IZQUIERDA);
	}
	
	@Override
	public void colisionarPoogling(Poogling poogling) {
		
		if (this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteIzquierda().obtenerPosicionSiguienteAbajo())==
			 Constants.ValorComparador.IGUAL){
			poogling.inicializarPasosEnDireccion();
			poogling.redireccionar(DiagonalAbajoDerecha.getInstance());
		}else if (this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteIzquierda())==
		   	 	Constants.ValorComparador.IGUAL && poogling.veniaEnEsaDireccion(obtenerPosicion())){
			poogling.inicializarPasosEnDireccion();
			poogling.redireccionar(DiagonalArribaIzquierda.getInstance());
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
