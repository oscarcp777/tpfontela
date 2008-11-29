package modelo.habilidadesPooglins;

import modelo.elementosDelMapa.Poogling;
import modelo.elementosDelMapa.Terreno;
import modelo.elementosDelMapa.Tierra;
import modelo.mapaDeJuego.Mapa;
import modelo.movimientoPooglins.Abajo;
import modelo.propiedadesDeElementos.Vida;
import modelo.utilitarios.Constants;

public class TaladroUltrasonico extends Habilidad {

	public TaladroUltrasonico(){
		estadoHabilidad = new EstadoHabilidad();
		estadoHabilidad.activarHabilidad();
	}

	@Override
	public void aplicarApooglin(Mapa mapa, Poogling poogling, Terreno terreno) {
		// TODO Auto-generated method stub
	
		if(terreno.isRompible()&&(terreno.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteAbajo())==
			Constants.ValorComparador.IGUAL)) {
			poogling.redireccionar(Abajo.getInstance());
			Vida vida = terreno.getVida();
			
			if(vida.hayVida()){
				poogling.invalidarMovimiento(true);
				poogling.inicializarPasosEnDireccion();//el contador lo pongo en 0
				poogling.contarPasos(false);
			}
			
			if(!vida.hayVida()){ //no puede ser un else if porque cuando sale de este metodo no y destruyo el terreno no moveria al pooglin pues quedaria seteado con movimiento false
				poogling.invalidarMovimiento(false);
				poogling.contarPasos(true);
			}
		}
	}
	
	@Override
	public void aplicarAterreno(Mapa mapa, Terreno terreno, Poogling poogling) {
			
		//Si el terreno esta por debajo del pooglin, aplica esta habilidad
		if(terreno.isRompible()&&(terreno.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteAbajo())==
			Constants.ValorComparador.IGUAL)) {
				Vida vida = terreno.getVida();
		    	
				if(vida.hayVida())
		    		vida.sacarVidas(1);
		    	
		    	if(!vida.hayVida())
		    	((Tierra)terreno).cambiarPorAire(mapa);
		    	
		    		
		}
			
	}

	@Override
	public boolean isConstruible() {
		// TODO Auto-generated method stub
		return false;
	}

	
}
