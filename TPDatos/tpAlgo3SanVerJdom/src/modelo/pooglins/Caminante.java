package modelo.pooglins;

import modelo.entornoDeJuego.MaterialDeTerreno;
import modelo.entornoDeJuego.ServiciosTerreno;
import modelo.excepciones.MuerteDePooglinException;
import modelo.excepciones.PooglinGanadorException;
import modelo.movimientos.Direccion;
import modelo.constantes.Constantes;
/*SOLUCIONAR EL INCONVENIENTE DEL SUBIR Y BAJAR TIENE QUE SER VACIO EL DE ARRIBA EN EL CASO DE SUBIR
 * Y EN EL CASO DE BAJAR TIENE QUE SER VACIO EL DE ABAJO
 */
/**
 * Clase: Caminante.
 * Utilidad: Utilizada para la representacion de la logica de un Pooglin Caminante, 
 *           extiende de Oficio.
 *           Tiene la logica necesaria para utilizar la accion mover de un Pooglin.
 * Utilizada Por: Pooglin.
 * Colabora Con: Direccion, ServiciosTerreno, Posicion.
 * */
public class Caminante extends Oficio {
	
	
	public Caminante(Direccion dir, Habilidad habilidad){
		this.setDireccion(dir);
		this.direccionAnterior = dir.copiar();
		this.finalizado = false;
		this.habilidad = habilidad;
		this.idOficio = Constantes.CAMINANTE;
		
	}
	public Oficio generarOficioSiguiente(ServiciosTerreno terreno, Posicion posicion){
		if (terreno.getMaterialActual(posicion).esVacio())	
		return FabricaDeOficio.crearCaminanteCayente(this.direccion,this.getHabilidad());
		else if(terreno.getMaterialActual(posicion).esPuertaDeSalida()){
			throw new PooglinGanadorException();
		}
		else
			throw new MuerteDePooglinException();
		}

	private void cambiarDireccion(Posicion miPosicion, ServiciosTerreno terreno){
		MaterialDeTerreno actual = terreno.getMaterialActual(miPosicion);
			if( actual.esEscalable()){
				if((actual.esRampaDerecha()&& this.direccion.esDireccionDerecha())||
						(actual.esRampaIzquierda()&& this.direccion.esDireccionIzquierda())){
					this.direccionAnterior = this.direccion.copiar();
					this.direccion.subirDireccion();
				}
				/*if((actual.esRampaDerecha()&& this.direccion.esDireccionIzquierda())||
						(actual.esRampaIzquierda()&& this.direccion.esDireccionDerecha())){
					setDireccionAnterior(this.direccion);
					this.direccion.bajarDireccion();
				}*/
			}
	}
	
	private void revertirDireccion(Posicion miPosicion, ServiciosTerreno terreno){
		/*MaterialDeTerreno actual = terreno.getMaterialActual(miPosicion);
		MaterialDeTerreno anterior = terreno.getMaterialAnterior(this.direccion, miPosicion);
			if(anterior.esEscalable()){
				this.direccion.bajarDireccion();
			}*/
		this.direccion = this.direccionAnterior;
	}
	
	private void rebotar(){
		this.direccion.invertir();
		this.direccionAnterior = this.direccion.copiar();
	}
	public void mover(ServiciosTerreno terreno, Posicion miPosicion) {
	    MaterialDeTerreno aux = terreno.getMaterialActual(miPosicion);
	    int cantidadMovimientos;
	    if(aux.esHielo()){
	    	cantidadMovimientos = 2;
	    }
	    else{
	    	cantidadMovimientos = 1;
	    }
	    while(!(cantidadMovimientos == 0) && !this.finalizado){
	    	if(aux.esVacio()){
	    		this.finalizado = true;
	    	}	
	    	else if (aux.esMortal() || aux.esPuertaDeSalida()){
	    		this.finalizado = true;
	    	}else{
	    
	    		if(tePuedesMover(terreno, miPosicion)){
	    			
	    			this.avanzar(miPosicion);
	    			this.direccion.setHorizontal();
	    			aux = terreno.getMaterialActual(miPosicion);
	       	
	    		}else{
	    			this.rebotar();
	    		}
	    	
	    		cantidadMovimientos--;	
	    	}
	    }
    }

	protected boolean tePuedesMover(ServiciosTerreno terreno, Posicion miPosicion){
		 this.cambiarDireccion(miPosicion, terreno);
		 MaterialDeTerreno materialActual = terreno.getSiguienteMaterial(direccion, miPosicion);
		 return materialActual.esCaminable();
	}	
	

}
