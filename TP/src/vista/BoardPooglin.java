package vista;

import java.util.Iterator;

import modelo.elementosDelMapa.Poogling;
import modelo.mapaDeJuego.Mapa;
import modelo.nivelDeJuego.ColPooglins;

public class BoardPooglin{

	private BoardGame boardGame;
	
	public BoardPooglin (BoardGame boardGame){

		this.boardGame = boardGame;
	}
	
	public void pintarPooglin (Mapa mapa){
		
		ColPooglins colPooglins = mapa.obtenerPooglinsNaveIngreso();
				
		for(Iterator it = colPooglins.iterator();it.hasNext();){
			Poogling poogling = (Poogling)it.next();
			
			if(poogling.isConVida()&&!mapa.llegoPooglinANaveEscape(poogling)){//si el pooglin tiene vida y no llego a la nave de salida lo dibujo en la pantalla
				boardGame.getGraphics().drawImage(poogling.getImage(), poogling.obtenerPosicion().getPosicionX()*30, poogling.obtenerPosicion().getPosicionY()*30 - 5, 
												  35, 35, boardGame);
			}
		}
	}
}
