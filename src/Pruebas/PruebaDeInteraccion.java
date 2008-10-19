package Pruebas;

import java.util.List;

import junit.framework.Assert;

import org.junit.Test;

import Otros.Poogling;
import TipoPosicion.Mapa;
import TipoPosicion.Posicion;
import TipoTerrenos.Aire;
import TipoTerrenos.Terreno;
import TipoTerrenos.Tierra;

public class PruebaDeInteraccion {
	
	
	@Test
	public void testCrear(){
		
		Mapa mapa = new Mapa();
		mapa.cargarTerreno();
		
		List pooglings = mapa.getNave().getPooglings();
		
		Poogling poogling = (Poogling)pooglings.get(0);
		
		Terreno[][] terrenoAux = mapa.getTerreno();
		poogling.obtenerPosicion();
		
		
		Posicion posicion = new Posicion(poogling.obtenerPosicion().getPosicionX(),poogling.obtenerPosicion().getPosicionY());
		poogling.getDireccion().siguientePosicion(posicion);
		Terreno terreno=new Tierra();
		terreno.asignarPosicion(new Posicion(5,3));
		poogling.mover(/*terreno[posicion.getPosicionX()][posicion.getPosicionY()]*/terreno);
			
		Assert.assertEquals(posicion.getPosicionX(),poogling.obtenerPosicion().getPosicionX());
		Assert.assertEquals(posicion.getPosicionY(),poogling.obtenerPosicion().getPosicionY());
	}
	

}
