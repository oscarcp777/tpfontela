package modelo.elementosDelMapa;

import java.awt.Image;
import java.awt.Toolkit;

import modelo.habilidadesPooglins.Habilidad;
import modelo.mapaDeJuego.Mapa;
import modelo.movimientoPooglins.DiagonalAbajoDerecha;
import modelo.movimientoPooglins.DiagonalAbajoIzquierda;
import modelo.movimientoPooglins.DiagonalArribaDerecha;
import modelo.movimientoPooglins.DiagonalArribaIzquierda;
import modelo.propiedadesDeElementos.Posicion;
import modelo.propiedadesDeElementos.Vida;
import modelo.utilitarios.Colores;
import modelo.utilitarios.Constants;

public class TunelDerecha extends Terreno{

	public TunelDerecha(){
		setVida(new Vida(5));
		image = Toolkit.getDefaultToolkit().getImage(Constants.PathImages.IMAGE_TUNEL_DERECHA);
	}
	
	public TunelDerecha(Posicion posicion){
		asignarPosicion(posicion);
		setVida(new Vida(5));
		image = Toolkit.getDefaultToolkit().getImage(Constants.PathImages.IMAGE_TUNEL_DERECHA);
	}
	
	@Override
	public void colisionarPoogling(Poogling poogling) {
		
		if (this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteDerecha())==
				 Constants.ValorComparador.IGUAL && poogling.veniaEnEsaDireccion(obtenerPosicion())){
			poogling.inicializarPasosEnDireccion();
			poogling.redireccionar(DiagonalArribaDerecha.getInstance());
		}else if (this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteIzquierda().obtenerPosicionSiguienteAbajo())==
		   	 	Constants.ValorComparador.IGUAL){
			poogling.inicializarPasosEnDireccion();
			poogling.redireccionar(DiagonalAbajoIzquierda.getInstance());
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
