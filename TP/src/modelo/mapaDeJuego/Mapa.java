package modelo.mapaDeJuego;


import java.util.Collection;
import java.util.Iterator;
import java.util.Set;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import modelo.elementosDelMapa.Nave;
import modelo.elementosDelMapa.Poogling;
import modelo.elementosDelMapa.Terreno;
import modelo.habilidadesPooglins.Habilidad;
import modelo.nivelDeJuego.ColHabilidades;
import modelo.nivelDeJuego.ColPooglins;
import modelo.nivelDeJuego.ColTerreno;
import modelo.nivelDeJuego.Dimension;
import modelo.nivelDeJuego.InfoNivel;
import modelo.propiedadesDeElementos.Posicion;
import modelo.utilitarios.Constants;





public class Mapa {
	
	private ColTerreno colTerreno;
	private ColHabilidades colHabilidades;
	private MapaTerreno mapaTerreno;
	private Nave naveIngreso;
	private Nave naveEscape;
	private Dimension dimension;

	public Nave getNaveEscape() {
		return naveEscape;
	}

	public Nave getNaveIngreso() {
		return naveIngreso;
	}

	public Mapa(InfoNivel infoNivel){
		//En este constructor se cargan los atributos del mapa de acuerdo a la informacion recibida por el planeta,
		//que seria nuestro nivel de juego.
			 
		colTerreno = infoNivel.getColTerreno();
		colHabilidades = infoNivel.getColHabilidades();
		mapaTerreno = new MapaTerreno();
		naveIngreso = new Nave (infoNivel.getPosicionNaveIngreso());
	    naveEscape = new Nave(infoNivel.getPosicionNaveEscape());
	    naveEscape.cargarPooglings(infoNivel.getColPooglinsNaveEscape());
	    naveIngreso.cargarPooglings(infoNivel.getColPooglinsNaveIngreso());
	    this.dimension = infoNivel.getDimension();
	}
	/*
	public void agregarTerreno(Terreno terreno){
		mapaTerreno.agregarTerreno(terreno);
	}
	*/
	public ColPooglins obtenerPooglinsNaveIngreso(){
		return naveIngreso.obtenerPooglings();
	}
	
	public ColPooglins obtenerPooglinsNaveEscape(){
		return naveEscape.obtenerPooglings();
	}
	
	public Posicion obtenerPosicionNaveIngreso(){
		return naveIngreso.obtenerPosicion();
	}
	
	public Posicion obtenerPosicionNaveEscape(){
		return naveEscape.obtenerPosicion();
	}
	
	public boolean llegoPooglinANaveEscape(Poogling poogling){
		if (poogling.obtenerPosicion().compareTo(this.naveEscape.obtenerPosicion())==Constants.ValorComparador.IGUAL)
		return true;
		else 
			return false;
	}
	
	public void subirPooglinNaveEscape(Poogling pooglin){
		//Cuando las posiciones coinciden el pooglin se sube a la nave
		//para pasar al 2do nivel
		naveEscape.colisionarPoogling(pooglin);
	}
	
	public void cargarTerrenoDeJuego(){
		for(Iterator itColTerreno=colTerreno.iterator();itColTerreno.hasNext();){
			Terreno terreno = (Terreno)itColTerreno.next();
			mapaTerreno.agregarTerreno(terreno);
		}
	}
	
	//Si la clave posicion del terreno se encuentra en el mapa, borra el terreno actual
	//y lo cambia por el terreno que se le pasa por parametro, en caso contrario no hace dicho cambio. 
	public void cambiarTerreno(Terreno terreno){
		
		//Actualizo la coleccion de terrenos.
		if(colTerreno.borrarPosicionable(mapaTerreno.obtenerTerreno(terreno.obtenerPosicion())))
		colTerreno.agregarPosicionable(terreno);
		
		if(mapaTerreno.eliminarTerreno(terreno.obtenerPosicion()))
			mapaTerreno.agregarTerreno(terreno);	
							
	}
	
