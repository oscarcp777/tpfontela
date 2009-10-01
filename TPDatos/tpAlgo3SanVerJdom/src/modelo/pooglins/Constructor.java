package modelo.pooglins;

import controlador.ConstantesControlador;
import modelo.constantes.Constantes;
import modelo.entornoDeJuego.ServiciosTerreno;
import modelo.movimientos.Direccion;


/**
 * Clase: Constructor (extiende de Oficio).
 * Utilidad: Utilizado para representar al builder del Lemmings original, permite 
 * 			 manipular la logica del Constructor, ya sea para el caso del movimiento
 * 			 como para la construccion de un puente.
 * Utilizada por: Pooglin.
 * Colabora con: Direccion, ServiciosTerreno, Posicion.
 * */
public class Constructor extends Oficio {
	
	private int cantidadMovimientosRestantes;

	public Constructor(Direccion direccion, Habilidad habilidad){
		this.direccion = direccion;
		this.direccion.subirDireccion();
		this.finalizado = false;
		this.cantidadMovimientosRestantes = Constantes.CANTIDAD_MOV_CONSTRUCTOR;
		this.habilidad = habilidad;
		this.idOficio = Constantes.CONSTRUCTOR;
	}
	@Override
	public void mover(ServiciosTerreno terreno, Posicion miPosicion) {
		if(this.tePuedesMover(terreno, miPosicion)){
			if(this.cantidadMovimientosRestantes == Constantes.CANTIDAD_MOV_CONSTRUCTOR) this.construirPuente(miPosicion, terreno);
			this.avanzar(miPosicion);
			this.construirPuente(miPosicion, terreno);
			this.cantidadMovimientosRestantes--;
			
		}else{
			this.finalizado = true;
		}
	}

	@Override
	public Oficio generarOficioSiguiente(ServiciosTerreno terreno, Posicion posicion) {
		Direccion direccion = this.direccion;
		direccion.modificarDireccion();
		if(this.cantidadMovimientosRestantes != 0) direccion.invertir();
		return FabricaDeOficio.crearCaminante(direccion, this.habilidad);
	}
	@Override
	protected boolean tePuedesMover(ServiciosTerreno terreno, Posicion miPosicion) {
		return (terreno.getSiguienteMaterial(direccion, miPosicion).esVacio()&& this.cantidadMovimientosRestantes > 0);

	}
	private void construirPuente( Posicion miPosicion, ServiciosTerreno terreno){
		terreno.crearPuente(miPosicion, this.direccion);
		for (int i = 1; i < ConstantesControlador.ALTURA_POOLGIN; i++) {
			terreno.generarVacio(new Posicion(miPosicion.getX(),miPosicion.getY()-i));			
		}
	}

}
