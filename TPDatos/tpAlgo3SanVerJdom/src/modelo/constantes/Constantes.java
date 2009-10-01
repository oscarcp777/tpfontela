package modelo.constantes;

import java.io.InputStream;
import java.io.StreamTokenizer;

import vista.utilitarias.ConstantesVista;

/**
 * Clase: Constantes
 * Utilidad: Clase definida para agrupar a todas las constantes que seran  utilizadas
 * 			 en el proyecto. No tiene metodos ni atributos, solo constantes.
 * 
 * */
public class Constantes {
	
	/**
	 * Constantes de territorio
	 */
	public static final int PISO = 0;
	public static final int RAMPA_DERECHA = 1;  //  es igual a:  /
	public static final int RAMPA_IZQUIERDA = 2;//  es igual a:  \
	public static final int PARED = 3;
	public static final int VACIO = 4;
	public static final int FUEGO = 5;
	public static final int HIELO = 6;
	public static final int POOGLINS_CONGELADO = 7;
	public static final int PISO_PIEDRA = 8;
	public static final int PARED_PIEDRA = 9;
	public static final int TUNEL_DERECHA = 1;
	public static final int TALADRO = 11;
	public static final int AGUJERO_NEGRO = 12;
	public static final int PUERTA_ENTRADA = 13;
	public static final int PUERTA_SALIDA = 14;
	public static final int TUNEL_IZQUIERDA = 2;
	public static final int TUNEL_PARED = 16;
	

    /**
	 * Constantes de movimientos
	 */
	public static final int CANTIDAD_MOV_TALADRADOR = 5;//TENEMOS QUE VER CUANToS SON
	public static final int CANTIDAD_MOV_CONSTRUCTOR = 6;//TENEMOS QUE VER CUANToS SON
	public static final int VELOCIDAD_CAIDA_DISMINUIDA = 0;//TENEMOS QUE VER si sirve
	public static final int VELOCIDAD_CAIDA_NORMAL = 1;//TENEMOS QUE VER si sirve
	public static final int ALTURA_MAX_CAIDA = 5 * 3 ;// 5 * ConstantesVista.ALTURA_POOLGIN;
	public static final int CANTIDAD_POSICION_TELETRANSPORTACION = 20;
	public static final int CANTIDAD_MOV_TELEPORTER_CAMINANDO = 5;
	/**
	 * Constantes de tipo de pooglins
	 */
	public static final int CAMINANTE = 0;
	public static final int CONSTRUCTOR = 1;
	public static final int TALADRADOR = 2;
	public static final int CONGELADO = 3;
	public static final int LASERMAN = 4;
	public static final int CAMINANTE_CAYENTE = 5;
	public static final int TELEPORTER = 6;
	
	/**
	 * Constantes de Habilidades
	 */
	public static final int HABILIDAD_NULA = 8;
	public static final int PARACAIDISTA_ESPACIAL = 9;
	
	
}
