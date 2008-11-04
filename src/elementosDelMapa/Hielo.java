package elementosDelMapa;

import mapaDeJuego.Mapa;
import propiedadesDeElementos.Posicion;
import propiedadesDeElementos.Velocidad;
import habilidadesPooglins.Habilidad;
import utilitarios.Constants;



public class Hielo extends Terreno{

	//Constructor por defecto
	public Hielo(){
				
	}
	
	public Hielo(Posicion posicion){
		asignarPosicion(posicion);
		
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
			int valorVelocidad=velocidadPoogling.getVelocidad();
			velocidadPoogling.setVelocidad((valorVelocidad+valorVelocidad));
			poogling.setVelocidad(velocidadPoogling);
		}
	}

	@Override
	public String obtenerNombre() {
		return Constants.NombreTerrenos.HIELO;		
	}

	@Override
	public void aplicar(Habilidad habilidad, Mapa mapa, Poogling poogling) {
		// TODO Auto-generated method stub
		
	}

}

