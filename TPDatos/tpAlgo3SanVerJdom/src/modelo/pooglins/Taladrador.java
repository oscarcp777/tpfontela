package modelo.pooglins;

import vista.utilitarias.ConstantesVista;
import modelo.constantes.Constantes;
import modelo.entornoDeJuego.BuilderMaterial;
import modelo.entornoDeJuego.ServiciosTerreno;
import modelo.movimientos.Direccion;
/**
 * Clase: Taladrador (extiende de Oficio).
 * Utilidad: Representar el Oficio Taladrador de un Pooglin, maneja la logica del
 * 			 movimiento de un Taladrador, asi como tambien la accion de taladrar.
 * Utilizada por: Pooglin.
 * Colbora con: Direccion, Posicion, ServiciosTerreno.
 * 
 * */
public class Taladrador extends Oficio {
	
	private int cantidadMovimientosRestantes;

	public Taladrador(Direccion direccion, Habilidad habilidad){
		this.direccionAnterior = direccion;	
		this.direccion = new Direccion();
		this.direccion.setAbajo();
		this.habilidad = habilidad;
		this.finalizado = false;
		this.cantidadMovimientosRestantes = Constantes.CANTIDAD_MOV_TALADRADOR;
		this.idOficio = Constantes.TALADRADOR;
		
	}
	
	@Override
	public void mover(ServiciosTerreno terreno, Posicion miPosicion) {
		if(this.tePuedesMover(terreno, miPosicion)){
			
			this.taladrar(terreno,miPosicion);
			this.avanzar(miPosicion);
			
			
			this.cantidadMovimientosRestantes--;
			
		}else this.finalizado = true;
	}
	@Override
	public Oficio generarOficioSiguiente(ServiciosTerreno terreno, Posicion posicion) {
		if (!terreno.getMaterialActual(posicion).esVacio()){
		return FabricaDeOficio.crearCaminante(this.direccionAnterior, this.habilidad);
		}else{
		return FabricaDeOficio.crearCaminanteCayente(this.direccionAnterior, this.habilidad);
		}
	}
	@Override
	protected boolean tePuedesMover(ServiciosTerreno terreno, Posicion miPosicion) {
		return (this.cantidadMovimientosRestantes > 0 && terreno.getMaterialActual(miPosicion).esRompible());
	}
	private void taladrar(ServiciosTerreno terreno, Posicion miPosicion){
		Posicion pos = miPosicion.copiar();
		pos.moverEnDireccion(this.direccion);
		/*if (this.cantidadMovimientosRestantes == Constantes.CANTIDAD_MOV_TALADRADOR){
			 for (int j = 0; j < ConstantesVista.ANCHO_POOGLIN; j++){
				   Posicion aModificar =  new Posicion(pos.getX() + j*this.direccionAnterior.getDireccionX(), pos.getY()+ 1);
	     		   if (terreno.getMaterialActual(aModificar).esRompible()) terreno.crearPiso(aModificar);
					}
		}else{*/
		terreno.cavarTerreno(pos, this.direccionAnterior);
		//}
				
	}
	
}
