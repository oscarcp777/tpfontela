package modelo.mapeoDirecciones;

import java.util.HashMap;

import modelo.movimientoPooglins.Abajo;
import modelo.movimientoPooglins.Derecha;
import modelo.movimientoPooglins.DiagonalArribaDerecha;
import modelo.movimientoPooglins.DiagonalArribaIzquierda;
import modelo.movimientoPooglins.Direccion;
import modelo.movimientoPooglins.Izquierda;
import modelo.utilitarios.Constants;

public class MapaSingletonsDirecciones {
	
	private static MapaSingletonsDirecciones instance = new MapaSingletonsDirecciones();
	private HashMap map;
	
	//devuelve una unica instancia por ser singleton
	public static MapaSingletonsDirecciones getInstance(){
		return instance;
	}
	private MapaSingletonsDirecciones(){
		map = new HashMap();
		mapearSingletonsDisponibles();
	}
	
	private void mapearSingletonsDisponibles(){
		map.put(Constants.NombreDirecciones.ABAJO, Abajo.getInstance());
		map.put(Constants.NombreDirecciones.DERECHA, Derecha.getInstance());
		map.put(Constants.NombreDirecciones.IZQUIERDA, Izquierda.getInstance());
		map.put(Constants.NombreDirecciones.DIAGONAL_ARRIBA_DERECHA, DiagonalArribaDerecha.getInstance());
		map.put(Constants.NombreDirecciones.DIAGONAL_ARRIBA_IZQUIERDA, DiagonalArribaIzquierda.getInstance());
		
	}
	
	public Direccion obtenerDireccion(String clave){
		return (Direccion)map.get(clave);
	}
}
