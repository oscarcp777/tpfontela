package modelo.entornoDeJuego;

import org.jdom.Element;

import modelo.constantes.Constantes;
import modelo.persistencia.SerializableJDOM;



/**
 * Clase: MaterialDeTerreno.
 * Utilidad: Permite setear los Atributos de un MaterialDeTerreno, tales como esRompible,
 * 			 esCaminable, esVacio, esMortal, esPuertaDeEntrada y esPuertaDeSalida;
 *           asi como el valor de la altura y el tipo de Material.
 * Utilizada por: BuilderMaterial.
 * 
 * 
 * */
public class MaterialDeTerreno implements SerializableJDOM {
	
	
	private boolean esRompible;
	private boolean esCaminable;
	private boolean esVacio;
	private boolean esMortal;
	private int tipoDeMaterial;
	private int altura;
	private boolean esPuertaDeEntrada;
	private boolean esPuertaDeSalida;
	
	public MaterialDeTerreno(boolean esRompible, boolean esCaminable, boolean esVacio, boolean esMortal, int tipoDeMaterial, int altura){
		this.esRompible = esRompible;
		this.esCaminable = esCaminable;
		this.esVacio = esVacio;
		this.esMortal = esMortal;
		this.tipoDeMaterial = tipoDeMaterial;		
		this.altura = altura;
	}
	
	public MaterialDeTerreno(boolean esRompible, boolean esCaminable, boolean esVacio, boolean esMortal, int tipoDeMaterial){
		this.esRompible = esRompible;
		this.esCaminable = esCaminable;
		this.esVacio = esVacio;
		this.esMortal = esMortal;
		this.tipoDeMaterial = tipoDeMaterial;		
		
	}		
	
	public MaterialDeTerreno(boolean esPuertaDeEntrada, boolean esPuertaDeSalida, int tipoDeMaterial){
		this.esPuertaDeEntrada = esPuertaDeEntrada;
		this.esPuertaDeSalida = esPuertaDeSalida;
		this.tipoDeMaterial = tipoDeMaterial;
		this.esVacio = false;
		this.esCaminable = true;
		this.esRompible = false;
		this.esMortal = false;
		this.altura = 0;
	}

	public int getTipoDeMaterial() {
		return tipoDeMaterial;
	}

	public boolean esRompible(){
		return this.esRompible;
	}
	
	public boolean esCaminable(){
		return this.esCaminable;
	}
	
	public boolean esVacio(){
		return this.esVacio;
	}
	public boolean esMortal(){
		return this.esMortal;
	}

	public boolean esEscalable(){
		return this.tipoDeMaterial == Constantes.RAMPA_DERECHA || this.tipoDeMaterial == Constantes.RAMPA_IZQUIERDA
			|| this.tipoDeMaterial == Constantes.TUNEL_DERECHA || this.tipoDeMaterial == Constantes.TUNEL_IZQUIERDA;
		
	}
	
	public boolean esPared(){
		return Constantes.PARED == this.tipoDeMaterial;
	}
	
	public boolean esPooglinsCongelado(){
		return Constantes.POOGLINS_CONGELADO == this.tipoDeMaterial;
	}
	public boolean esFuego(){
		return this.esMortal;
	}
	
	public boolean esPuertaDeEntrada(){
		return this.esPuertaDeEntrada;
	}
	
	public boolean esPuertaDeSalida(){
		return this.esPuertaDeSalida;
	}

	public int getAltura() {
		return altura;
	}

	@Override
	public String toString() {
		return ((Integer)this.tipoDeMaterial).toString();
	}
	
	public boolean esRampaIzquierda(){
		return Constantes.RAMPA_IZQUIERDA == this.tipoDeMaterial || Constantes.TUNEL_IZQUIERDA == this.tipoDeMaterial;
	}
	
	public boolean esRampaDerecha(){
		return Constantes.RAMPA_DERECHA == this.tipoDeMaterial  || Constantes.TUNEL_DERECHA == this.tipoDeMaterial;
	}

	public boolean esHielo() {
		// TODO Auto-generated method stub
		return (this.getTipoDeMaterial() == Constantes.HIELO);
	}

	public boolean esPiso() {
		
		return (this.getTipoDeMaterial() == Constantes.PISO);
	}

	public void setMortal() {
		// TODO Auto-generated method stub
		this.esMortal = true;
	}
	
	public Element serializarJDOM() {
		Element raiz = new Element("MaterialDeTerreno");
		raiz.setAttribute("esRompible", new Boolean(this.esRompible).toString());
		raiz.setAttribute("esCaminable", new Boolean(this.esCaminable).toString());
		raiz.setAttribute("esVacio", new Boolean(this.esVacio).toString());
		raiz.setAttribute("esMortal", new Boolean(this.esMortal).toString());
		raiz.setAttribute("tipoDeMaterial", new Integer(this.tipoDeMaterial).toString());
		raiz.setAttribute("altura", new Integer(this.altura).toString());
		raiz.setAttribute("esPuertaDeEntrada", new Boolean(this.esPuertaDeEntrada).toString());
		raiz.setAttribute("esPuertaDeSalida", new Boolean(this.esPuertaDeSalida).toString());
		raiz.setText("\n");
		return raiz;
	}
	
	public void hidratarJDOM(Element desde) {
		this.esRompible = Boolean.parseBoolean(desde.getAttributeValue("esRompible"));
		this.esCaminable = Boolean.parseBoolean(desde.getAttributeValue("esCaminable"));
		this.esVacio = Boolean.parseBoolean(desde.getAttributeValue("esVacio"));
		this.esMortal = Boolean.parseBoolean(desde.getAttributeValue("esMortal"));
		this.tipoDeMaterial = Integer.parseInt(desde.getAttributeValue("tipoDeMaterial"));
		this.altura = Integer.parseInt(desde.getAttributeValue("altura"));
		this.esPuertaDeEntrada = Boolean.parseBoolean(desde.getAttributeValue("esPuertaDeEntrada"));
		this.esPuertaDeSalida = Boolean.parseBoolean(desde.getAttributeValue("esPuertaDeSalida"));
		
	}




}
