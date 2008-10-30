package habilidadesPooglins;
import propiedadesDeElementos.Vida;
import utilitarios.Constants;
import elementosDelMapa.Poogling;
import elementosDelMapa.Terreno;
import elementosDelMapa.Tierra;

public class RayoLaser extends Habilidad{

	@Override
	public void aplicar(Poogling poogling) {
		// TODO Auto-generated method stub
		/*si el pooglin tiene tierra en alguna de sus posiciones
		 *laterales puede "romperla" (reemplazarla por aire), tener en cuenta que 
		 *la tierra se pouede destruir con 4 disparos (o vuelta de torpedo)
		 *(a mi criterio tierra deberia de tener 4 vidas, e ir restandoselas, porque 
		 *puede que ese bloque sea disparado por distintos pooglin) 
		 */
	}

	//falta ver la posicion del pooglin 
	@Override
	public void aplicar(Terreno terreno) {

		if(((terreno.getNombreTerreno()==Constants.NombreTerreno.TIERRA))
			||((terreno.getNombreTerreno()==Constants.NombreTerreno.HIELO))
			){
		
		Vida vida = terreno.getVida();
		
		if(vida.getCantidadVidas()<=4)
		vida.sacarVidas(1);
		
	
			
			

	}

	
	}
}
