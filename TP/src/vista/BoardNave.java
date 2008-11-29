package vista;

import modelo.mapaDeJuego.Mapa;

public class BoardNave {

	private BoardGame boardGame;
	
	public BoardNave (BoardGame g){
		this.boardGame = g;
	}
	
	public void pintarNave (Mapa mapa){
		
		boardGame.getGraphics().drawImage(mapa.getNaveIngreso().getImage(),mapa.getNaveIngreso().obtenerPosicion().getPosicionX()*30,mapa.getNaveIngreso().obtenerPosicion().getPosicionY()*30,40,40,this.boardGame);
		boardGame.getGraphics().drawImage(mapa.getNaveEscape().getImage(),mapa.getNaveEscape().obtenerPosicion().getPosicionX()*30 + 20,mapa.getNaveEscape().obtenerPosicion().getPosicionY()*27 + 20,40,40,this.boardGame);
	}
}
