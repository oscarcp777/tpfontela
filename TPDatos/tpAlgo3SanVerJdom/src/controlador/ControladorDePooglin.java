package controlador;


import vista.componentes.BotoneraHabilidades;
import vista.utilitarias.ObservadorLabels;
import controlador.excepciones.HabilidadInactivaException;
import modelo.constantes.Constantes;
import modelo.entornoDeJuego.ControladorEstadoPooglin;


public class ControladorDePooglin{
	
	private ControladorEstadoPooglin controladorPoglin;
	private ControladorEstadoHabilidades controladorHabilidades;
	private ObservadorLabels observador;
	
	
	public ControladorDePooglin(ControladorEstadoPooglin controladorPoglin){
		this.controladorPoglin = controladorPoglin;
		this.controladorHabilidades = ControladorEstadoHabilidades.getIntence();
		
	}
	
	public void activarHabilidad(int idHabilidad) {
		
		this.controladorHabilidades.modificarEstadoDeHabilidad(idHabilidad);		
	}
	
	public synchronized void setHabilidad(int idPooglin) throws HabilidadInactivaException{
		if(controladorHabilidades.HabilidaEstaActiva() && 
				ControladorDeDisponibilidadHabilidades.getInstance(controladorPoglin.obtenerHabilidades()).tieneDisponibles(this.controladorHabilidades.getIdHabilidad())){
			switch (controladorHabilidades.getIdHabilidad()) {
				case Constantes.HABILIDAD_NULA: this.controladorPoglin.setearHabilidadAPooglin(idPooglin, controladorHabilidades.getIdHabilidad());
				break;
			    case Constantes.PARACAIDISTA_ESPACIAL : this.controladorPoglin.setearHabilidadAPooglin(idPooglin, controladorHabilidades.getIdHabilidad());
				break;
			//En caso de no ser una habilidad seteara un oficio.   
			default:this.controladorPoglin.setearOficioAPooglin(idPooglin, controladorHabilidades.getIdHabilidad());
				break;
			}
			
			ControladorDeDisponibilidadHabilidades.getInstance(controladorPoglin.obtenerHabilidades()).descontarUno(this.controladorHabilidades.getIdHabilidad());
			this.observador.actualizar(controladorHabilidades.getIdHabilidad(),ControladorDeDisponibilidadHabilidades.getInstance(controladorPoglin.obtenerHabilidades()).obtenerDiponibles(controladorHabilidades.getIdHabilidad()));
		}else throw new HabilidadInactivaException();
	}

	public ControladorEstadoPooglin getControladorPoglin() {
		return controladorPoglin;
	}

	public void suscribirObservador(ObservadorLabels obs) {
		// TODO Auto-generated method stub
		this.observador = obs;
		
	} 
	
	
	
 
 
}
