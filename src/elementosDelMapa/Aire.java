package elementosDelMapa;

import mapaDeJuego.Mapa;
import movimientoPooglins.Abajo;
import propiedadesDeElementos.Posicion;
import propiedadesDeElementos.Vida;
import habilidadesPooglins.Habilidad;
import utilitarios.Constants;

public class Aire extends Terreno{
	
	//Constructor por defecto
	public Aire(){
		setVida(new Vida(5)); //se setea la vida por default, pues 
	}						  //al hacer un cambio de tierra por aire debe definirse esta propiedad
	
	public Aire(Posicion posicion){
		asignarPosicion(posicion);
		setVida(new Vida(5));//se setea la vida por default, pues 
	}						 //al hacer un cambio de tierra por aire debe definirse esta propiedad
		
	
	
	//con aire este metodo no hace nada, dado que el pooglin puede moverse
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

	public void cambiarPorHielo(Mapa mapa){
		mapa.cambiarTerreno(new Hielo(obtenerPosicion()));
	}

}
