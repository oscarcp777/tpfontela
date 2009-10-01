package modelo.entornoDeJuego;

import modelo.movimientos.Direccion;
import modelo.pooglins.Posicion;
/**
 * Clase: Interfaz ServiciosTerreno.
 * Utilidad: Agrupar un conjunto de metodos referidos a la construccion de ciertos
 *           tipos de terreno.
 * */
public interface ServiciosTerreno {
	
	public MaterialDeTerreno getSiguienteMaterial(Direccion direccion, Posicion posicion);
	
	public MaterialDeTerreno getMaterialAnterior(Direccion direccion, Posicion posicion);

	public MaterialDeTerreno getMaterialActual( Posicion posicion);
	
	public void crearPuente(Posicion miPosicion, Direccion direccion);
	
	public void romperTerreno(Posicion miPosicion, Direccion dirMovimiento);
	
	public void cavarTerreno(Posicion miPosicion, Direccion direccion);
	
	public void crearPiso(Posicion miPosicion);
	
	public void generarVacio(Posicion miPosicion);
	
	public void generarTunel(Posicion miPosicion);
	
	public void crearPooglinCongelado(Posicion miPosicion);
	
	public MaterialDeTerreno getSiguienteMaterialTeleportador(Direccion direccion, Posicion posicion);
	
	//El excavador las usa para reemplazar el terreno actual por una rampa
	public void crearRampaDerecha(Posicion miPosicion);
	
	public void crearRampaIzquierda(Posicion miPosicion);

	public void crearVacio(Posicion modificar);
	
}
