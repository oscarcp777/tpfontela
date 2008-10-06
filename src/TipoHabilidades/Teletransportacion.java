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
		
		public void Teletransportar(){
			
			this.poogling=poogling.asignarPosicion([(posicion.getPosicionY)+20][posicion.getPosicionX]);
		}
		
}
