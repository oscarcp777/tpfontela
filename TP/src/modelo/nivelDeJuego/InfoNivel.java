package modelo.nivelDeJuego;



import java.util.Iterator;
import java.util.List;

import modelo.elementosDelMapa.Poogling;
import modelo.fabricaTerrenos.MapeoTerrenos;
import modelo.habilidadesPooglins.ContenedorHabilidades;
import modelo.mapeoDirecciones.MapaSingletonsDirecciones;
import modelo.movimientoPooglins.Movimiento;
import modelo.movimientoPooglins.PasosEnDireccion;
import modelo.propiedadesDeElementos.Posicion;
import modelo.propiedadesDeElementos.Vida;
import modelo.xml.DatosDimensionMapa;
import modelo.xml.DatosNave;
import modelo.xml.DatosPooglins;

public class InfoNivel {
	private Posicion posicionNaveEscape;
	private Posicion posicionNaveIngreso;
	private ColPooglins colPooglinsNaveIngreso;
	private ColPooglins colPooglinsNaveEscape;
	private ColTerreno colTerreno;
	private ColHabilidades colHabilidades;
	private Dimension dimension;



	public ColPooglins getColPooglinsNaveEscape() {
		return colPooglinsNaveEscape;
	}

	public void setColPooglinsNaveEscape(ColPooglins colPooglinsNaveEscape) {
		this.colPooglinsNaveEscape = colPooglinsNaveEscape;
	}

	public ColPooglins getColPooglinsNaveIngreso() {
		return colPooglinsNaveIngreso;
	}

	public void setColPooglinsNaveIngreso(ColPooglins colPooglinsNaveIngreso) {
		this.colPooglinsNaveIngreso = colPooglinsNaveIngreso;
	}

	public void setDimension(Dimension dimension) {
		this.dimension = dimension;
	}

	/** LEVANTA ESTA INFO DE UN XML **/
	
	public InfoNivel(){
		
	}

	public InfoNivel(DatosNave datosNaveIngreso, DatosNave datosNaveEscape, List listaDatosTerrenos, List listaNombresHabilidades, DatosDimensionMapa datosDimensionMapa){
	
		cargarColPooglinsYposNaveIngreso(datosNaveIngreso);
		cargarColPooglinsYposNaveEscape(datosNaveEscape);
		cargarColTerrenos(listaDatosTerrenos);
		cargarColHabilidades(listaNombresHabilidades);
		cargarDimensionMapa(datosDimensionMapa);
	}
	
	private void cargarDimensionMapa(DatosDimensionMapa datos) {
		// TODO Auto-generated method stub
		dimension = new Dimension(Integer.parseInt(datos.getMaxX()),Integer.parseInt(datos.getMaxY()));
	}

	//METODOS QUE SE USAN PARA CARGAR LA INFORMACION RECIBIDA DEL ARCHIVO XML NIVEL
	
	//carga los pooglins en una lista de pooglins, y tambien se guarda la posicion de la 
	//nave de ingreso
	private void cargarColPooglinsYposNaveIngreso(DatosNave datosNaveIngreso){
		colPooglinsNaveIngreso = new ColPooglins();
	posicionNaveIngreso = new Posicion(Integer.parseInt(datosNaveIngreso.getCoordenadaX()),Integer.parseInt(datosNaveIngreso.getCoordenadaY()));	

	for(Iterator it=datosNaveIngreso.getPooglins().iterator();it.hasNext();){
		DatosPooglins datosPoogling = (DatosPooglins)it.next();
		Poogling poogling = new Poogling(new Posicion(Integer.parseInt(datosPoogling.getPosicionX()),Integer.parseInt(datosPoogling.getPosicionY())),new Vida(Integer.parseInt(datosPoogling.getVida())));
		
		Movimiento movimiento = new Movimiento();
		PasosEnDireccion pasosEnDireccion = new PasosEnDireccion();
		
		pasosEnDireccion.setContar(Boolean.parseBoolean(datosPoogling.getContar()));
		pasosEnDireccion.setQuietoEnDireccion(Boolean.parseBoolean(datosPoogling.getQuietoEnDireccion()));
		pasosEnDireccion.darPasosEnDireccion(Integer.parseInt(datosPoogling.getCantidadDePasos()));
		
		movimiento.setPosicion(new Posicion(Integer.parseInt(datosPoogling.getPosicionX()),Integer.parseInt(datosPoogling.getPosicionY())));
		movimiento.setPasosEnDireccion(pasosEnDireccion);
		movimiento.setDireccion(MapaSingletonsDirecciones.getInstance().obtenerDireccion(datosPoogling.getDireccionMovimiento()));
		
		poogling.setMovimiento(movimiento);
		colPooglinsNaveIngreso.agregarPosicionable(poogling);
	}
		
		
	}
	
