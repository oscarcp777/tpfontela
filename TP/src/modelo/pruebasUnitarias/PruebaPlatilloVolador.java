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

public class PruebaPlatilloVolador extends TestCase{

private Planeta planeta;
	
	protected void setUp() throws Exception{
		super.setUp();
		Posicion posicionNaveIngreso = new Posicion(0,0); //se posiciona la nave de ingreso
		Posicion posicionNaveEscape = new Posicion(5,5); //se posiciona la nave de escape
		ColPooglins colPooglins = new ColPooglins();
		
		/* Se carga el pooglin que va a salir de la nave de entrada */
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
		
		for(int j=0;j<=6;j++){
			Terreno aireAux1 = new Aire();
			aireAux1.asignarPosicion(new Posicion(j,2));
			aireAux1.setVida(new Vida(5));
			colTerreno.agregarTerreno(aireAux1);
		}
		
		for(int j=0;j<=6;j++){
			Terreno aireAux1 = new Aire();
			aireAux1.asignarPosicion(new Posicion(j,3));
			aireAux1.setVida(new Vida(5));
			colTerreno.agregarTerreno(aireAux1);
		}
		
		for(int j=0;j<=6;j++){
			Terreno aireAux1 = new Aire();
			aireAux1.asignarPosicion(new Posicion(j,4));
			aireAux1.setVida(new Vida(5));
			colTerreno.agregarTerreno(aireAux1);
		}
		
		for(int j=0;j<=6;j++){
			Terreno aireAux1 = new Aire();
			aireAux1.asignarPosicion(new Posicion(j,5));
			aireAux1.setVida(new Vida(5));
			colTerreno.agregarTerreno(aireAux1);
		}
		
		for(int j=0;j<=6;j++){
			Terreno tierra = new Tierra();
			tierra.asignarPosicion(new Posicion(j,6));
			tierra.setVida(new Vida(5));
			colTerreno.agregarTerreno(tierra);
		}
			
		
         ColHabilidades colHabilidades = new ColHabilidades(ContenedorHabilidades.getInstance().obtenerColeccionHabilidades());
		
		/* Se termino de cargar la coleccion de fabrica de terrenos */
		
		//Se carga la informacion del nivel
		InfoNivel infoNivel = new InfoNivel(posicionNaveIngreso, posicionNaveEscape, colPooglins, colTerreno,colHabilidades);
		//Se carga el planeta con esta info de nivel
		planeta = new Planeta(infoNivel);
	}
	
	public void testPooglinSalvatajePlatilloVolador(){
		ColPooglins colPooglins = this.planeta.obtenerPooglinsNaveIngreso();
				
		Poogling pooglin=colPooglins.obtenerPoogling(0);
		
		boolean movimientoValido;
		
		pooglin.darHabilidad(Constants.NombreHabilidades.PLATILLO_VOLADOR);
		
		do{			
			movimientoValido=planeta.moverPooglin(pooglin);
					
		}while(movimientoValido);
		
		assertEquals(pooglin.isConVida(),true); //se le aplico el platillo volador y se salvo el pooglin
		
		colPooglins = planeta.obtenerPooglinsNaveEscape();
			
		assertEquals(false,colPooglins.estaVacia()); //llego a la nave de salida gracias a la habilidad platillo volador
	}
	
}
