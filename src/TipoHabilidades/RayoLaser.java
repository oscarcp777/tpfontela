package TipoHabilidades;

import Otros.Vida;
import TipoPosicion.Posicion;
import TipoTerrenos.Aire;
import TipoTerrenos.Terreno;
import TipoTerrenos.Tierra;
import Utilidades.Constants;

public class RayoLaser extends Habilidad{


	public void atacarTerreno(Terreno terreno,Posicion posicionPooglin) {
	    
		if(terreno.getNombre().compareTo(Constants.NombreTerreno.TIERRA)==Constants.ValorComparador.IGUAL 
		   && compare(terreno.obtenerPosicion(),posicionPooglin)!=Constants.ValorComparador.IGUAL){
	    	Tierra tierra = (Tierra)terreno;	
	    	Vida vida = tierra.getVida();
	    	if(vida.getCantidadVidas()>0){
	    		vida.sacarVidas(1);
	    	}else{
	    		Aire aire = new Aire();
	    		aire.asignarPosicion(terreno.obtenerPosicion());
	    		terreno = aire;
	    	}
		}
	}

	@Override
	public int compare(Object o1, Object o2) {
		Posicion posicionTerreno = (Posicion)o1;
		Posicion posicionPooglin = (Posicion)o2;
		
		if(posicionPooglin.getPosicionX()==posicionTerreno.getPosicionX()-1) //lateral derecho para el pooglin
		return Constants.ValorComparador.MENOR;
		else if(posicionPooglin.getPosicionX()==posicionTerreno.getPosicionX()+1) //lateral izquierdo para el pooglin
			return Constants.ValorComparador.MAYOR;
		else 
			return Constants.ValorComparador.IGUAL; //no es un lateral y por lo tanto es un valor no valido 
	}
	
	
	
	
}
