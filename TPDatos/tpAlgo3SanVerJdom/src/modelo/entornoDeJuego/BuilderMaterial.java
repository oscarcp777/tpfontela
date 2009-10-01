package modelo.entornoDeJuego;

import modelo.constantes.Constantes;
/**
 * Clase: Builder Material
 * Utilidad: Clase utilizada para la construccion de los distintos tipos de
 * material que tendra el terreno del juego.
 * Posee todos sus metodos estaticos, ya que no necesitamos instanciar esta clase, solo 
 * necesitamos sus servicios.
 * */


public class BuilderMaterial {
	
	public static MaterialDeTerreno crearPiso(){
		//(boolean esRompible, boolean esCaminable, boolean esVacio, boolean esMortal, int tipoDeMaterial)
		MaterialDeTerreno material = new MaterialDeTerreno(true, true, false, false, Constantes.PISO);
		return material;
	}
	
	public static MaterialDeTerreno crearPiedra(){
		//(boolean esRompible, boolean esCaminable, boolean esVacio, boolean esMortal, int tipoDeMaterial)
		MaterialDeTerreno material = new MaterialDeTerreno(false, true, false, false, Constantes.PISO_PIEDRA);
		return material;
	}
	
	public static MaterialDeTerreno crearParedPiedra(){
		//(boolean esRompible, boolean esCaminable, boolean esVacio, boolean esMortal, int tipoDeMaterial)
		MaterialDeTerreno material = new MaterialDeTerreno(false, false, false, false, Constantes.PARED_PIEDRA);
		return material;
	}
	
	public static MaterialDeTerreno crearPared(){
		//(boolean esRompible, boolean esCaminable, boolean esVacio, boolean esMortal, int tipoDeMaterial)
		MaterialDeTerreno material = new MaterialDeTerreno(true, false, false, false, Constantes.PARED);
		return material;
	}
	public static MaterialDeTerreno crearHielo(){
		//(boolean esRompible, boolean esCaminable, boolean esVacio, boolean esMortal, int tipoDeMaterial)
		MaterialDeTerreno material = new MaterialDeTerreno(true, true, false, false, Constantes.HIELO);
		return material;
	}
	
	public static MaterialDeTerreno crearVacio(){
		//(boolean esRompible, boolean esCaminable, boolean esVacio, boolean esMortal, int tipoDeMaterial)
		MaterialDeTerreno material = new MaterialDeTerreno(false, true, true, false, Constantes.VACIO);
		return material;
	}
	
	public static MaterialDeTerreno crearFuego(){
		//(boolean esRompible, boolean esCaminable, boolean esVacio, boolean esMortal, int tipoDeMaterial)
		MaterialDeTerreno material = new MaterialDeTerreno(false, true, false, true, Constantes.FUEGO);
		return material;
	}
	
	public static MaterialDeTerreno crearPooglinCongelado(){
		//(boolean esRompible, boolean esCaminable, boolean esVacio, boolean esMortal, int tipoDeMaterial)
		MaterialDeTerreno material = new MaterialDeTerreno(false, false, false, false, Constantes.POOGLINS_CONGELADO);
		return material;
	}
	public  static MaterialDeTerreno crearTunelElectromagneticoDerecha(){
		MaterialDeTerreno material = new MaterialDeTerreno(true, true, false, false, Constantes.TUNEL_DERECHA);
		return material;
	}
	public static MaterialDeTerreno crearTunelElectromagneticoIzquierda(){
		//(boolean esRompible, boolean esCaminable, boolean esVacio, boolean esMortal, int tipoDeMaterial)
		MaterialDeTerreno material = new MaterialDeTerreno(true, true, false, false, Constantes.TUNEL_IZQUIERDA);
		return material;
	}
	
	public static MaterialDeTerreno crearTaladroUltrasonico(){
	MaterialDeTerreno material= new MaterialDeTerreno(true, true, true,false,Constantes.TALADRO);
	return material;
	}
	
	public static MaterialDeTerreno crearAgujeroNegro(){
		//(boolean esRompible, boolean esCaminable, boolean esVacio, boolean esMortal, int tipoDeMaterial)
		MaterialDeTerreno material = new MaterialDeTerreno(false, false, false, true, Constantes.AGUJERO_NEGRO);
		return material;
	}
	
	
	public static MaterialDeTerreno puertaEntrada(){
		//(booloean esPuertaDeEntrada, boolean esPuertaDeSalida int tipoDeMaterial)
		MaterialDeTerreno material = new MaterialDeTerreno(true, false, Constantes.PUERTA_ENTRADA);
		return material;
	}
	
	public static MaterialDeTerreno puertaSalida(){
		//(booloean esPuertaDeEntrada, boolean esPuertaDeSalida int tipoDeMaterial)
		MaterialDeTerreno material = new MaterialDeTerreno(false, true, Constantes.PUERTA_SALIDA);
		return material;
	}
	
	public static MaterialDeTerreno crearRampaDerecha(){
		//(boolean esRompible, boolean esCaminable, boolean esVacio, boolean esMortal, int tipoDeMaterial)
		MaterialDeTerreno material = new MaterialDeTerreno(true, true, false, false, Constantes.RAMPA_DERECHA);
		return material;
	}
	
	public static MaterialDeTerreno crearRampaIzquierda(){
		//(boolean esRompible, boolean esCaminable, boolean esVacio, boolean esMortal, int tipoDeMaterial)
		MaterialDeTerreno material = new MaterialDeTerreno(true, true, false, false, Constantes.RAMPA_IZQUIERDA);
		return material;
	}
	

}