	public Terreno obtenerTerreno(Posicion posicionKey){
		return (Terreno)mapaTerreno.obtenerTerreno(posicionKey);
	}
	
	private void agregarAcolTerrenoBloqueContiguo(ColTerreno colTerrenoContiguos,Terreno terrenoContiguo){
		if(terrenoContiguo!=null)
			colTerrenoContiguos.agregarPosicionable(terrenoContiguo);
	}
	
	public ColTerreno obtenerBloquesContiguosAlPooglin(Poogling pooglin){
		Posicion posicionActualPooglin = pooglin.obtenerPosicion();
		ColTerreno colTerrenoContiguos = new ColTerreno();
		
		Terreno terrenoArriba=(Terreno)obtenerTerreno(posicionActualPooglin.obtenerPosicionSiguienteArriba());
		Terreno terrenoAbajo=(Terreno)obtenerTerreno(posicionActualPooglin.obtenerPosicionSiguienteAbajo());
		Terreno terrenoDerecha=(Terreno)obtenerTerreno(posicionActualPooglin.obtenerPosicionSiguienteIzquierda());
		Terreno terrenoIzquierda=(Terreno)obtenerTerreno(posicionActualPooglin.obtenerPosicionSiguienteDerecha());
		Terreno terrenoActualPooglin=(Terreno)obtenerTerreno(posicionActualPooglin);
		
		agregarAcolTerrenoBloqueContiguo(colTerrenoContiguos,terrenoArriba);	
		agregarAcolTerrenoBloqueContiguo(colTerrenoContiguos,terrenoAbajo);
		agregarAcolTerrenoBloqueContiguo(colTerrenoContiguos,terrenoDerecha);
		agregarAcolTerrenoBloqueContiguo(colTerrenoContiguos,terrenoIzquierda);
		agregarAcolTerrenoBloqueContiguo(colTerrenoContiguos,terrenoActualPooglin);
	
		return colTerrenoContiguos;
	}
	
	public ColTerreno getColTerreno() {
		return colTerreno;
	}
	
	public Set obtenerPosicionesTerrenos(){
		return mapaTerreno.obtenerClaves();
	}

	public Dimension getDimension() {
		return dimension;
	}

	//mato a todos los pooglins porque se supero el tiempo en que podian estar al aire libre sobre el planeta de juego
	public void matarPooglins(){
		for(Iterator it=naveIngreso.obtenerPooglings().iterator();it.hasNext();){
			Poogling poogling = (Poogling)it.next();
			poogling.sacrificar();
		}
	}
	
	//Este metodo guarda el estado del mapa completo
	//Desde el juego en el momento de la persistencia, llamo a este metodo.
	public Element toXml(Document doc){
		
		Element xmlElemento = doc.createElement("Mapa");
		
		Element xmlElementoTerreno = doc.createElement("Terrenos");
		Element xmlElementoHabilidades = doc.createElement("HabilidadesDisponibles");

		Collection collecionTerrenos = mapaTerreno.obtenerTerrenos();
		
		for(Iterator it = collecionTerrenos.iterator();it.hasNext();)
			xmlElementoTerreno.appendChild(((Terreno)it.next()).toXml(doc));
		
		xmlElemento.appendChild(xmlElementoTerreno);
		xmlElemento.appendChild(naveIngreso.toXml(doc,true));//true porque le paso la nave de ingreso
		xmlElemento.appendChild(naveEscape.toXml(doc,false));//false porque no le estoy pasando la nave de ingreso, sino la de escape
		xmlElemento.appendChild(dimension.toXml(doc));
		
		for(Iterator it = colHabilidades.iterator();it.hasNext();)
			xmlElementoHabilidades.appendChild(((Habilidad)it.next()).toXml(doc)); //guardo las habilidades disponibles que hay en el nivel de juego
		
		xmlElemento.appendChild(xmlElementoHabilidades);
		
		return xmlElemento;
	}
}
