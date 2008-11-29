package modelo.habilidadesPooglins;

import modelo.elementosDelMapa.Poogling;
import modelo.elementosDelMapa.Terreno;
import modelo.mapaDeJuego.Mapa;
import modelo.movimientoPooglins.PasosEnDireccion;
import modelo.propiedadesDeElementos.Posicion;
import modelo.utilitarios.Constants;
import modelo.utilitarios.Constants.ValorComparador;

public class Teletransportacion extends Habilidad{
		
	
		public Teletransportacion(){
			estadoHabilidad = new EstadoHabilidad();
			estadoHabilidad.activarHabilidad();
		}
		
		@Override
		public void aplicarApooglin(Mapa mapa, Poogling poogling, Terreno terreno) {

			if(poogling.obtenerPosicion().compareTo(terreno.obtenerPosicion().obtenerPosicionSiguienteArriba())==
				Constants.ValorComparador.IGUAL){ //el terreno contiguo que se le pasa por parametro es el piso del pooglin
				PasosEnDireccion pasosEnDireccion = new PasosEnDireccion();
				pasosEnDireccion.darPasosEnDireccion(5);
				Posicion posicionTeletransportacion=poogling.avanzarEnDireccion(pasosEnDireccion);
				Terreno terrenoTeletranportacion = (Terreno)mapa.obtenerTerreno(posicionTeletransportacion);
				if(terrenoTeletranportacion!=null && terrenoTeletranportacion.isTraspasable()){ //si el terreno esta dentro de los limites del mapa  
					poogling.asignarPosicion(posicionTeletransportacion);						 //y si es aire se teletransportara a esa posicion.			
					poogling.actualizarPosicionDeMovimiento(posicionTeletransportacion);
				}
				poogling.desactivarHabilidad();
			}
		}


		@Override
		public void aplicarAterreno(Mapa mapa, Terreno terreno,
				Poogling poogling) {
			// TODO Auto-generated method stub
			//No aplica nada sobre el terreno
		}

		@Override
		public boolean isConstruible() {
			// TODO Auto-generated method stub
			return false;
		}

		
		
}
