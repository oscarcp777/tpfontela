package vista;

import java.util.Iterator;
import java.util.Set;

import modelo.mapaDeJuego.Mapa;
import modelo.propiedadesDeElementos.Posicion;


public class BoardTerreno {

private BoardGame boardGame;
	
	public BoardTerreno (BoardGame g){
		this.boardGame = g;
	}
	
	public void pintarTerreno (Mapa mapa){
		
		Set keys=mapa.obtenerPosicionesTerrenos();
		
		for(Iterator key = keys.iterator();key.hasNext();){
			Posicion posicion = (Posicion)key.next();
					
			boardGame.getGraphics().drawImage(mapa.obtenerTerreno(posicion).getImage(),posicion.getPosicionX()*30,posicion.getPosicionY()*30,30,30,this.boardGame);
		}
	}
}
