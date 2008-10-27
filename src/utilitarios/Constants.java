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
	
	public interface NombreTerreno{
		public static String AGUJERO_NEGRO="Agujero Negro";
		public static String AIRE="Aire";
		public static String FUEGO="Fuego";
		public static String HIELO="Hielo";
		public static String ROCA="Roca";
		public static String TIERRA="Tierra";
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
 