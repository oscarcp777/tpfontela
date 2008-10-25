package elementosDelMapa;

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
	
	public boolean movimientoPooglingValido(Poogling poogling){
		return true;
	}

	//con aire este método no hace nada, dado que el pooglin puede moverse
	//libremente sobre este tipo de terreno.
	@Override
	public void colisionarPoogling(Poogling poogling) {
	
	}

	@Override
	public void aplicarHabilidad(Habilidad habilidad) {
		// TODO Auto-generated method stub
		
	}

}