	//nave de escape
	private void cargarColPooglinsYposNaveEscape(DatosNave datosNaveEscape){
		colPooglinsNaveEscape = new ColPooglins();
		posicionNaveEscape = new Posicion(Integer.parseInt(datosNaveEscape.getCoordenadaX()),Integer.parseInt(datosNaveEscape.getCoordenadaY()));	

		for(Iterator it=datosNaveEscape.getPooglins().iterator();it.hasNext();){
			DatosPooglins datosPoogling = (DatosPooglins)it.next();
			Poogling poogling = new Poogling(new Posicion(Integer.parseInt(datosPoogling.getPosicionX()),Integer.parseInt(datosPoogling.getPosicionY())),new Vida(Integer.parseInt(datosPoogling.getVida())));
			
			Movimiento movimiento = new Movimiento();
			PasosEnDireccion pasosEnDireccion = new PasosEnDireccion();
			
			pasosEnDireccion.setContar(Boolean.parseBoolean(datosPoogling.getContar()));
			pasosEnDireccion.setQuietoEnDireccion(Boolean.parseBoolean(datosPoogling.getQuietoEnDireccion()));
			pasosEnDireccion.darPasosEnDireccion(Integer.parseInt(datosPoogling.getCantidadDePasos()));
			
			movimiento.setPosicion(new Posicion(Integer.parseInt(datosPoogling.getPosicionX()),Integer.parseInt(datosPoogling.getPosicionY())));
			movimiento.setPasosEnDireccion(pasosEnDireccion);
			movimiento.setDireccion(MapaSingletonsDirecciones.getInstance().obtenerDireccion(datosPoogling.getDireccionMovimiento()));
			
			poogling.setMovimiento(movimiento);
			colPooglinsNaveEscape.agregarPosicionable(poogling);
		}	
	}
		
	//se carga la coleccion de terrenos
	private void cargarColTerrenos(List listaDatosTerrenos){
		MapeoTerrenos.getInstance().cargarMapaTerrenos(listaDatosTerrenos);
		colTerreno = new ColTerreno(MapeoTerrenos.getInstance().obtenerColeccionTerrenos());
	}
	
	//se carga la coleccion de habilidades
	private void cargarColHabilidades(List listaNombresHabilidades){
		ContenedorHabilidades.getInstance().cargarMapaHabilidades(listaNombresHabilidades);
		colHabilidades = new ColHabilidades(ContenedorHabilidades.getInstance().obtenerColeccionHabilidades());
	}


	//GETTERS Y SETTERS
	
	public Posicion getPosicionNaveIngreso() {
		return posicionNaveIngreso;
	}

	public void setPosicionNaveIngreso(Posicion posicionNaveIngreso) {
		this.posicionNaveIngreso = posicionNaveIngreso;
	}

	public Posicion getPosicionNaveEscape() {
		return posicionNaveEscape;
	}

	public void setPosicionNaveEscape(Posicion posicionNaveEscape) {
		this.posicionNaveEscape = posicionNaveEscape;
	}

	public ColTerreno getColTerreno() {
		return colTerreno;
	}

	public void setColTerreno(ColTerreno colTerreno) {
		this.colTerreno = colTerreno;
	}

	public ColHabilidades getColHabilidades() {
		return colHabilidades;
	}

	public void setColHabilidades(ColHabilidades colHabilidades) {
		this.colHabilidades = colHabilidades;
	}

	public Dimension getDimension() {
		return dimension;
	}

	
		
		
}
