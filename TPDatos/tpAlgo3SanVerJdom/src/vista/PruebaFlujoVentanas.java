package vista;

import java.util.Timer;

import modelo.entornoDeJuego.Mapa;
import vista.manejadores.LevantaMapas;
import vista.utilitarias.FlujoDeJuego;
import vista.utilitarias.IniciadorDeImagenes;
import vista.utilitarias.NavegadorDeVentanas;

public class PruebaFlujoVentanas {
	
	
	public static boolean salir;
	public static boolean ejecutar = true;
	public static boolean pause;
	public static Mapa mapa;
	public static FlujoDeJuego flujo;
	public static int nivelEnJuego = 0;
	 
	
	public static void newGame(int nivel){
		PruebaFlujoVentanas.nivelEnJuego = nivel;
		PruebaFlujoVentanas.mapa = null;
		PruebaFlujoVentanas.mapa = LevantaMapas.getIntance().cargarMapa(nivel);
	}
	
	public static void cargarJuego(Mapa mapa){
		PruebaFlujoVentanas.mapa = null;
		PruebaFlujoVentanas.mapa = mapa;
	}
	
	public static void main(String[] args) {
		
		NavegadorDeVentanas.getInstance().crearPanelPrincipal();
		while (ejecutar){
			if (mapa != null){
				PruebaFlujoVentanas.flujo = new FlujoDeJuego(PruebaFlujoVentanas.mapa,300);
				NavegadorDeVentanas.getInstance().crearPanelDeJuego(PruebaFlujoVentanas.mapa);
				PruebaFlujoVentanas.flujo.CorrerHiloJuego();
				if (PruebaFlujoVentanas.flujo.terminoPartidaCompleta()){
					NavegadorDeVentanas.getInstance().crearPanelDeResultados();
				}
				PruebaFlujoVentanas.flujo = null;
				PruebaFlujoVentanas.mapa = null;
				
			}	
		}
		
	}

}

