package utilitarios;

public class Constants {

	public interface TamanioMatriz{
	public static int MAX = 10; 
	}
	
	public interface TipoVelocidad{
	public static int VELOCIDAD_NORMAL=1;
	public static int VELOCIDAD_MEDIA=2;
	public static int VELOCIDAD_RAPIDA=3;
	public static int VELOCIDAD_MUYRAPIDA=4;
	}
	
	public interface NombreTerrenos{
		public static String TIERRA = "tierra";
		public static String AIRE = "aire";
		public static String FUEGO = "fuego";
		public static String ROCA = "roca";
		public static String AGUJERO_NEGRO = "agujeroNegro";
		public static String HIELO = "hielo";
		public static String TUNEL = "tunel";
		
	}
	
	public interface NombreHabilidades{
		public static String CONGELAMIENTO = "congelamiento";
		public static String PLATILLO_VOLADOR = "platilloVolador";
		public static String RAYO_LASER = "rayoLaser";
		public static String TALADRO_ULTRASONICO = "taladroUltrasonico";
		public static String TELETRANSPORTACION = "teletransportacion";
		public static String TUNEL_ELECTROMAGNETICO = "tunelElectromagnetico";
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
	
}
 