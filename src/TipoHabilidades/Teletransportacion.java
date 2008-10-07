package TipoHabilidades;

import Otros.Poogling;
import TipoTerrenos.Terreno;

public class Teletransportacion extends Habilidad{
		
		private Poogling poogling;
		private Terreno terreno;
		
		public Teletransportacion(Poogling poogling,Terreno terreno){
			this.poogling=poogling;
			this.terreno=terreno;
		}
		
		public Poogling Teletransportar(){
			return this.poogling.asignarPosicion([(posicion.getPosicionY)+20][posicion.getPosicionX]);
		}

		@Override
		public void destruirTerreno(Terreno terreno) {
			// TODO Auto-generated method stub
			
		}

		
		
}
