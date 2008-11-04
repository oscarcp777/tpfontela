package elementosDelMapa;

import mapaDeJuego.Mapa;
import propiedadesDeElementos.Posicion;
import habilidadesPooglins.Habilidad;
import utilitarios.Constants;

public class Tierra extends Terreno{

	//Constructor por defecto
	public Tierra(){
			
	}
	
	public Tierra(Posicion posicion){
		asignarPosicion(posicion);
	}


	@Override
	public String obtenerNombre() {
		return Constants.NombreTerrenos.TIERRA;		
	}


	@Override
	public void aplicar(Habilidad habilidad, Mapa mapa, Poogling poogling) {
		/*
		//Si la siguiente posicion del pooglin (derecha,izquierda o abajo) coincide
		//con la posicion de tierra, podrá sacarle vidas.
		if((this.obtenerPosicion().compareTo(posicionPooglin.obtenerPosicionSiguienteAbajo())==
			Constants.ValorComparador.IGUAL)||(this.obtenerPosicion().compareTo(posicionPooglin.obtenerPosicionSiguienteDerecha())==
			Constants.ValorComparador.IGUAL)||(this.obtenerPosicion().compareTo(posicionPooglin.obtenerPosicionSiguienteDerecha())==
			Constants.ValorComparador.IGUAL)){
			*/
			habilidad.aplicarAterreno(mapa,this,poogling); //le aplica la habilidad rayoLaser o taladroUltrasonico, depende del tipo de habilidad
														  //que se reciba.	
		
		
	}
	
	
	public void colisionarPoogling(Poogling poogling) {
		
		if((this.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteAbajo())==
			Constants.ValorComparador.IGUAL) && (poogling.cantidadDePasosEnDireccion()==Constants.PooglinAlVacio.CANTIDAD_PASOS_AIRE_MUERE)) 
						
			poogling.quitarVida();
	
		else if(this.obtenerPosicion().compareTo(poogling.siguientePosicion())==
			Constants.ValorComparador.IGUAL && !poogling.quieto())
				
		    poogling.cambiarDireccionDeMovimiento();
		
	}
	
	public void cambiarPorAire(Mapa mapa){
		mapa.cambiarTerreno(new Aire(obtenerPosicion()));
	}

}
