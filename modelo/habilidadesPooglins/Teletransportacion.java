package habilidadesPooglins;

import propiedadesDeElementos.Posicion;
import mapaDeJuego.Mapa;
import movimientoPooglins.PasosEnDireccion;
import utilitarios.Constants;
import utilitarios.Constants.ValorComparador;
import elementosDelMapa.Poogling;
import elementosDelMapa.Terreno;

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
				if(terrenoTeletranportacion!=null && terrenoTeletranportacion.obtenerNombre().equalsIgnoreCase(Constants.NombreTerrenos.AIRE)){ //si el terreno esta dentro de los limites del mapa  
					poogling.asignarPosicion(posicionTeletransportacion);										 //y si es aire se teletransportara a esa posicion.			
					poogling.desactivarHabilidad();
				}
			}
		}

		@Override
		public String getNombre() {
			// TODO Auto-generated method stub
			return Constants.NombreHabilidades.TELETRANSPORTACION;
		}

		@Override
		public void aplicarAterreno(Mapa mapa, Terreno terreno,
				Poogling poogling) {
			// TODO Auto-generated method stub
			
		}

		
		
}
