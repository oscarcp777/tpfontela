package modelo.pruebasUnitarias;

import modelo.FabricaHabilidades.FabricaCongelamiento;
import modelo.FabricaHabilidades.FabricaPlatilloVolador;
import modelo.FabricaHabilidades.FabricaRayoLaser;
import modelo.FabricaHabilidades.FabricaTaladroUltrasonico;
import modelo.FabricaHabilidades.FabricaTeletransportacion;
import modelo.FabricaHabilidades.FabricaTunelElectromagnetico;
import modelo.elementosDelMapa.AgujeroNegro;
import modelo.elementosDelMapa.Aire;
import modelo.elementosDelMapa.Poogling;
import modelo.elementosDelMapa.Roca;
import modelo.elementosDelMapa.Terreno;
import modelo.elementosDelMapa.Tierra;
import modelo.mapaDeJuego.Planeta;
import modelo.nivelDeJuego.ColFabricaHabilidades;
import modelo.nivelDeJuego.ColPooglins;
import modelo.nivelDeJuego.ColTerreno;
import modelo.nivelDeJuego.InfoNivel;
import modelo.propiedadesDeElementos.Posicion;
import modelo.propiedadesDeElementos.Velocidad;
import modelo.propiedadesDeElementos.Vida;
import modelo.utilitarios.Constants;
import junit.framework.TestCase;

public class PruebaPooglinAlVacio extends TestCase{
	
	private Planeta planeta;
	
	protected void setUp() throws Exception{
		super.setUp();
		Posicion posicionNaveIngreso = new Posicion(0,0); //se posiciona la nave de ingreso
		Posicion posicionNaveEscape = new Posicion(5,1); //se posiciona la nave de escape
				
		/* Se carga el pooglin que va a salir de la nave de entrada */
		ColPooglins colPooglins = new ColPooglins();
		ColFabricaHabilidades colFabrica = new ColFabricaHabilidades();
		colFabrica.agregarFabrica(new FabricaPlatilloVolador());
		colFabrica.agregarFabrica(new FabricaRayoLaser());
		colFabrica.agregarFabrica(new FabricaCongelamiento());
		colFabrica.agregarFabrica(new FabricaTaladroUltrasonico());
		colFabrica.agregarFabrica(new FabricaTeletransportacion());
		colFabrica.agregarFabrica(new FabricaTunelElectromagnetico());
		
		Poogling pooglin = new Poogling(new Posicion(0,0),new Vida(5));
		Velocidad velocidadPooglin=new Velocidad();
		velocidadPooglin.setVelocidad(2);
		pooglin.setVelocidad(velocidadPooglin);
		colPooglins.agregarPooglin(pooglin);
		
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
			Terreno aireAux1 = new Aire();
			aireAux1.asignarPosicion(new Posicion(j,6));
			aireAux1.setVida(new Vida(5));
			colTerreno.agregarTerreno(aireAux1);
		}
			
		Terreno tierra = new Tierra();
		tierra.asignarPosicion(new Posicion(0,6));
		tierra.setVida(new Vida(5));
		colTerreno.agregarTerreno(tierra);
		
		Terreno tierraAux = new Tierra();
		tierraAux.asignarPosicion(new Posicion(1,6));
		tierraAux.setVida(new Vida(5));
		colTerreno.agregarTerreno(tierraAux);
		
		Terreno tierraAux2 = new Tierra();
		tierraAux2.asignarPosicion(new Posicion(2,6));
		tierraAux2.setVida(new Vida(5));
		colTerreno.agregarTerreno(tierraAux2);
		
		Terreno tierraAux3 = new Tierra();
		tierraAux3.asignarPosicion(new Posicion(3,6));
		tierraAux3.setVida(new Vida(5));
		colTerreno.agregarTerreno(tierraAux3);
		
		Terreno tierraAux4 = new Tierra();
		tierraAux4.asignarPosicion(new Posicion(4,6));
		tierraAux4.setVida(new Vida(5));
		colTerreno.agregarTerreno(tierraAux4);
		
		Terreno roca = new Roca();
		roca.asignarPosicion(new Posicion(3,5));
		roca.setVida(new Vida(5));
		colTerreno.agregarTerreno(roca);
		
		Terreno rocaAux = new Roca();
		rocaAux.asignarPosicion(new Posicion(-1,5));
		rocaAux.setVida(new Vida(5));
		colTerreno.agregarTerreno(rocaAux);
				
		/* Se termino de cargar la coleccion de fabrica de terrenos */
		
		//Se carga la informacion del nivel
		InfoNivel infoNivel = new InfoNivel(posicionNaveIngreso, posicionNaveEscape, colPooglins, colTerreno,colFabrica);
		
		//Se carga el planeta con esta info de nivel
		planeta = new Planeta(infoNivel);
	}
	
	public void testPooglinAlVacio(){
		ColPooglins colPooglins = this.planeta.obtenerPooglinsNaveIngreso();
				
		Poogling pooglin=colPooglins.obtenerPooglin(0);
		boolean movimientoValido;
		
		do{			
			movimientoValido=planeta.moverPooglin(pooglin);
		}while(movimientoValido);
		
		assertEquals(true,colPooglins.estaVacia());
		
		colPooglins = planeta.obtenerPooglinsNaveEscape();
		
		assertEquals(true,colPooglins.estaVacia());
	}
	

}
