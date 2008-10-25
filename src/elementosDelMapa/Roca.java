package elementosDelMapa;

import propiedadesDeElementos.Posicion;
import habilidadesPooglins.Habilidad;
import utilitarios.Constants;

public class Roca extends Terreno{

	
	//Constructor por defecto
	public Roca(){
		
	}
	
	public Roca(Posicion posicion){
		asignarPosicion(posicion);
	}
	
	@Override
	public void colisionarPoogling(Poogling poogling) {
		poogling.getMovimiento().cambiarMovimiento();
	}


	@Override
	public void aplicarHabilidad(Habilidad habilidad) {
		// TODO Auto-generated method stub
		
	}

	

}
