package TipoHabilidades;

import Otros.Vida;
import TipoTerrenos.Terreno;
import TipoTerrenos.Tierra;

public class TaladroUltrasonico extends Habilidad {

	public TaladroUltrasonico(){
		
	}

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
}
