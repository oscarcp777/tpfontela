package elementosDelMapa;

import mapaDeJuego.Mapa;
import movimientoPooglins.Abajo;
import propiedadesDeElementos.Posicion;
import habilidadesPooglins.Habilidad;
import utilitarios.Constants;

public class Aire extends Terreno{
	
	//Constructor por defecto
	public Aire(){
		
	}
	
	public Aire(Posicion posicion){
		asignarPosicion(posicion);
		
	}
	
	//con aire este método no hace nada, dado que el pooglin puede moverse
	//libremente sobre este tipo de terreno.
	@Override
	public void colisionarPoogling(Poogling poogling) {
		
		if((this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteAbajo())==
			Constants.ValorComparador.IGUAL) && !poogling.isConDireccion())
			poogling.redireccionar(Abajo.getInstance());
			
	}

	@Override
	public String obtenerNombre() {
		return Constants.NombreTerrenos.AIRE;
	}

	@Override
	public void aplicar(Habilidad habilidad, Mapa mapa, Poogling poogling) {
		// TODO Auto-generated method stub
		
	}
		
	public void cambiarPorHielo(Mapa mapa){
		mapa.cambiarTerreno(new Hielo(obtenerPosicion()));
	}

}
