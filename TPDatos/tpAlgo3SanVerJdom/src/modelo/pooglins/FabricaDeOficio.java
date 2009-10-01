package modelo.pooglins;


import modelo.constantes.Constantes;
import modelo.excepciones.IdOficioIncorrectoException;
import modelo.movimientos.Direccion;
import modelo.pooglins.Caminante;
import modelo.pooglins.CaminanteCayendo;
import modelo.pooglins.Habilidad;
import modelo.pooglins.Oficio;
/**
 * Clase: FabricaDeOficio.
 * Utilidad: Permite crear oficios tales como Caminante, CaminanteCayente...
 * Colabora con: Oficio, Direccion, Habilidad.
 * */
public class FabricaDeOficio{
	
	
	public static Oficio crearOficio(Oficio oficio){
		if(oficio instanceof Caminante){
			Oficio nuevoOficio = new CaminanteCayendo(oficio.getDireccion(), oficio.getHabilidad());
			return nuevoOficio;
		}
		else if(oficio instanceof CaminanteCayendo){
			CaminanteCayendo oficioCaminanteCayendo = (CaminanteCayendo)oficio;
			Oficio nuevoOficio = new Caminante(oficioCaminanteCayendo.getDirAnterior(), oficioCaminanteCayendo.getHabilidad());
			return nuevoOficio;
		}else{
			Oficio nuevoOficio = new Caminante(oficio.getDireccion(), oficio.getHabilidad());
			return nuevoOficio;
		}
		
	}
	public static Oficio crearCaminante( Direccion direccion, Habilidad habilidad){ 
		return new Caminante(direccion,habilidad);
		
	}
	public static Oficio crearCaminanteCayente( Direccion direccion, Habilidad habilidad){ 
		
		return new CaminanteCayendo(direccion,habilidad);
		
	}
	public static Oficio crearOficioPorId(int id, Direccion direccion, Habilidad habilidad){
		switch (id) {
		case Constantes.CAMINANTE: return new Caminante(direccion, habilidad);
		case Constantes.CAMINANTE_CAYENTE: return new CaminanteCayendo(direccion, habilidad);
		case Constantes.TELEPORTER: return new Teleportador(direccion, habilidad);
		case Constantes.TALADRADOR: return new Taladrador(direccion, habilidad);
		case Constantes.CONGELADO: return new Congelado();
		case Constantes.CONSTRUCTOR: return new Constructor(direccion, habilidad);
		case Constantes.LASERMAN: return new Laserman(direccion, habilidad);
		
		default: throw new IdOficioIncorrectoException(); 
		}
	}
}