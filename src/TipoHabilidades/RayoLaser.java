package TipoHabilidades;
import Otros.Poogling;
import Otros.Vida;
import TipoTerrenos.Terreno;
import TipoTerrenos.Tierra;

public class RayoLaser extends Habilidad{

	@Override
	public void destruirTerreno(Terreno terreno) {
	    try{
	    	Tierra tierra = (Tierra)terreno;	
	    	Vida vida = tierra.getVida();
	    	if(vida.getCantidadVidas()<=4){
	    		vida.sacarVidas(1);
	    	}
	    }catch(ClassCastException e){
	    	System.err.println("No se pudo castear el terreno al tipo Tierra");
	    }
	}

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

	
}
