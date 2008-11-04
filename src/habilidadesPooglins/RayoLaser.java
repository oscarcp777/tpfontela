package habilidadesPooglins;
import mapaDeJuego.Mapa;
import propiedadesDeElementos.Vida;
import utilitarios.Constants;
import elementosDelMapa.Aire;
import elementosDelMapa.Poogling;
import elementosDelMapa.Terreno;
import elementosDelMapa.Tierra;

public class RayoLaser extends Habilidad{


	public RayoLaser() {
		estadoHabilidad = new EstadoHabilidad();
		estadoHabilidad.activarHabilidad();
	}

	
	@Override
	public void aplicarApooglin(Mapa mapa, Poogling poogling, Terreno terreno) {
		// TODO Auto-generated method stub
		/*si el pooglin tiene tierra en alguna de sus posiciones
		 *laterales puede "romperla" (reemplazarla por aire), tener en cuenta que 
		 *la tierra se pouede destruir con 4 disparos (o vuelta de torpedo)
		 *(a mi criterio tierra deberia de tener 4 vidas, e ir restandoselas, porque 
		 *puede que ese bloque sea disparado por distintos pooglin) 
		 */
	}

	@Override
	public String getNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreHabilidades.RAYO_LASER;
		
	}


	@Override
	public void aplicarAterreno(Mapa mapa, Terreno terreno, Poogling poogling) {
		//esta habilidad solo se aplica si el pooglin tiene tierra a la izquierda o a la derecha
		if((terreno.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteDerecha())==
			Constants.ValorComparador.IGUAL)||(terreno.obtenerPosicion().compareTo(poogling.obtenerPosicion().obtenerPosicionSiguienteIzquierda())==
				Constants.ValorComparador.IGUAL)){

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

