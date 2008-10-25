package elementosDelMapa;

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
	public void aplicarHabilidad(Habilidad habilidad) {
		
		
	}

}
