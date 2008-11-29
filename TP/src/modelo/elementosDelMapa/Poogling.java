
package modelo.elementosDelMapa;

import java.awt.Image;
import java.awt.Toolkit;
import java.util.Iterator;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import modelo.fabricaTerrenos.FabricaTerrenos;
import modelo.fabricaTerrenos.MapeoTerrenos;
import modelo.habilidadesPooglins.ContenedorHabilidades;
import modelo.habilidadesPooglins.Habilidad;
import modelo.mapaDeJuego.Mapa;
import modelo.movimientoPooglins.Direccion;
import modelo.movimientoPooglins.Movimiento;
import modelo.movimientoPooglins.PasosEnDireccion;
import modelo.propiedadesDeElementos.Posicion;
import modelo.propiedadesDeElementos.Posicionable;
import modelo.propiedadesDeElementos.Velocidad;
import modelo.propiedadesDeElementos.Vida;
import modelo.utilitarios.Constants;

public class Poogling extends Posicionable{

	private Habilidad habilidad;
	private Vida vida;
	private Velocidad velocidad;
	private Movimiento movimiento;
	private Image image;
	private boolean llegoAnave;
	
	//Constructor por defecto
	public Poogling(){
		image = Toolkit.getDefaultToolkit().getImage("imagenes/pooglin.gif");
		velocidad=new Velocidad();
	}
	
	public Poogling(Posicion posicionInicial,Vida vida){
		this.asignarPosicion(posicionInicial);
		movimiento = new Movimiento(posicionInicial);
		velocidad=new Velocidad();
		this.vida = vida;
		image = Toolkit.getDefaultToolkit().getImage("imagenes/pooglin.gif");
	}
	
	public Habilidad getHabilidad() {
		return habilidad;
	}

	public void setHabilidad(Habilidad habilidad) {
		this.habilidad = habilidad;
	}
	
	public Velocidad getVelocidad() {
		return velocidad;
	}

	public void setVelocidad(Velocidad velocidad) {
		this.velocidad = velocidad;
	}

	public void darHabilidad(String nombre) {
		this.habilidad = ContenedorHabilidades.getInstance().obtenerHabilidad(nombre);
	}
	
	public void desactivarHabilidad() {
		habilidad.desactivarHabilidad();
	}
	
	private void aplicarHabilidadTerrenoYpooglin(Mapa mapa, Terreno terreno){
		//si la habilidad es distinta de null y si esta activada la aplico
		//si la habilidad es distinta de null y es de tipo tunel, la aplico al poogling
		//aunque este no tenga habilidad, dado que otro poogling ha creado dicho tunel en el juego 
		//y por lo tanto este puede pasar por ahi.
		if (habilidad!=null && habilidad.isActivada()){
			terreno.aplicar(habilidad,mapa,this);
			habilidad.aplicarApooglin(mapa,this,terreno);
		}
	}
		
	//Mueve al pooglin y segun sobre que terreno este parado el mismo
	//cambiara de direccion en que se esta moviendo o se le duplicara 
	//la velocidad o puede llegar a quitarle la vida.
    public boolean mover(Mapa mapa){
    	boolean ret_val=false; //valor de retorno si el pooglin no tiene vida
    	do{             	
		for(Iterator itColTerrenoContiguo=mapa.obtenerBloquesContiguosAlPooglin(this).iterator(); itColTerrenoContiguo.hasNext();){
			Terreno terreno=(Terreno)itColTerrenoContiguo.next();
			aplicarHabilidadTerrenoYpooglin(mapa,terreno); //metodo de pooglin que le aplica la habilidad a si mismo y al terreno
			if(this.isConVida()&&!this.quieto())
			terreno.colisionarPoogling(this);
		}
		
		llegoAnave = mapa.llegoPooglinANaveEscape(this);
				
		if(!llegoAnave && isConVida()){ //Si el pooglin no llego a la nave, seguira moviendose y colisionando con el terreno
			this.asignarPosicion(movimiento.siguientePosicion()); //le pido la siguiente posicion y se la asigno al pooglin 
		ret_val=true;
		}else if(llegoAnave){
			mapa.subirPooglinNaveEscape(this);
			ret_val=false;
		}	
		
    	}while(velocidad.avanzarEnVelocidad()&&ret_val); //si puede seguir avanzando en velocidad y si no subio a la nave o
    	return ret_val;
	}
    /*
    public void cambiarPorAire(Mapa mapa){
    	Terreno terreno = MapeoTerrenos.getInstance().obtenerTerreno(Constants.NombreTerrenos.AIRE);
    	terreno.asignarPosicion(obtenerPosicion());
    	mapa.agregarTerreno(terreno); 
    }
    */
    public boolean isConDireccionAbajo(){
    	return movimiento.isConDireccionAbajo();
    }
    
