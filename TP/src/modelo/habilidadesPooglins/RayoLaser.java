package modelo.habilidadesPooglins;
import modelo.elementosDelMapa.Aire;
import modelo.elementosDelMapa.Poogling;
import modelo.elementosDelMapa.Terreno;
import modelo.elementosDelMapa.Tierra;
import modelo.mapaDeJuego.Mapa;
import modelo.propiedadesDeElementos.Vida;
import modelo.utilitarios.Constants;

public class RayoLaser extends Habilidad{


	public RayoLaser() {
		estadoHabilidad = new EstadoHabilidad();
		estadoHabilidad.activarHabilidad();
	}

	
	/*
	 * En este metodo se pregunta si a los costados hay tierra (Es rompible), en caso verdadero el pooglin se quedara quieto
	 * en esa posicion (quieto en posicion) hasta que se destruya ese terreno (libre para moverse).
	 * 
	 * (non-Javadoc)
	 * @see modelo.habilidadesPooglins.Habilidad#aplicarApooglin(modelo.mapaDeJuego.Mapa, modelo.elementosDelMapa.Poogling, modelo.elementosDelMapa.Terreno)
	 */
	@Override
	public void aplicarApooglin(Mapa mapa, Poogling poogling, Terreno terreno) {
		// TODO Auto-generated method stub
		/*si el pooglin tiene tierra en alguna de sus posiciones
		 *laterales puede "romperla" (reemplazarla por aire), tener en cuenta que 
		 *la tierra se pouede destruir con 4 disparos (o vuelta de torpedo)
		 *(a mi criterio tierra deberia de tener 4 vidas, e ir restandoselas, porque 
		 *puede que ese bloque sea disparado por distintos pooglin) 
		 */
		if(terreno.isRompible()&&(((terreno.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteDerecha())==
			Constants.ValorComparador.IGUAL)||(terreno.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteIzquierda())==
				Constants.ValorComparador.IGUAL)))){
			
			Vida vida = terreno.getVida();
			
			if(vida.hayVida())
				poogling.invalidarMovimiento(true);
			
			if(!vida.hayVida()) //no puede ser un else if porque sino cuando sale del metodo y destruyo el terreno queda seteado el poogling con movimiento false.
				poogling.invalidarMovimiento(false); 
		
		}
	}


	/*
	 * En este metodo se pregunta si a los costados hay tierra, si es correcto se aplicara el rayo sobre este terreno hasta dejarlo sin vida.
	 * Una vez que el terreno no tenga vida se cambiara el mismo por aire.
	 *  
	 * (non-Javadoc)
	 * @see modelo.habilidadesPooglins.Habilidad#aplicarAterreno(modelo.mapaDeJuego.Mapa, modelo.elementosDelMapa.Terreno, modelo.elementosDelMapa.Poogling)
	 */
	@Override
	public void aplicarAterreno(Mapa mapa, Terreno terreno, Poogling poogling) {
	
		if(terreno.isRompible()&&(((terreno.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteDerecha())==
			Constants.ValorComparador.IGUAL)||(terreno.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteIzquierda())==
				Constants.ValorComparador.IGUAL)))){
			
			Vida vida = terreno.getVida();

			if(vida.hayVida())
				vida.sacarVidas(1);
			
			if(!vida.hayVida()) //no puedo poner un else if(!vida.hayVida) porque si en el if anterior le saca la ultima vida que le queda no cambiara dicho terreno por aire
			((Tierra)terreno).cambiarPorAire(mapa);
				
		}

	}

	@Override
	public boolean isConstruible() {
		// TODO Auto-generated method stub
		return false;
	}
}

