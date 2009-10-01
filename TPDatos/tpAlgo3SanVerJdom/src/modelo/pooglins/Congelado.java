package modelo.pooglins;

import modelo.constantes.Constantes;
import modelo.entornoDeJuego.ServiciosTerreno;
import modelo.excepciones.MuerteDePooglinException;
import modelo.movimientos.Direccion;
/**
 * Clase: Congelado (extiende de Oficio)
 * Utilidad: Representar el estado congelado de un Pooglin.
 * Utilizado por: Pooglin.
 * Colabora con: ServiciosTerreno, Posicion.
 * */
public class Congelado extends Oficio {
	
	public Congelado(){
		this.habilidad = new HabilidadNula();
		this.finalizado = false;
		this.idOficio = Constantes.CONGELADO;
		this.direccion = new Direccion();
		
	}

	@Override
	public void mover(ServiciosTerreno terreno, Posicion miPosicion) {
		terreno.crearPooglinCongelado(miPosicion);
		throw new MuerteDePooglinException() ;
	}

	@Override
	public Oficio generarOficioSiguiente(ServiciosTerreno terreno, Posicion posicion) {
		return this;
	}

	@Override
	protected boolean tePuedesMover(ServiciosTerreno terreno, Posicion miPosicion) {
		return true;
	}

	
}
