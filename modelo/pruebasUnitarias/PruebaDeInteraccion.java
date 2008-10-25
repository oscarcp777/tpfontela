package pruebasUnitarias;

import mapaDeJuego.Planeta;
import nivelDeJuego.ColPooglins;
import nivelDeJuego.ColTerreno;
import nivelDeJuego.InfoNivel;
import elementosDelMapa.Aire;
import elementosDelMapa.Hielo;
import elementosDelMapa.Poogling;
import elementosDelMapa.Roca;
import elementosDelMapa.Terreno;
import elementosDelMapa.Tierra;
import propiedadesDeElementos.Posicion;
import propiedadesDeElementos.Velocidad;
import junit.framework.TestCase;

public class PruebaDeInteraccion extends TestCase{
	
	private Planeta planeta;
		
	protected void setUp() throws Exception{
		super.setUp();
		Posicion posicionNaveIngreso = new Posicion(0,0); //se posiciona la nave de ingreso
		Posicion posicionNaveEscape = new Posicion(5,1); //se posiciona la nave de escape
				
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
		InfoNivel infoNivel = new InfoNivel(posicionNaveIngreso, posicionNaveEscape, colPooglins, colTerreno);
		
		//Se carga el planeta con esta info de nivel
		planeta = new Planeta(infoNivel);
	}
	
	
	public void testPooglinConTerreno(){
		ColPooglins colPooglins = this.planeta.obtenerPooglinsNaveIngreso();
				
		Poogling pooglin=colPooglins.obtenerPooglin(0);
		boolean movimientoValido;
		
		do{			
			movimientoValido=planeta.moverPooglin(pooglin);
		}while(movimientoValido);
		
		assertEquals(true,colPooglins.estaVacia());
		
		colPooglins = planeta.obtenerPooglinsNaveEscape();
		
		assertEquals(false,colPooglins.estaVacia());
	}
	

}
