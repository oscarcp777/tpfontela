package vista.utilitarias;

import modelo.constantes.Constantes;
import vista.componentes.SpriteSimple;
import vista.utilitarias.ListaCircular;
/*
 * MODIFIQUE LOS NOMBRES, AHORA TODO. ES EN MINUSCULAS
 * */
public class CargadorDeListasImagenes {

	
	
	public static ListaCircular<SpriteSimple> crearListaDeSecuencias(int id){
		switch (id) {
		case Constantes.CAMINANTE: return crearListaCaminante();
		case Constantes.CONSTRUCTOR: return crearListaConstructor();
		case Constantes.TALADRADOR: return crearListaTaladrador();
		case Constantes.CONGELADO: return crearListaCongelado();
		case Constantes.LASERMAN: return crearListaLaserman();
		case Constantes.CAMINANTE_CAYENTE: return crearListaCaminanteCayente();
		case Constantes.TELEPORTER: return crearListaTeleporter();
		case Constantes.PARACAIDISTA_ESPACIAL: return crearListaParacaidista();
		case ConstantesVista.CAMINANTE_IZQ: return crearListaCaminanteIzq();
		case ConstantesVista.CONSTRUCTOR_IZQ: return crearListaConstructorIzq();
		case ConstantesVista.TALADRADOR_IZQ: return crearListaTaladrador();
		case ConstantesVista.CONGELADO_IZQ: return crearListaCongelado();
		case ConstantesVista.LASERMAN_IZQ: return crearListaLasermanIzq();
		case ConstantesVista.CAMINANTE_CAYENTE_IZQ: return crearListaCaminanteCayente();
		case ConstantesVista.TELEPORTER_IZQ: return crearListaTeleporter();
		case ConstantesVista.PARACAIDISTA_ESPACIAL_IZQ: return crearListaParacaidista();
		default: return crearListaCaminante();
		}
		
	}

	private static ListaCircular<SpriteSimple> crearListaLasermanIzq() {
		// TODO Auto-generated method stub
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("laser_01_30x45_izquierda.png",0,0));
		list.add(new SpriteSimple("laser_02_30x45_izquierda.png",0,0));
		list.add(new SpriteSimple("laser_03_30x45_izquierda.png",0,0));
		list.add(new SpriteSimple("laser_04_30x45_izquierda.png",0,0));
		return list;

	}

	private static ListaCircular<SpriteSimple> crearListaConstructorIzq() {
		// TODO Auto-generated method stub
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("tunelelectro_01_30x45_izquierda.png",0,0));
		list.add(new SpriteSimple("tunelelectro_02_30x45_izquierda.png",0,0));
		list.add(new SpriteSimple("tunelelectro_03_30x45_izquierda.png",0,0));
		list.add(new SpriteSimple("tunelelectro_04_30x45_izquierda.png",0,0));
		return list;

	}

	private static ListaCircular<SpriteSimple> crearListaCaminanteIzq() {
		// TODO Auto-generated method stub
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("camina_01_30x45_izquierda.png",0,0));
		list.add(new SpriteSimple("camina_02_30x45_izquierda.png",0,0));
		list.add(new SpriteSimple("camina_03_30x45_izquierda.png",0,0));
		list.add(new SpriteSimple("camina_04_30x45_izquierda.png",0,0));
		return list;

	}

	private static ListaCircular<SpriteSimple> crearListaParacaidista() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("plato_01_30x45.png",0,0));
		list.add(new SpriteSimple("plato_02_30x45.png",0,0));
		list.add(new SpriteSimple("plato_03_30x45.png",0,0));
		list.add(new SpriteSimple("plato_04_30x45.png",0,0));
		
		return list;
	}

	/*
	 * ACA FALTA CARGAR LAS IMAGENES POSTA!!!
	 */
	private static ListaCircular<SpriteSimple> crearListaTeleporter() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("camina_01_30x45.png",0,0));
		list.add(new SpriteSimple("camina_02_30x45.png",0,0));
		list.add(new SpriteSimple("camina_03_30x45.png",0,0));
		list.add(new SpriteSimple("camina_04_30x45.png",0,0));
		return list;
	}

	private static ListaCircular<SpriteSimple> crearListaCaminanteCayente() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("cae_01_30x45.png",0,0));
		list.add(new SpriteSimple("cae_02_30x45.png",0,0));
		list.add(new SpriteSimple("cae_03_30x45.png",0,0));
		list.add(new SpriteSimple("cae_04_30x45.png",0,0));
		return list;
	}
	/*
	 * ACA FALTA CARGAR LAS IMAGENES POSTA!!!
	 */
	private static ListaCircular<SpriteSimple> crearListaLaserman() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("laser_01_30x45.png",0,0));
		list.add(new SpriteSimple("laser_02_30x45.png",0,0));
		list.add(new SpriteSimple("laser_03_30x45.png",0,0));
		list.add(new SpriteSimple("laser_04_30x45.png",0,0));
		return list;
	}
	/*
	 * ACA FALTA CARGAR LAS IMAGENES POSTA!!!
	 */
	private static  ListaCircular<SpriteSimple> crearListaCongelado() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("congelado30X45.png",0,0));
		return list;
	}

	private static ListaCircular<SpriteSimple> crearListaTaladrador() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("taladrador_01_30x45.png",0,0));
		list.add(new SpriteSimple("taladrador_02_30x45.png",0,0));
		list.add(new SpriteSimple("taladrador_03_30x45.png",0,0));
		list.add(new SpriteSimple("taladrador_04_30x45.png",0,0));
		return list;
	}
	/*
	 * ACA FALTA CARGAR LAS IMAGENES POSTA!!!
	 */
	private static ListaCircular<SpriteSimple> crearListaConstructor() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("tunelelectro_01_30x45.png",0,0));
		list.add(new SpriteSimple("tunelelectro_02_30x45.png",0,0));
		list.add(new SpriteSimple("tunelelectro_03_30x45.png",0,0));
		list.add(new SpriteSimple("tunelelectro_04_30x45.png",0,0));
		return list;
	}

	private static ListaCircular<SpriteSimple> crearListaCaminante() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("camina_01_30x45.png",0,0));
		list.add(new SpriteSimple("camina_02_30x45.png",0,0));
		list.add(new SpriteSimple("camina_03_30x45.png",0,0));
		list.add(new SpriteSimple("camina_04_30x45.png",0,0));
		return list;
	}
	
	

}
