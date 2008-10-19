package TipoPosicion;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import Otros.Nave;
import Otros.Poogling;
import TipoTerrenos.Aire;
import TipoTerrenos.Terreno;
import TipoTerrenos.Tierra;
import Utilidades.Constants;


public class Mapa {
	private Terreno[][] terreno;
	private Nave nave;
	
	public Mapa(){
		terreno = new Terreno[Constants.TamanioMatriz.MAX][Constants.TamanioMatriz.MAX];
	    nave = new Nave ();
	    nave.asignarPosicion(new Posicion(5,10));
	    List pooglins = new ArrayList();
	    Poogling poogling = new Poogling(new Posicion(5,4));
	    pooglins.add(poogling);
	    nave.setPooglings(pooglins);
	
	}
	
	public Nave getNave(){
		return nave;
	}
	
	public Terreno[][] getTerreno(){
		return terreno;
	}
	
	public void cargarTerreno(){
		for (int x=0; x<=10;x++)
			for(int y=0; y<=4;y++){
		Terreno terrenoAux = new Aire();
		terrenoAux.asignarPosicion(new Posicion(x,y));
			}
		
		for (int x=0; x<=9;x++)
			for(int y=5; y<6;y++){
		Terreno terrenoAux = new Aire();
		terrenoAux.asignarPosicion(new Posicion(x,y));
			}
		
		
		
		for (int x=0; x<=10;x++)
			for(int y=6; y<=10;y++){
		Terreno terrenoAux = new Tierra();
		terrenoAux.asignarPosicion(new Posicion(x,y));
			}
		
	}
	
	

}
