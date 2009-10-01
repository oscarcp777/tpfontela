package vista.utilitarias;

import modelo.constantes.Constantes;
import vista.componentes.SpriteSimple;

public class CargadorImagenesTerreno {
	/*
	 * SOLO CAMBIE LOS NOMBRES DE LAS IMAGENES A minusculas
	 * */
	public static SpriteSimple crearImagen(int id){
		switch (id) {
		case Constantes.PISO: return new SpriteSimple("piso.png",0,0);
		case Constantes.VACIO: return new SpriteSimple("vacio.png",0,0);
		case Constantes.PARED: return new SpriteSimple("tierra.png",0,0);
		case Constantes.PARED_PIEDRA: return new SpriteSimple("piedra.png",0,0);
		case Constantes.FUEGO: return new SpriteSimple("lava.png",0,0);
		case Constantes.HIELO: return new SpriteSimple("hielo2.png",0,0);
		case Constantes.RAMPA_DERECHA: return new SpriteSimple("rampaderecha.png",0,0);
		case Constantes.RAMPA_IZQUIERDA: return new SpriteSimple("rampaizquierda.png",0,0);
		case Constantes.PUERTA_SALIDA: return new SpriteSimple("puertasalida.png",0,0);
		case Constantes.PUERTA_ENTRADA: return new SpriteSimple("entrada.png",0,0);
		case Constantes.POOGLINS_CONGELADO: return new SpriteSimple("congelado30X45.png",0,0);
		//case Constantes.TUNEL_DERECHA: return new SpriteSimple("Congelado30X45.png",0,0);
		//case Constantes.TUNEL_IZQUIERDA: return new SpriteSimple("Congelado30X45.png",0,0);
		case Constantes.TUNEL_PARED: return new SpriteSimple("tunelpared.png",0,0);
		default: return new SpriteSimple("vacio.png",0,0);
		}
	}
}
