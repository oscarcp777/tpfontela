package habilidadesPooglins;

import mapaDeJuego.Mapa;
import movimientoPooglins.DiagonalArribaDerecha;
import movimientoPooglins.DiagonalArribaIzquierda;
import movimientoPooglins.Direccion;
import propiedadesDeElementos.Posicion;
import propiedadesDeElementos.Vida;
import utilitarios.Constants;
import elementosDelMapa.Poogling;
import elementosDelMapa.Terreno;
import elementosDelMapa.Tunel;

public class TunelElectromagnetico extends Habilidad{

	public TunelElectromagnetico() {
		estadoHabilidad = new EstadoHabilidad();
		estadoHabilidad.activarHabilidad();
	}

	private boolean sePuedeConstruir(Mapa mapa, Posicion posicionUltima){
		if (((Terreno)mapa.obtenerTerreno(posicionUltima)).obtenerNombre().equalsIgnoreCase(Constants.NombreTerrenos.AIRE))
			return true;
		else return false;
	}
	
	@Override
	public void aplicarApooglin(Mapa mapa, Poogling poogling, Terreno terreno) {
		
		Posicion posicionSig = poogling.siguientePosicion();
		Tunel tunel1;
		Tunel tunel2;
		
		if((posicionSig.compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteDerecha())==
		   Constants.ValorComparador.IGUAL)&& sePuedeConstruir(mapa,posicionSig.obtenerPosicionSiguienteDerecha().obtenerPosicionSiguienteArriba()
			.obtenerPosicionSiguienteDerecha().obtenerPosicionSiguienteArriba())){ //El pooglin se esta moviendo a la derecha, por lo que se pondra al lado dicho tunel
			tunel1 = new Tunel(posicionSig);
			tunel2 = new Tunel(posicionSig.obtenerPosicionSiguienteDerecha().obtenerPosicionSiguienteArriba()); 
			mapa.cambiarTerreno(tunel1);
			mapa.cambiarTerreno(tunel2);
			poogling.redireccionar(DiagonalArribaDerecha.getInstance());
		}else if((posicionSig.compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteIzquierda())==
			   Constants.ValorComparador.IGUAL) && sePuedeConstruir(mapa,posicionSig.obtenerPosicionSiguienteIzquierda().obtenerPosicionSiguienteArriba()
						.obtenerPosicionSiguienteIzquierda().obtenerPosicionSiguienteArriba())){ //El pooglin se esta moviendo a la izquierda, por lo que se pondra al lado dicho tunel
			tunel1 = new Tunel(posicionSig);
			tunel2 = new Tunel(posicionSig.obtenerPosicionSiguienteIzquierda().obtenerPosicionSiguienteArriba()); 
			mapa.cambiarTerreno(tunel1);
			mapa.cambiarTerreno(tunel2);
			poogling.redireccionar(DiagonalArribaIzquierda.getInstance());
		}else if(poogling.cantidadDePasosEnDireccion()==2){
			poogling.cambiarDireccionDeMovimiento();
			poogling.desactivarHabilidad();
		}
		
	}

	@Override
	public String getNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreHabilidades.TUNEL_ELECTROMAGNETICO;
	}

	@Override
	public void aplicarAterreno(Mapa mapa, Terreno terreno, Poogling poogling) {
		// TODO Auto-generated method stub
		
	}

	

}
