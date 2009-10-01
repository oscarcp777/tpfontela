package modelo.control;

import java.util.Iterator;
import java.util.LinkedList;

import modelo.entornoDeJuego.EstadoParcela;
import modelo.entornoDeJuego.EstadoPooglin;
import modelo.persistencia.SerializableJDOM;

import org.jdom.Element;

public class Nivel implements EstadoDeNivelCargable,EstadoDeNivelDescargable, SerializableJDOM{
	
	
	private int[][]terreno; 
	private int cantidadDePooglins;
	private int tiempo;
	private LinkedList<CantidadDeOficios> cantidadDeOficiosPorNivel;
	private int anchoTerreno;
	private int altoTerreno;
	private int porcentajeGanadores;
	
	
	public int getPorcentajeGanadores() {
		return porcentajeGanadores;
	}
	public void setPorcentajeGanadores(int porcentajeGanadores) {
		this.porcentajeGanadores = porcentajeGanadores;
	}
	public int[][] getTerreno() {
		
		return terreno;
	}
	public void setTerreno(int[][] terreno) {
		this.terreno = terreno;
	}
	public int getCantidadDePooglins() {
		return cantidadDePooglins;
	}
	public void setCantidadDePooglins(int cantidadDePooglins) {
		this.cantidadDePooglins = cantidadDePooglins;
	}
	public int getTiempo() {
		return tiempo;
	}
	public void setTiempo(int tiempo) {
		this.tiempo = tiempo;
	}
	public LinkedList<CantidadDeOficios> getCantidadDeOficiosPorNivel() {
		return cantidadDeOficiosPorNivel;
	}
	public void setCantidadDeOficiosPorNivel(
			LinkedList<CantidadDeOficios> cantidadDeOficiosPorNivel) {
		this.cantidadDeOficiosPorNivel = cantidadDeOficiosPorNivel;
	}
	public int getAnchoTerreno() {
		return anchoTerreno;
	}
	public void setAnchoTerreno(int anchoTerreno) {
		this.anchoTerreno = anchoTerreno;
	}
	public int getAltoTerreno() {
		return altoTerreno;
	}
	public void setAltoTerreno(int altoTerreno) {
		this.altoTerreno = altoTerreno;
	}
	@Override
	
	public String toString() {
		// TODO Auto-generated method stub
		String s = null;
		return	s;
		
	}
	
	public Element serializarJDOM() {
		Element raiz = new Element("Nivel");
		raiz.setAttribute("CantidadDePooglins", (new Integer(this.cantidadDePooglins).toString()));
		raiz.setAttribute("Tiempo", new Integer(this.tiempo).toString());
		raiz.setAttribute("AnchoTerreno", new Integer(this.anchoTerreno).toString());
		raiz.setAttribute("AltoTerreno", new Integer(this.altoTerreno).toString());
		raiz.setAttribute("PorcentajeGanadores", new Integer(this.porcentajeGanadores).toString());
		for (int j = 0; j < this.getAltoTerreno(); j++) {
			for (int i = 0; i < this.getAnchoTerreno(); i++) {
				raiz.setAttribute("Terreno-" + j + "-" + i + "-", (new Integer(this.terreno[j][i]).toString()));
			}
		}
		if (this.cantidadDeOficiosPorNivel != null){
		Iterator i = this.cantidadDeOficiosPorNivel.iterator();
		while (i.hasNext()){
			raiz.addContent(((CantidadDeOficios)i.next()).serializarJDOM());
		}
		}
		return raiz;
	}
	
	public void hidratarJDOM(Element desde) {
		this.cantidadDeOficiosPorNivel = new LinkedList<CantidadDeOficios>();
		this.cantidadDePooglins = Integer.parseInt(desde.getAttributeValue("CantidadDePooglins"));
		this.tiempo = Integer.parseInt(desde.getAttributeValue("Tiempo"));
		this.anchoTerreno = Integer.parseInt(desde.getAttributeValue("AnchoTerreno"));
		this.altoTerreno = Integer.parseInt(desde.getAttributeValue("AltoTerreno"));
		this.porcentajeGanadores = Integer.parseInt(desde.getAttributeValue("PorcentajeGanadores"));
		this.terreno = new int[altoTerreno][anchoTerreno];  
		for (int j = 0; j < this.getAltoTerreno(); j++) {
			for (int i = 0; i < this.getAnchoTerreno(); i++) {
				this.terreno[j][i] = new Integer (Integer.parseInt(desde.getAttributeValue("Terreno-" + j + "-" + i + "-")));
			}
		}
		this.cantidadDeOficiosPorNivel.clear();
		Iterator i = desde.getChildren().iterator();
		while (i.hasNext()){
			Element a = (Element)i.next();
			CantidadDeOficios b = new CantidadDeOficios(0,0);
			b.hidratarJDOM(a);
			this.cantidadDeOficiosPorNivel.add(b);
		}
		
	}
	
	
	

}
