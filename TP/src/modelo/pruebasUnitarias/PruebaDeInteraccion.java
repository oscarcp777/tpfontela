package modelo.pruebasUnitarias;

import junit.framework.TestCase;
import modelo.elementosDelMapa.AgujeroNegro;
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

public class PruebaDeInteraccion extends TestCase{
	
	private Planeta planeta;
		
	protected void setUp() throws Exception{
		super.setUp();
		Posicion posicionNaveIngreso = new Posicion(0,0); //se posiciona la nave de ingreso
		Posicion posicionNaveEscape = new Posicion(5,1); //se posiciona la nave de escape
		
			
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
			Terreno aireAux1 = new Aire();
			aireAux1.asignarPosicion(new Posicion(j,1));
			aireAux1.setVida(new Vida(5));
			colTerreno.agregarTerreno(aireAux1);
		}
		
		for(int j=0;j<=2;j++){
			Terreno tierraAux = new Tierra();
			tierraAux.asignarPosicion(new Posicion(j,2));
			tierraAux.setVida(new Vida(5));
			colTerreno.agregarTerreno(tierraAux);
		}
			
		Terreno tierra = new Tierra();
		tierra.asignarPosicion(new Posicion(5,2));
		tierra.setVida(new Vida(5));
		colTerreno.agregarTerreno(tierra);
		
		Terreno agujeroNegro = new AgujeroNegro();
		agujeroNegro.asignarPosicion(new Posicion(3,2));
		agujeroNegro.setVida(new Vida(5));
		colTerreno.agregarTerreno(agujeroNegro);
		
		Terreno roca = new Roca();
		roca.asignarPosicion(new Posicion(4,2));
		roca.setVida(new Vida(5));
		colTerreno.agregarTerreno(roca);
				
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
		
		do{			
			movimientoValido=planeta.moverPooglin(pooglin);
		}while(movimientoValido);
		
		assertEquals(true,colPooglins.estaVacia());
		
		colPooglins = planeta.obtenerPooglinsNaveEscape();
		
		assertEquals(true,colPooglins.estaVacia()); //llego a la nave de salida
	}
	

}
