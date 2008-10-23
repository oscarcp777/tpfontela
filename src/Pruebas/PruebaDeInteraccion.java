package Pruebas;

import junit.framework.TestCase;


import Otros.ColPooglins;
import Otros.ColTerreno;
import Otros.DimensionTerreno;
import Otros.InfoNivel;
import Otros.Planeta;
import Otros.Poogling;
import TipoPosicion.Posicion;
import TipoPosicion.Velocidad;
import TipoTerrenos.Aire;
import TipoTerrenos.Hielo;
import TipoTerrenos.Roca;
import TipoTerrenos.Terreno;
import TipoTerrenos.Tierra;



public class PruebaDeInteraccion extends TestCase{
	
	private Planeta planeta;
		
	protected void setUp() throws Exception{
		super.setUp();
		Posicion posicionNaveIngreso = new Posicion(0,0); //se posiciona la nave de ingreso
		Posicion posicionNaveEscape = new Posicion(1,5); //se posiciona la nave de escape
		DimensionTerreno dimensionTerreno = new DimensionTerreno(); //se da la dimension para la matriz del terreno
		dimensionTerreno.setdimX(6);
		dimensionTerreno.setdimY(6);
		/* Se carga el pooglin que va a salir de la nave de entrada */
		ColPooglins colPooglins = new ColPooglins();
		
		Poogling pooglin = new Poogling(new Posicion(0,0));
		Velocidad velocidadPooglin=new Velocidad();
		velocidadPooglin.setVelocidad(2);
		pooglin.setVelocidad(velocidadPooglin);
		colPooglins.agregarPooglin(pooglin);
		
		/* Se carga la coleccion de terrenos */
		ColTerreno colTerreno = new ColTerreno();
		
		for(int j=0;j<=6;j++){
			Terreno aireAux = new Aire();
			aireAux.asignarPosicion(new Posicion(j,0));
			colTerreno.agregarTerreno(aireAux);
		}
		
		for(int j=0;j<=6;j++){
			Terreno aireAux1 = new Aire();
			aireAux1.asignarPosicion(new Posicion(j,1));
			colTerreno.agregarTerreno(aireAux1);
		}
		
		for(int j=0;j<=2;j++){
			Terreno tierraAux = new Tierra();
			tierraAux.asignarPosicion(new Posicion(j,2));
			colTerreno.agregarTerreno(tierraAux);
		}
			
		Terreno tierra = new Tierra();
		tierra.asignarPosicion(new Posicion(5,2));
		colTerreno.agregarTerreno(tierra);
		
		Terreno hielo = new Hielo();
		hielo.asignarPosicion(new Posicion(3,2));
		colTerreno.agregarTerreno(hielo);
		
		Terreno roca = new Roca();
		roca.asignarPosicion(new Posicion(4,2));
		colTerreno.agregarTerreno(roca);
				
		/* Se termino de cargar la coleccion de fabrica de terrenos */
		
		//Se carga la información del nivel
		InfoNivel infoNivel = new InfoNivel(posicionNaveIngreso, posicionNaveEscape, colPooglins, colTerreno, dimensionTerreno);
		
		//Se carga el planeta con esta info de nivel
		planeta = new Planeta(infoNivel);
	}
	
	
	public void testPooglinConTerreno(){
		ColPooglins colPooglins = this.planeta.obtenerPooglins();
		int cantidadDePasos = 0;
		
		Poogling pooglin=colPooglins.obtenerPooglin(0);
		
		while(cantidadDePasos<=5){
			planeta.moverPooglin(pooglin);
			cantidadDePasos++;
		}
		
		assertEquals(true,colPooglins.estaVacia());
	}
	

}
