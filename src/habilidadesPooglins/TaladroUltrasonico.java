package habilidadesPooglins;

import propiedadesDeElementos.Vida;
import elementosDelMapa.Poogling;
import elementosDelMapa.Terreno;
import elementosDelMapa.Tierra;

public class TaladroUltrasonico extends Habilidad {

	public TaladroUltrasonico(){
		
	}

	@Override
	public void aplicar(Poogling poogling) {
		// TODO Auto-generated method stub
	/*se pueden romper hasta 5 bloques de profundidad , recordar que
	 * la tierra se rompe con 4 vueltas de torpedo, y que la roca no se puede romper	
	 * 
	 */
	}
	
	public void aplicar(Terreno terreno){
		
	}
	@Override
	public void aplicar(Terreno terreno) {
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
