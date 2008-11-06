package pruebasUnitarias;

import mapaDeJuego.Planeta;
import nivelDeJuego.ColFabricaHabilidades;
import nivelDeJuego.ColPooglins;
import nivelDeJuego.ColTerreno;
import nivelDeJuego.InfoNivel;
import propiedadesDeElementos.Posicion;
import propiedadesDeElementos.Velocidad;
import propiedadesDeElementos.Vida;
import utilitarios.Constants;
import FabricaHabilidades.FabricaCongelamiento;
import FabricaHabilidades.FabricaPlatilloVolador;
import FabricaHabilidades.FabricaRayoLaser;
import FabricaHabilidades.FabricaTaladroUltrasonico;
import FabricaHabilidades.FabricaTeletransportacion;
import FabricaHabilidades.FabricaTunelElectromagnetico;
import elementosDelMapa.AgujeroNegro;
import elementosDelMapa.Aire;
import elementosDelMapa.Poogling;
import elementosDelMapa.Roca;
import elementosDelMapa.Terreno;
import elementosDelMapa.Tierra;
import junit.framework.TestCase;

public class PruebaTaladroUltrasonico extends TestCase {

	private Planeta planeta;
	
	protected void setUp() throws Exception{
		super.setUp();
		Posicion posicionNaveIngreso = new Posicion(0,0); //se posiciona la nave de ingreso
		Posicion posicionNaveEscape = new Posicion(5,4); //se posiciona la nave de escape
		
		/*Se crean las fabricas de habilidades que tendra el nivel del juego*/
		ColFabricaHabilidades colFabrica = new ColFabricaHabilidades();
		colFabrica.agregarFabrica(new FabricaPlatilloVolador());
		colFabrica.agregarFabrica(new FabricaRayoLaser());
		colFabrica.agregarFabrica(new FabricaCongelamiento());
		colFabrica.agregarFabrica(new FabricaTaladroUltrasonico());
		colFabrica.agregarFabrica(new FabricaTeletransportacion());
		colFabrica.agregarFabrica(new FabricaTunelElectromagnetico());
		
		/* Se carga el pooglin que va a salir de la nave de entrada */
		ColPooglins colPooglins = new ColPooglins();
		
		Poogling pooglin = new Poogling(new Posicion(0,0),new Vida(5));
		Velocidad velocidadPooglin=new Velocidad();
		velocidadPooglin.setVelocidad(2);
		pooglin.setVelocidad(velocidadPooglin);
		colPooglins.agregarPooglin(pooglin);
		
		/* Se carga la coleccion de terrenos */
		ColTerreno colTerreno = new ColTerreno();
		
		for(int j=0;j<=6;j++){
			Terreno aire = new Aire();
			aire.asignarPosicion(new Posicion(j,0));
			colTerreno.agregarTerreno(aire);
		}
		
		for(int j=0;j<=6;j++){
			Terreno aire = new Aire();
			aire.asignarPosicion(new Posicion(j,1));
			colTerreno.agregarTerreno(aire);
		}
		
		
		for(int j=0;j<=6;j++){
			Terreno aire = new Aire();
			aire.asignarPosicion(new Posicion(j,2));
			colTerreno.agregarTerreno(aire);
		}
		
		
		for(int j=0;j<=6;j++){
			Terreno tierra = new Tierra();
			tierra.asignarPosicion(new Posicion(j,3));
			tierra.setVida(new Vida(4));
			colTerreno.agregarTerreno(tierra);
		}
		
	    for(int j=0;j<=6;j++){
			Terreno aire = new Aire();
			aire.asignarPosicion(new Posicion(j,4));
			aire.setVida(new Vida(4));
			colTerreno.agregarTerreno(aire);
		}
				
		for(int j=0;j<=6;j++){
		Terreno roca = new Roca();
		roca.asignarPosicion(new Posicion(j,5));
		roca.setVida(new Vida(4));
		colTerreno.agregarTerreno(roca);
		}
		/* Se termino de cargar la coleccion de fabrica de terrenos */
		
		//Se carga la informacion del nivel
		InfoNivel infoNivel = new InfoNivel(posicionNaveIngreso, posicionNaveEscape, colPooglins, colTerreno,colFabrica);
		
		//Se carga el planeta con esta info de nivel
		planeta = new Planeta(infoNivel);
	}
	
	public void testPooglinConTerreno(){
		ColPooglins colPooglins = this.planeta.obtenerPooglinsNaveIngreso();
				
		Poogling pooglin=colPooglins.obtenerPooglin(0);
		boolean movimientoValido;
		int cantPasos=0;
		
		do{			
			movimientoValido=planeta.moverPooglin(pooglin);
			cantPasos++;
			if(cantPasos==4)
				pooglin.darHabilidad(Constants.NombreHabilidades.TALADRO_ULTRASONICO);
			
		}while(movimientoValido);
		
		assertEquals(true,colPooglins.estaVacia());
		
		colPooglins = planeta.obtenerPooglinsNaveEscape();
		
		assertEquals(false,colPooglins.estaVacia());
	}
	
}
