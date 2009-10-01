package modelo.pooglins;

import controlador.ConstantesControlador;
import modelo.constantes.Constantes;
import modelo.entornoDeJuego.ServiciosTerreno;
import modelo.movimientos.Direccion;
/**
 * Clase: Laserman (extiende de Oficio).
 * Utilidad: Representar la logica de un Pooglin con el oficio Laser.
 * Utilizada por: Pooglin.
 * Colabora con: Direccion, ServiciosTerreno, Posicion.
 * */
public class Laserman extends Oficio {

	public Laserman(Direccion direccion, Habilidad habilidad){
		this.direccionAnterior = direccion;	
		this.direccion = direccion.copiar();
		this.direccion.setHorizontal();
		this.habilidad = habilidad;
		this.finalizado = false;
		this.idOficio = Constantes.LASERMAN;
		
		
	}
	@Override
	public void mover(ServiciosTerreno terreno, Posicion miPosicion) {
		if(this.tePuedesMover(terreno, miPosicion)){
			
			this.taladrar(terreno,miPosicion);
			this.avanzar(miPosicion);
			
			
			
		}else this.finalizado = true;
	}
	@Override
	public Oficio generarOficioSiguiente(ServiciosTerreno terreno, Posicion posicion) {
		return FabricaDeOficio.crearCaminante(this.direccionAnterior, this.habilidad);
	
	}
	@Override
	protected boolean tePuedesMover(ServiciosTerreno terreno, Posicion miPosicion) {
		// TODO Auto-generated method stub
		return (terreno.getSiguienteMaterial(direccion, miPosicion).esRompible()&& !terreno.getSiguienteMaterial(direccion, miPosicion).esCaminable());
	}

	private void taladrar(ServiciosTerreno terreno, Posicion miPosicion){
		terreno.romperTerreno(new Posicion(miPosicion.getX(),miPosicion.getY()), this.direccion);
		
		/*for (int i = 1; i < ConstantesControlador.ALTURA_POOLGIN; i++) {
			terreno.romperTerreno(new Posicion(miPosicion.getX(),miPosicion.getY()-i));
		}*/
	}
}
