package modelo.habilidadesPooglins;

import modelo.elementosDelMapa.Poogling;
import modelo.elementosDelMapa.Terreno;
import modelo.elementosDelMapa.TunelDerecha;
import modelo.elementosDelMapa.TunelIzquierda;
import modelo.mapaDeJuego.Mapa;
import modelo.movimientoPooglins.DiagonalArribaDerecha;
import modelo.movimientoPooglins.DiagonalArribaIzquierda;
import modelo.propiedadesDeElementos.Posicion;
import modelo.utilitarios.Constants;

public class TunelElectromagnetico extends Habilidad{

	public TunelElectromagnetico() {
		estadoHabilidad = new EstadoHabilidad();
		estadoHabilidad.activarHabilidad();
	}

	private boolean sePuedeConstruir(Mapa mapa, Posicion posicionUltima){
		if ((mapa.obtenerTerreno(posicionUltima))!=null){
			if(((Terreno)mapa.obtenerTerreno(posicionUltima)).isTraspasable())
			return true;
		return false;
		}
			
		return false;
	}
	
	@Override
	public void aplicarApooglin(Mapa mapa, Poogling poogling, Terreno terreno) {
		
		Posicion posicionSig = poogling.siguientePosicion();
		
		if((posicionSig.compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteDerecha())==
			   Constants.ValorComparador.IGUAL)&& sePuedeConstruir(mapa,posicionSig.obtenerPosicionSiguienteDerecha().obtenerPosicionSiguienteArriba()
				.obtenerPosicionSiguienteDerecha().obtenerPosicionSiguienteArriba())) //El pooglin se esta moviendo a la derecha, por lo que se pondra al lado dicho tunel
			
			poogling.redireccionar(DiagonalArribaDerecha.getInstance());
		
		else if((posicionSig.compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteIzquierda())==
			   Constants.ValorComparador.IGUAL) && sePuedeConstruir(mapa,posicionSig.obtenerPosicionSiguienteIzquierda().obtenerPosicionSiguienteArriba()
						.obtenerPosicionSiguienteIzquierda().obtenerPosicionSiguienteArriba())) //El pooglin se esta moviendo a la izquierda, por lo que se pondra al lado dicho tunel
			
			poogling.redireccionar(DiagonalArribaIzquierda.getInstance());
		
		poogling.desactivarHabilidad();
	
	}

	@Override
	public void aplicarAterreno(Mapa mapa, Terreno terreno, Poogling poogling) {
		// TODO Auto-generated method stub
		Posicion posicionSig = poogling.siguientePosicion();
		TunelDerecha tunel1;
		TunelDerecha tunel2;
		TunelIzquierda tunel3;
		TunelIzquierda tunel4;
		
		if((posicionSig.compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteDerecha())==
		   Constants.ValorComparador.IGUAL)&& sePuedeConstruir(mapa,posicionSig.obtenerPosicionSiguienteDerecha().obtenerPosicionSiguienteArriba()
			.obtenerPosicionSiguienteDerecha().obtenerPosicionSiguienteArriba())){ //El pooglin se esta moviendo a la derecha, por lo que se pondra al lado dicho tunel
			tunel1 = new TunelDerecha(posicionSig);
			tunel2 = new TunelDerecha(posicionSig.obtenerPosicionSiguienteDerecha().obtenerPosicionSiguienteArriba()); 
			mapa.cambiarTerreno(tunel1);
			mapa.cambiarTerreno(tunel2);
		}else if((posicionSig.compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteIzquierda())==
			   Constants.ValorComparador.IGUAL) && sePuedeConstruir(mapa,posicionSig.obtenerPosicionSiguienteIzquierda().obtenerPosicionSiguienteArriba()
						.obtenerPosicionSiguienteIzquierda().obtenerPosicionSiguienteArriba())){ //El pooglin se esta moviendo a la izquierda, por lo que se pondra al lado dicho tunel
			tunel3 = new TunelIzquierda(posicionSig);
			tunel4 = new TunelIzquierda(posicionSig.obtenerPosicionSiguienteIzquierda().obtenerPosicionSiguienteArriba()); 
			mapa.cambiarTerreno(tunel3);
			mapa.cambiarTerreno(tunel4);
		}

	}

	//Con esta habilidad puedo contruir un tunel en el mapa de juego
	@Override
	public boolean isConstruible() {
		// TODO Auto-generated method stub
		return true;
	}

	

}
