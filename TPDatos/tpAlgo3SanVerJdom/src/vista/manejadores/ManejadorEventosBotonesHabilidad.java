package vista.manejadores;


import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import vista.componentes.BotonGrafico;
import controlador.ControladorDeDisponibilidadHabilidades;
import controlador.ControladorDePooglin;
public class ManejadorEventosBotonesHabilidad extends MouseAdapter {
	
	private ControladorDePooglin controladorDePooglin;
	private static ManejadorEventosBotonesHabilidad instance;
	
	private ManejadorEventosBotonesHabilidad(ControladorDePooglin controladorPooglin){
		controladorDePooglin  = controladorPooglin;
		
	}

	public static ManejadorEventosBotonesHabilidad getInstance(ControladorDePooglin controler){
		if (ManejadorEventosBotonesHabilidad.instance == null) ManejadorEventosBotonesHabilidad.instance = new ManejadorEventosBotonesHabilidad(controler);
		return ManejadorEventosBotonesHabilidad.instance;
	}
	
	
	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		System.out.println("CLICK");
		BotonGrafico b = (BotonGrafico) e.getSource();		
		if(ControladorDeDisponibilidadHabilidades.getInstance(controladorDePooglin.getControladorPoglin().obtenerHabilidades()).tieneDisponibles(b.getIdBoton())){
			controladorDePooglin.activarHabilidad(b.getIdBoton());
		}
		
	}

	

}
