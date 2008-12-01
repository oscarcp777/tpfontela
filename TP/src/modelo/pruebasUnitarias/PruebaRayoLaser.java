package modelo.pruebasUnitarias;

import junit.framework.TestCase;
import modelo.elementosDelMapa.Aire;
import modelo.elementosDelMapa.Poogling;
import modelo.elementosDelMapa.Terreno;
import modelo.elementosDelMapa.Tierra;
import modelo.habilidadesPooglins.ContenedorHabilidades;
import modelo.mapaDeJuego.Planeta;
import modelo.nivelDeJuego.ColHabilidades;
import modelo.nivelDeJuego.ColPooglins;
import modelo.nivelDeJuego.ColTerreno;
import modelo.nivelDeJuego.InfoNivel;
import modelo.propiedadesDeElementos.Posicion;
import modelo.propiedadesDeElementos.Velocidad;
import modelo.propiedadesDeElementos.Vida;
import modelo.utilitarios.Constants;

public class PruebaRayoLaser extends TestCase {

	private Planeta planeta;
	
	protected void setUp() throws Exception{
		super.setUp();
		Posicion posicionNaveIngreso = new Posicion(0,0); //se posiciona la nave de ingreso
		Posicion posicionNaveEscape = new Posicion(5,3); //se posiciona la nave de escape
		
		/* Se carga el pooglin que va a salir de la nave de entrada */
		ColPooglins colPooglins = new ColPooglins();
		
		Poogling pooglin = new Poogling(new Posicion(0,0),new Vida(5));
		Velocidad velocidadPooglin=new Velocidad();
		velocidadPooglin.setVelocidad(2);
		pooglin.setVelocidad(velocidadPooglin);
		colPooglins.agregarPoogling(pooglin);
		
		/* Se carga la coleccion de terrenos */
		ColTerreno colTerreno = new ColTerreno();
		
		for(int j=0;j<=6;j++){
			Terreno aire = new Aire();
			aire.asignarPosicion(new Posicion(j,0));
			aire.setVida(new Vida(5));
			colTerreno.agregarTerreno(aire);
		}
		
		for(int j=0;j<=6;j++){
			Terreno aire = new Aire();
			aire.asignarPosicion(new Posicion(j,1));
			aire.setVida(new Vida(5));
			colTerreno.agregarTerreno(aire);
		}
		
		
		for(int j=0;j<=6;j++){
			Terreno aire = new Aire();
			aire.asignarPosicion(new Posicion(j,2));
			aire.setVida(new Vida(5));
			colTerreno.agregarTerreno(aire);
		}
		
		
		for(int j=0;j<=6;j++){
			Terreno aire = new Aire();
			aire.asignarPosicion(new Posicion(j,3));
			aire.setVida(new Vida(5));
			colTerreno.agregarTerreno(aire);
		}
		
		for(int j=0;j<=6;j++){
			Terreno tierra = new Tierra();
			tierra.asignarPosicion(new Posicion(j,4));
			tierra.setVida(new Vida(5));
			colTerreno.agregarTerreno(tierra);
		}
			
		Terreno tierra = new Tierra();
		tierra.asignarPosicion(new Posicion(4,3));
		tierra.setVida(new Vida(4));
		colTerreno.agregarTerreno(tierra);
		
		ColHabilidades colHabilidades = new ColHabilidades(ContenedorHabilidades.getInstance().obtenerColeccionHabilidades());
		
		/* Se termino de cargar la coleccion de fabrica de terrenos */
		
		//Se carga la informacion del nivel
		InfoNivel infoNivel = new InfoNivel(posicionNaveIngreso, posicionNaveEscape, colPooglins, colTerreno,colHabilidades);
		
		//Se carga el planeta con esta info de nivel
		planeta = new Planeta(infoNivel);
	}
	
	public void testPooglinConTerreno(){
		ColPooglins colPooglins = this.planeta.obtenerPooglinsNaveIngreso();
				
		Poogling pooglin=colPooglins.obtenerPoogling(0);
		boolean movimientoValido;
		int cantPasos=0;
		
		do{			
			movimientoValido=planeta.moverPooglin(pooglin);
			cantPasos++;
			if(cantPasos==3)
				pooglin.darHabilidad(Constants.NombreHabilidades.RAYO_LASER);
			
		}while(movimientoValido);
		
		colPooglins = planeta.obtenerPooglinsNaveEscape();
		
		assertEquals(false,colPooglins.estaVacia()); //el poogling pudo llegar a la nave de salida, aplicando la habilidad Rayo Laser
	}

}
