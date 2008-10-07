package TipoHabilidades;

import Otros.Vida;
import TipoPosicion.Posicion;
import TipoTerrenos.Aire;
import TipoTerrenos.Terreno;
import TipoTerrenos.Tierra;
import Utilidades.Constants;

public class TaladroUltrasonico extends Habilidad {

	public TaladroUltrasonico(){
		
	}


	public void atacarTerreno(Terreno terreno,Posicion posicionPooglin) {
	    
		//El compare devuelve menor si la posicion del pooglin (y-1) es igual a la posicion (y) del terreno
		//y en este caso el TaladroUltrasonico puede sacarle vidas al terreno de tipo tierra
		if(terreno.getNombre().compareTo(Constants.NombreTerreno.TIERRA)==Constants.ValorComparador.IGUAL 
		   && compare(terreno.obtenerPosicion(),posicionPooglin)==Constants.ValorComparador.MENOR){
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
	public int compare(Object arg0, Object arg1) {
		Posicion posicionTerreno = (Posicion)arg0;
		Posicion posicionPooglin = (Posicion)arg1;
		
		if(posicionTerreno.getPosicionY()==posicionPooglin.getPosicionY()-1)
		return Constants.ValorComparador.MENOR;
		else if(posicionTerreno.getPosicionY()==posicionPooglin.getPosicionY())
			return Constants.ValorComparador.IGUAL;
		else 
			return Constants.ValorComparador.MAYOR;
	}
	

}
