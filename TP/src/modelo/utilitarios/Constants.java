package modelo.utilitarios;

import modelo.movimientoPooglins.Abajo;
import modelo.movimientoPooglins.Derecha;
import modelo.movimientoPooglins.DiagonalArribaDerecha;
import modelo.movimientoPooglins.Izquierda;

public class Constants {

	public interface TipoVelocidad{
	public static int VELOCIDAD_NORMAL=1;
	public static int VELOCIDAD_MEDIA=2;
	public static int VELOCIDAD_RAPIDA=3;
	public static int VELOCIDAD_MUYRAPIDA=4;
	}
	
	//como se llaman las clases porque se usa reflection para la persistencia
	public interface NombreTerrenos{
		public static String TIERRA = "Tierra"; 
		public static String AIRE = "Aire";
		public static String FUEGO = "Fuego";
		public static String ROCA = "Roca";
		public static String AGUJERO_NEGRO = "AgujeroNegro";
		public static String HIELO = "Hielo";
		public static String TUNEL_DERECHA = "TunelDerecha";
		public static String TUNEL_IZQUIERDA = "TunelIzquierda";
		
	}
	
	public interface NombreDirecciones{
		public static String ABAJO = "Abajo";
		public static String DERECHA = "Derecha";
		public static String IZQUIERDA = "Izquierda";
		public static String DIAGONAL_ARRIBA_DERECHA = "DiagonalArribaDerecha";
		public static String DIAGONAL_ARRIBA_IZQUIERDA = "DiagonalArribaIzquierda";
			
	}
	
	public interface NombreHabilidades{
		public static String CONGELAMIENTO = "Congelamiento";
		public static String PLATILLO_VOLADOR = "PlatilloVolador";
		public static String RAYO_LASER = "RayoLaser";
		public static String TALADRO_ULTRASONICO = "TaladroUltrasonico";
		public static String TELETRANSPORTACION = "Teletransportacion";
		public static String TUNEL_ELECTROMAGNETICO = "TunelElectromagnetico";
	}
	
	public interface ValorComparador{
		public static int MAYOR=1;
		public static int IGUAL=0;
		public static int MENOR=-1;
	}
	
	public interface SentidoMovimiento{
		public static int DERECHA=1;
		public static int IZQUIERDA=-1;
		public static int ABAJO=-2;
		public static int ARRIBA=2;
		public static int NULO=0;
	}
	
	public interface PooglinAlVacio{
		public static int CANTIDAD_PASOS_AIRE_MUERE=5;
	}
		
	public interface MapasDeJuego{
		public static String NIVEL_1="xml//nivel1.xml";
		public static String NIVEL_2="xml//nivel2.xml";
		public static String NIVEL_3="xml//nivel3.xml";
		public static String PARTIDA_GUARDADA="xml//partida.xml";
	}
		
	public interface PathImages{
		public static String IMAGE_POOGLIN="\\images\\pooglin.gif";
		public static String IMAGE_TUNEL_DERECHA="imagenes/tunelDerecha.png";
		public static String IMAGE_TUNEL_IZQUIERDA="imagenes/tunelIzquierda.png";
	}
	
	
	
}
 