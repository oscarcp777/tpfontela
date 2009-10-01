package modelo.pooglins;

import modelo.constantes.Constantes;
import modelo.entornoDeJuego.MaterialDeTerreno;
import modelo.entornoDeJuego.ServiciosTerreno;
import modelo.movimientos.Direccion;
/**
 * Clase: Teleportador (extiende de Oficio).
 * Utilidad: Representar la accion de teletransportarse de un Pooglin, manejando la
 * 			 logica de esta accion.
 * Utilizada por: Pooglin.
 * Colabora con: Direccion, ServiciosTerreno, Posicion.
 * */
public class Teleportador extends Oficio {
private int movimientosRestantes;
private Caminante caminante;

public Teleportador(Direccion direccion, Habilidad habilidad){
	this.direccion = direccion;
	this.habilidad = habilidad;
	this.caminante = new Caminante(this.direccion,this.habilidad);
	
	this.finalizado = false;
	this.movimientosRestantes = Constantes.CANTIDAD_MOV_TELEPORTER_CAMINANDO;
	this.idOficio = Constantes.TELEPORTER;
	
}
/*	public Teleportador(){
		this.finalizado = false;
		this.movimientosRestantes = Constantes.CANTIDAD_MOV_TELEPORTER_CAMINANDO;
		
	}*/
	@Override
	public void mover(ServiciosTerreno terreno, Posicion miPosicion) {
		if(movimientosRestantes > 0){
			this.caminante.mover(terreno, miPosicion);
			this.movimientosRestantes--;
			
		}else{
			if (this.tePuedesMover(terreno, miPosicion)){
			this.teletransportar(direccion,miPosicion);
			}
			finalizado = true;
		}
	}

	private void teletransportar(Direccion direccion, Posicion miPosicion) {
		// deberia lanzar una excepcion si no puede transportarse
		miPosicion.moverEnDireccion(direccion, Constantes.CANTIDAD_POSICION_TELETRANSPORTACION);
	}
	@Override
	public Oficio generarOficioSiguiente(ServiciosTerreno terreno, Posicion posicion) {
		// TODO Auto-generated method stub
		if(terreno.getMaterialActual(posicion).esVacio()){
			return FabricaDeOficio.crearCaminanteCayente(direccion, habilidad);
	}else{
		return FabricaDeOficio.crearCaminante(direccion, habilidad);
	}
	}
	@Override
	protected boolean tePuedesMover(ServiciosTerreno terreno, Posicion miPosicion) {
		MaterialDeTerreno aux = terreno.getSiguienteMaterialTeleportador(this.direccion, miPosicion);
		return aux.esCaminable();
	}
	
}