    /*
     * Me devuelve la posicion en donde estaria el poogling luego de dar x pasos en direccion.
     * Este metodo no le asigna dicha posicion al pooglin, solo retorna la posicion en donde podria llegar a estar
     * dado que habria que ver primero si en dicha posicion hay aire. Lo uso para la habilidad teletransportacion.
     */
    public Posicion avanzarEnDireccion(PasosEnDireccion pasosEnDireccion){
    	return movimiento.darPasosEnDireccion(pasosEnDireccion);
    }
	
    public int cantidadDePasosEnDireccion(){
    	return movimiento.cantidadDePasosEnDireccion();
    }
    
    public void invalidarMovimiento(boolean mover){
    	movimiento.movimientoInvalido(mover);
    }
    
    public boolean quieto(){
    	return movimiento.noCambiaSuPosicion();
    }
    
    public void redireccionar(Direccion direccion){
    	movimiento.cambiarDireccion(direccion);
    }
    
    public void cambiarDireccionDeMovimiento(){
    	movimiento.cambiarDireccion();
    }
    
    public Posicion siguientePosicion(){
    	return movimiento.verSiguientePosicion(obtenerPosicion());
    }
    
    /*
     * Lo uso para la teletransportacion, dado que si el pooglin cambia su posicion porque se la asigno la teletransportacion
     * el metodo actualizarPosicionDeMovimiento actualiza el movimiento con la nueva posicion del poogling teletransportado.
     * El movimiento del poogling lo maneja la clase movimiento, el cual contiene una direccion por la cual sabe en que direccion moverse
     * el poogling.
     */
    public void actualizarPosicionDeMovimiento(Posicion nuevaPosicion){
    	movimiento.setPosicion(nuevaPosicion);
    }
    
	public void quitarVida(){
		vida.sacarVidas(vida.getCantidadVidas());
	}
	
	public boolean isConVida(){
		return vida.hayVida();
	}
	
	public boolean isConHabilidad(){
		return habilidad.isActivada();
	}
	
	public void contarPasos(boolean conteo){
		movimiento.contarPasos(conteo);
	}
	
	public boolean isConDireccion(){
		return movimiento.isConDireccion();
	}

	@Override
	public Image getImage() {
		// TODO Auto-generated method stub
		return image;
	}
	
	public void setImage(Image image){
		this.image = image;
	}
	
	public boolean isLlegoAnave() {
		return llegoAnave;
	}
	
	public void inicializarPasosEnDireccion(){
		movimiento.inicializarPasosEnDireccion();
	}
	
	//para cargar la partida guardada necesito setear el movimiento que tenia
	public void setMovimiento(Movimiento movimiento){
		this.movimiento = movimiento;
	}
	
	public void sacrificar(){
		vida.sacarVidas(vida.getCantidadVidas()); //le saco todas las vidas que tenia
	}
	
	//esto me sirve para el tunel electromagnetico para que no se quede dando vueltas sobre el.
	public boolean veniaEnEsaDireccion(Posicion posicionTerreno){
		return movimiento.veniaEnEsaDireccion(obtenerPosicion(),posicionTerreno); //se lo delego al movimiento que sabe que hacer con esa posicion
	}
	
	public Element toXml(Document doc){
		
		Element xmlElemento = doc.createElement("Poogling");
		
		xmlElemento.appendChild(velocidad.toXml(doc));
		xmlElemento.appendChild(movimiento.toXml(doc));
		xmlElemento.appendChild(obtenerPosicion().toXml(doc));
		xmlElemento.appendChild(vida.toXml(doc));
		
		if (this.habilidad!=null)
		xmlElemento.appendChild(habilidad.toXml(doc));
				
		return xmlElemento;
	}

}
