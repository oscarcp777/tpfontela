package modelo.pooglins;

import modelo.constantes.Constantes;
import modelo.entornoDeJuego.MaterialDeTerreno;
import modelo.entornoDeJuego.ServiciosTerreno;
import modelo.excepciones.MuerteDePooglinException;
import modelo.movimientos.Direccion;
/**
 * Clase: CaminanteCayendo.
 * Utilidad: Se utiliza para delegar la logica de un Pooglin que cae, en esta clase. 			 
 * Utilizada por: Pooglin.
 * Colabora Con: Direccion, Habilidad.
 * */
public class CaminanteCayendo extends Oficio {
	
	private int alturaMaxCaida;
	
	public CaminanteCayendo(Direccion dir, Habilidad habilidad){
		this.direccionAnterior = dir;
		this.direccion = new Direccion();
		this.direccion.setAbajo();
		this.finalizado = false;
		this.habilidad = habilidad;
		this.alturaMaxCaida = Constantes.ALTURA_MAX_CAIDA;
		this.idOficio = Constantes.CAMINANTE_CAYENTE;
	}
	
	public void mover(ServiciosTerreno terreno, Posicion miPosicion) {
		if(this.tePuedesMover(terreno, miPosicion)){
			this.avanzar(miPosicion);
			this.alturaMaxCaida = this.alturaMaxCaida - this.habilidad.getVelocidadDeCaida();  
		}else this.finalizado = true;
			
	}

	public Direccion getDirAnterior() {
		return direccionAnterior;
	}
	
	protected boolean tePuedesMover(ServiciosTerreno terreno, Posicion miPosicion){
		MaterialDeTerreno aux = terreno.getMaterialActual(miPosicion); 
		return aux.esVacio();
	}

	@Override
	public Oficio generarOficioSiguiente(ServiciosTerreno terreno, Posicion miPosicion) {
			if(this.alturaMaxCaida > 0){
				return FabricaDeOficio.crearCaminante(this.direccionAnterior, this.habilidad);
			}else throw new MuerteDePooglinException();
	}

}
