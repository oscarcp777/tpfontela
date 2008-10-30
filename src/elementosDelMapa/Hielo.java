package elementosDelMapa;

import mapaDeJuego.Mapa;
import propiedadesDeElementos.Posicion;
import propiedadesDeElementos.Velocidad;
import habilidadesPooglins.Habilidad;
import utilitarios.Constants;



public class Hielo extends Terreno{

	//Constructor por defecto
	public Hielo(){
		setNombreTerreno(Constants.NombreTerreno.HIELO);		
	}
	
	public Hielo(Posicion posicion){
		asignarPosicion(posicion);
		setNombreTerreno(Constants.NombreTerreno.HIELO);
	}
	
	@Override
	public void colisionarPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		Velocidad velocidadPoogling=poogling.getVelocidad();
		int valorVelocidad=velocidadPoogling.getVelocidad();
		velocidadPoogling.setVelocidad((valorVelocidad+valorVelocidad));
		poogling.setVelocidad(velocidadPoogling);
	}

}

