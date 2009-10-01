package vista.utilitarias;

import modelo.constantes.Constantes;

public class IniciadorDeImagenes {

	public static void init(){
	ImagenesParcela.getInstance().agregarImagen(Constantes.PISO, CargadorImagenesTerreno.crearImagen(Constantes.PISO));
	ImagenesParcela.getInstance().agregarImagen(Constantes.VACIO, CargadorImagenesTerreno.crearImagen(Constantes.VACIO));
	ImagenesParcela.getInstance().agregarImagen(Constantes.PARED, CargadorImagenesTerreno.crearImagen(Constantes.PARED));
	ImagenesParcela.getInstance().agregarImagen(Constantes.PARED_PIEDRA, CargadorImagenesTerreno.crearImagen(Constantes.PARED_PIEDRA));
	ImagenesParcela.getInstance().agregarImagen(Constantes.AGUJERO_NEGRO, CargadorImagenesTerreno.crearImagen(Constantes.AGUJERO_NEGRO));
	ImagenesParcela.getInstance().agregarImagen(Constantes.POOGLINS_CONGELADO, CargadorImagenesTerreno.crearImagen(Constantes.POOGLINS_CONGELADO));
	ImagenesParcela.getInstance().agregarImagen(Constantes.HIELO, CargadorImagenesTerreno.crearImagen(Constantes.HIELO));
	ImagenesParcela.getInstance().agregarImagen(Constantes.PISO_PIEDRA, CargadorImagenesTerreno.crearImagen(Constantes.PISO_PIEDRA));
	ImagenesParcela.getInstance().agregarImagen(Constantes.FUEGO, CargadorImagenesTerreno.crearImagen(Constantes.FUEGO));
	ImagenesParcela.getInstance().agregarImagen(Constantes.PUERTA_ENTRADA, CargadorImagenesTerreno.crearImagen(Constantes.PUERTA_ENTRADA));
	ImagenesParcela.getInstance().agregarImagen(Constantes.PUERTA_SALIDA, CargadorImagenesTerreno.crearImagen(Constantes.PUERTA_SALIDA));
	ImagenesParcela.getInstance().agregarImagen(Constantes.RAMPA_DERECHA, CargadorImagenesTerreno.crearImagen(Constantes.RAMPA_DERECHA));
	ImagenesParcela.getInstance().agregarImagen(Constantes.RAMPA_IZQUIERDA, CargadorImagenesTerreno.crearImagen(Constantes.RAMPA_IZQUIERDA));
	ImagenesParcela.getInstance().agregarImagen(Constantes.TUNEL_PARED, CargadorImagenesTerreno.crearImagen(Constantes.TUNEL_PARED));
	AnimacionesOficios.getInstance().agregarSecuenciaDeImagen(Constantes.CAMINANTE,CargadorDeListasImagenes.crearListaDeSecuencias(Constantes.CAMINANTE));
	AnimacionesOficios.getInstance().agregarSecuenciaDeImagen(Constantes.TALADRADOR,CargadorDeListasImagenes.crearListaDeSecuencias(Constantes.TALADRADOR));
	AnimacionesOficios.getInstance().agregarSecuenciaDeImagen(Constantes.CAMINANTE_CAYENTE,CargadorDeListasImagenes.crearListaDeSecuencias(Constantes.CAMINANTE_CAYENTE));
	AnimacionesOficios.getInstance().agregarSecuenciaDeImagen(Constantes.LASERMAN,CargadorDeListasImagenes.crearListaDeSecuencias(Constantes.LASERMAN));
	AnimacionesOficios.getInstance().agregarSecuenciaDeImagen(Constantes.CONGELADO,CargadorDeListasImagenes.crearListaDeSecuencias(Constantes.CONGELADO));
	AnimacionesOficios.getInstance().agregarSecuenciaDeImagen(Constantes.CONSTRUCTOR,CargadorDeListasImagenes.crearListaDeSecuencias(Constantes.CONSTRUCTOR));
	AnimacionesOficios.getInstance().agregarSecuenciaDeImagen(Constantes.PARACAIDISTA_ESPACIAL,CargadorDeListasImagenes.crearListaDeSecuencias(Constantes.PARACAIDISTA_ESPACIAL));
	AnimacionesOficios.getInstance().agregarSecuenciaDeImagen(Constantes.TELEPORTER,CargadorDeListasImagenes.crearListaDeSecuencias(Constantes.TELEPORTER));
	AnimacionesOficios.getInstance().agregarSecuenciaDeImagen(ConstantesVista.CAMINANTE_IZQ,CargadorDeListasImagenes.crearListaDeSecuencias(ConstantesVista.CAMINANTE_IZQ));
	AnimacionesOficios.getInstance().agregarSecuenciaDeImagen(ConstantesVista.TALADRADOR_IZQ,CargadorDeListasImagenes.crearListaDeSecuencias(ConstantesVista.TALADRADOR_IZQ));
	AnimacionesOficios.getInstance().agregarSecuenciaDeImagen(ConstantesVista.CAMINANTE_CAYENTE_IZQ,CargadorDeListasImagenes.crearListaDeSecuencias(ConstantesVista.CAMINANTE_CAYENTE_IZQ));
	AnimacionesOficios.getInstance().agregarSecuenciaDeImagen(ConstantesVista.LASERMAN_IZQ,CargadorDeListasImagenes.crearListaDeSecuencias(ConstantesVista.LASERMAN_IZQ));
	AnimacionesOficios.getInstance().agregarSecuenciaDeImagen(ConstantesVista.CONGELADO_IZQ,CargadorDeListasImagenes.crearListaDeSecuencias(ConstantesVista.CONGELADO_IZQ));
	AnimacionesOficios.getInstance().agregarSecuenciaDeImagen(ConstantesVista.CONSTRUCTOR_IZQ,CargadorDeListasImagenes.crearListaDeSecuencias(ConstantesVista.CONSTRUCTOR_IZQ));
	AnimacionesOficios.getInstance().agregarSecuenciaDeImagen(ConstantesVista.PARACAIDISTA_ESPACIAL_IZQ,CargadorDeListasImagenes.crearListaDeSecuencias(ConstantesVista.PARACAIDISTA_ESPACIAL_IZQ));
	AnimacionesOficios.getInstance().agregarSecuenciaDeImagen(ConstantesVista.TELEPORTER_IZQ,CargadorDeListasImagenes.crearListaDeSecuencias(ConstantesVista.TELEPORTER_IZQ));
	
	}
}
