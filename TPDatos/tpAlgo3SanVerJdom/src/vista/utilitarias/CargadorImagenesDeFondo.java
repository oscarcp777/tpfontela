package vista.utilitarias;

import java.util.Date;

import modelo.constantes.Constantes;
import vista.componentes.SpriteSimple;

/*
 * LO MISMO QUE LAS ANTERIORES CAMBIE TODO. A MINUSCULA
 * */
public class CargadorImagenesDeFondo {
	
	public static ListaCircular<SpriteSimple> crearImagen(int id){
		switch (id) {
		case ConstantesVista.NIVEL_UNO: return crearListaNivelUno();
		case ConstantesVista.NIVEL_DOS: return crearListaNivelDos();
		case ConstantesVista.NIVEL_TRES: return crearListaNivelTres();
		case ConstantesVista.NIVEL_CUATRO: return crearListaNivelCuatro();
		case ConstantesVista.NIVEL_CINCO: return crearListaNivelCinco();
		case ConstantesVista.NIVEL_SEIS: return crearListaNivelSeis();
		case ConstantesVista.NIVEL_SIETE: return crearListaNivelSiete();
		case ConstantesVista.NIVEL_OCHO: return crearListaNivelOcho();
		case ConstantesVista.NIVEL_NUEVE: return crearListaNivelNueve();
		case ConstantesVista.NIVEL_DIEZ: return crearListaNivelDiez();
		case ConstantesVista.NIVEL_ONCE: return crearListaNivelOnce();
		case ConstantesVista.NIVEL_DOCE: return crearListaNivelDoce();
		case ConstantesVista.PANEL_PRINCIPAL: return crearListaPanelPricipal();
		case ConstantesVista.PANEL_NIVELES: return crearListaPanelDeNiveles();
		case ConstantesVista.PANEL_GUARDADOS: return crearListaPanelGuardados();
		case ConstantesVista.PANEL_RESULTADOS: return crearListaPanelResultados();
		default: return crearListaNivelUno();
		}
	}
	
	private static ListaCircular<SpriteSimple> crearListaNivelDoce() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("nivel12.jpg",0,0));
		return list;
	}

	private static ListaCircular<SpriteSimple> crearListaNivelOnce() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("nivel11.jpg",0,0));
		return list;
	}

	private static ListaCircular<SpriteSimple> crearListaNivelDiez() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("nivel10.jpg",0,0));
		return list;
	}

	private static ListaCircular<SpriteSimple> crearListaNivelNueve() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("nivel09.jpg",0,0));
		return list;
	}

	private static ListaCircular<SpriteSimple> crearListaNivelOcho() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("nivel08.jpg",0,0));
		return list;
	}

	private static ListaCircular<SpriteSimple> crearListaPanelResultados() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("fondo.png",0,0));
		return list;
	}
	
	private static ListaCircular<SpriteSimple> crearListaPanelGuardados() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("juegosGuardados.jpg",0,0));
		return list;
	}
	
	private static ListaCircular<SpriteSimple> crearListaPanelDeNiveles() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("nivelesPooglin.jpg",0,0));
		return list;
	}

	private static ListaCircular<SpriteSimple> crearListaPanelPricipal() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("principalFachera.jpg",0,0));
		return list;
	}

	private static ListaCircular<SpriteSimple> crearListaNivelUno() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("nivel01.jpg",0,0));
		return list;
	}
	private static ListaCircular<SpriteSimple> crearListaNivelDos() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("nivel02.jpg",0,0));
		return list;
	}

	private static ListaCircular<SpriteSimple> crearListaNivelTres() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("nivel03.jpg",0,0));
		return list;
	}

	private static ListaCircular<SpriteSimple> crearListaNivelCuatro() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("nivel04.jpg",0,0));
		return list;
	}

	private static ListaCircular<SpriteSimple> crearListaNivelCinco() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("nivel05.jpg",0,0));
		return list;
	}

	private static ListaCircular<SpriteSimple> crearListaNivelSeis() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("nivel06.jpg",0,0));
		return list;
	}

	private static ListaCircular<SpriteSimple> crearListaNivelSiete() {
		ListaCircular<SpriteSimple> list = new ListaCircular<SpriteSimple>();
		list.add(new SpriteSimple("nivel07.jpg",0,0));
		return list;
	}

	
}
