package habilidadesPooglins;

import elementosDelMapa.Poogling;
import elementosDelMapa.Terreno;

public class Teletransportacion extends Habilidad{
		
		private Poogling poogling;
		private Terreno terreno;
		
		public Teletransportacion(Poogling poogling,Terreno terreno){
			this.poogling=poogling;
			this.terreno=terreno;
		}
		
		public Poogling Teletransportar(){
		//	return this.poogling.asignarPosicion([(posicion.getPosicionY)+20][posicion.getPosicionX]);
		return null;
		}

		@Override
		public void destruirTerreno(Terreno terreno) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void aplicar(Poogling poogling) {
			// TODO Auto-generated method stub
			/*el pooglin adelanta 20 pasos (posiciones) 
			 * ya sea de derecha o izquierda (dependiendo de
			 * su direccion)
			 */
		}

		
		
}
