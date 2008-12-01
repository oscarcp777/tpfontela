package modelo.pruebasUnitarias;

import junit.framework.TestCase;
import modelo.elementosDelMapa.Aire;
import modelo.elementosDelMapa.Poogling;
import modelo.elementosDelMapa.Roca;
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

public class PruebaCongelamientoDelPooglin extends TestCase{

private Planeta planeta;
	
	protected void setUp() throws Exception{
		super.setUp();
		Posicion posicionNaveIngreso = new Posicion(0,0); //se posiciona la nave de ingreso
		Posicion posicionNaveEscape = new Posicion(5,2); //se posiciona la nave de escape
	
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
			Terreno aireAux = new Aire();
			aireAux.asignarPosicion(new Posicion(j,0));
			aireAux.setVida(new Vida(5));
			colTerreno.agregarTerreno(aireAux);
		}
		
		for(int j=0;j<=6;j++){
			Terreno aireAux = new Aire();
			aireAux.asignarPosicion(new Posicion(j,1));
			aireAux.setVida(new Vida(5));
			colTerreno.agregarTerreno(aireAux);
		}
		
		for(int j=0;j<=6;j++){
			Terreno aireAux = new Aire();
			aireAux.asignarPosicion(new Posicion(j,2));
			aireAux.setVida(new Vida(5));
			colTerreno.agregarTerreno(aireAux);
		}
		
		for(int j=0;j<=2;j++){
			Terreno tierraAux = new Tierra();
			tierraAux.asignarPosicion(new Posicion(j,3));
			tierraAux.setVida(new Vida(5));
			colTerreno.agregarTerreno(tierraAux);
		}
			
		Terreno tierra = new Tierra();
		tierra.asignarPosicion(new Posicion(5,3));
		tierra.setVida(new Vida(5));
		colTerreno.agregarTerreno(tierra);
		
		Terreno tierraAux = new Tierra();
		tierraAux.asignarPosicion(new Posicion(3,3));
		tierraAux.setVida(new Vida(5));
		colTerreno.agregarTerreno(tierraAux);
		
		Terreno roca = new Roca();
		roca.asignarPosicion(new Posicion(4,3));
		roca.setVida(new Vida(5));
		colTerreno.agregarTerreno(roca);
		
		ColHabilidades colHabilidades = new ColHabilidades(ContenedorHabilidades.getInstance().obtenerColeccionHabilidades());
		
		/* Se termino de cargar la coleccion de fabrica de terrenos */
		
		//Se carga la informacion del nivel
		InfoNivel infoNivel = new InfoNivel(posicionNaveIngreso, posicionNaveEscape, colPooglins, colTerreno,colHabilidades);
		
		//Se carga el planeta con esta info de nivel
		planeta = new Planeta(infoNivel);
	}
	
	public void testPooglinCongelado(){
		ColPooglins colPooglins = this.planeta.obtenerPooglinsNaveIngreso();
		Terreno terreno=null;
		Poogling pooglin=colPooglins.obtenerPoogling(0);
		boolean movimientoValido;
		int cantPasos=0;
		
		do{			
			terreno = planeta.obtenerMapaDeJuego().obtenerTerreno(pooglin.obtenerPosicion());
			movimientoValido=planeta.moverPooglin(pooglin);
			cantPasos++;
			if(cantPasos==3)
				pooglin.darHabilidad(Constants.NombreHabilidades.CONGELAMIENTO);
			
		}while(movimientoValido);
				
		assertEquals(pooglin.isConVida(),false); //el pooglin no tiene vida porque se congelo
				
		assertNotSame(planeta.obtenerMapaDeJuego().obtenerTerreno(pooglin.obtenerPosicion()),terreno); //Hielo se transformo en Aire
	}
		
}
