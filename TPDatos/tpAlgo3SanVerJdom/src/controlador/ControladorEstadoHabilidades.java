package controlador;


public class ControladorEstadoHabilidades {
	
	private int idHabilidad = ConstantesControlador.HABILIDAD_DESACTIVADO;
	private static ControladorEstadoHabilidades controlador;
		
	private ControladorEstadoHabilidades() {
		// TODO Auto-generated constructor stub
	}
	
	public static ControladorEstadoHabilidades getIntence(){
		if(controlador == null) controlador = new ControladorEstadoHabilidades();
		
		return controlador;		
	}
		
	private void activarHabilidad(int idHabilidad){
		this.controlador.idHabilidad = idHabilidad;
	}
	
	private void desactivarHabilidad(){
		idHabilidad = ConstantesControlador.HABILIDAD_DESACTIVADO;
	}
	
	public void modificarEstadoDeHabilidad(int idHabilidad){
		if(ControladorEstadoHabilidades.controlador.idHabilidad == idHabilidad) this.desactivarHabilidad();
		else activarHabilidad(idHabilidad);
	}
	
	public boolean HabilidaEstaActiva(){
		return this.idHabilidad != ConstantesControlador.HABILIDAD_DESACTIVADO;
	}

	public int getIdHabilidad() {
		return idHabilidad;
	}
	
	
	
}