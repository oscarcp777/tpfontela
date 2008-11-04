package habilidadesPooglins;

import mapaDeJuego.Mapa;
import movimientoPooglins.Abajo;
import propiedadesDeElementos.Vida;
import utilitarios.Constants;
import elementosDelMapa.Poogling;
import elementosDelMapa.Terreno;
import elementosDelMapa.Tierra;

public class TaladroUltrasonico extends Habilidad {

	public TaladroUltrasonico(){
		estadoHabilidad = new EstadoHabilidad();
		estadoHabilidad.activarHabilidad();
	}

	@Override
	public void aplicarApooglin(Mapa mapa, Poogling poogling, Terreno terreno) {
		// TODO Auto-generated method stub
	/*se pueden romper hasta 5 bloques de profundidad , recordar que
	 * la tierra se rompe con 4 vueltas de torpedo, y que la roca no se puede romper	
	 * 
	 */
	}

	@Override
	public String getNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreHabilidades.TALADRO_ULTRASONICO;
	}

	@Override
	public void aplicarAterreno(Mapa mapa, Terreno terreno, Poogling poogling) {
			
		//Si el terreno esta por debajo del pooglin, aplica esta habilidad
		if((terreno.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteAbajo())==
			Constants.ValorComparador.IGUAL)&& (terreno.obtenerNombre().compareToIgnoreCase(Constants.NombreTerrenos.TIERRA)==
			Constants.ValorComparador.IGUAL)) {
				poogling.redireccionar(Abajo.getInstance());
				Vida vida = terreno.getVida();
		    	if(vida.hayVida()){
		    		vida.sacarVidas(1);
		    		poogling.invalidarMovimiento(true);
		    	}else{
		    		((Tierra)terreno).cambiarPorAire(mapa);
		    		poogling.invalidarMovimiento(false);
		    	}
		}
	}

	
}
