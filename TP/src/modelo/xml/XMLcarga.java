package modelo.xml;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;
import org.dom4j.*;

import modelo.nivelDeJuego.InfoNivel;
import modelo.utilitarios.Constants;



public class XMLcarga {
private String nombreArchivoXml;
	
	private Document document;
	private InfoNivel infoNivel;
		

	public XMLcarga(String nombreArchivoXml){
		this.nombreArchivoXml = nombreArchivoXml; //concateno la ruta donde se encuentra el archivo junto con el nombre del mismo concatenadole la extension
		document=obtenerDocumento();
		infoNivel = new InfoNivel(datosNave(false),datosNave(true),listaStringTerrenos(),listaStringHabilidades(),datosDimensionFrame(),datosNivel());
	}
	
	private Document obtenerDocumento(){
				
		try
		{
			File xml = new File(nombreArchivoXml);
			SAXReader reader = new SAXReader();
			document = reader.read(xml);
					
			//document = reader.read( url );
			//getNodeAttributes(document.node(0));
			//String xPath = "/Root";
		    // List nodes = document.selectNodes(xPath);
		    

		}
		catch (DocumentException e)
		{
			e.printStackTrace();
		}
		return document;

	}
	
	public String datosNivel(){
		Element root = document.getRootElement();
		return (String)root.attributeValue("nivel");
	}
	
	public List listaStringTerrenos(){
		
		Element root = document.getRootElement();
		List nodes = root.elements();
		List listTerrenos = new ArrayList();
		
		Element terrenos = (Element)nodes.get(0);
			
		for(Iterator i = terrenos.elementIterator(); i.hasNext();){
			DatosTerreno datosTerreno = new DatosTerreno();
			Element elem = (Element)i.next();
			datosTerreno.setNombreTerreno(elem.getName());
			List elements = elem.elements();
			datosTerreno.setCoordenadaX(((Element)(elements.get(0))).attributeValue("posicionX")); //obtengo la posicion
			datosTerreno.setCoordenadaY(((Element)(elements.get(0))).attributeValue("posicionY"));
			datosTerreno.setCantVidas(((Element)elements.get(1)).attributeValue("cantidadVidas")); //obtengo la vida
			listTerrenos.add(datosTerreno);
		}
		
		return listTerrenos;
	}

	public List listaStringHabilidades(){
		Element root = document.getRootElement();
		List nodes = root.elements();
		List listHabilidades = new ArrayList();
				
		Element habilidades = (Element)nodes.get(4);
		
			for(Iterator i = habilidades.elementIterator(); i.hasNext();){
				Element elem = (Element)i.next();
				DatosHabilidades datosHabilidades = new DatosHabilidades();
				datosHabilidades.setNombreHabilidad(elem.attributeValue("nombreHabilidad"));
				Element elemEstadoHabilidad = (Element)elem.elements().get(0);
				datosHabilidades.setEstadoHabilidad(elemEstadoHabilidad.attributeValue("activada"));
				listHabilidades.add(datosHabilidades);
			}
			return listHabilidades;	
	}
		
	
	
	public DatosNave datosNave(boolean naveEscape){
		
		Element root = document.getRootElement();
		List nodes = root.elements();
		DatosNave datosNave = new DatosNave();
		List<DatosPooglins> listPooglins = new ArrayList<DatosPooglins>();
	
		Element nave=(Element)nodes.get(1);
		
		if(naveEscape){
			datosNave.setCantidadPooglins(nave.attributeValue("cantidadPooglinsFinal"));
			nave = (Element)nodes.get(2);
		}else
			datosNave.setCantidadPooglins(nave.attributeValue("cantidadPooglinsInicial"));
				
		datosNave.setCoordenadaX(nave.attributeValue("posicionX"));
		datosNave.setCoordenadaY(nave.attributeValue("posicionY"));
		
		
		for(Iterator it=nave.elementIterator();it.hasNext();){
			Element elem = (Element)it.next();
			List elementsPoogling = elem.elements();
			DatosPooglins datosPooglins = new DatosPooglins();
			datosPooglins.setVelocidad(((Element)elementsPoogling.get(0)).attributeValue("velocidad"));
			Element elemMovimiento = (Element)elementsPoogling.get(1);
			Element elemPosicion = (Element)elementsPoogling.get(2);
			datosPooglins.setPosicionX(elemPosicion.attributeValue("posicionX"));
			datosPooglins.setPosicionY(elemPosicion.attributeValue("posicionY"));
			datosPooglins.setDireccionMovimiento(elemMovimiento.attributeValue("direccion"));
			List nodosHijosMov=elemMovimiento.elements();
			datosPooglins.setCantidadDePasos(((Element)nodosHijosMov.get(0)).attributeValue("cantidadDePasos"));
			datosPooglins.setContar(((Element)nodosHijosMov.get(0)).attributeValue("contar"));
			datosPooglins.setQuietoEnDireccion(((Element)nodosHijosMov.get(0)).attributeValue("quietoEnDireccion"));
			datosPooglins.setVida(((Element)elementsPoogling.get(3)).attributeValue("cantidadVidas"));
			if(elementsPoogling.size()==5){//el 5to elemento seria la habilidad si es que la tiene el poogling
			datosPooglins.setNombreHabilidad(((Element)elementsPoogling.get(4)).attributeValue("nombreHabilidad"));
			Element elementEstadoHabilidad=(Element)((Element)elementsPoogling.get(4)).elements().get(0);
			datosPooglins.setNombreHabilidad(elementEstadoHabilidad.attributeValue("activada"));
			}
			listPooglins.add(datosPooglins);
		}
		datosNave.setPooglins(listPooglins);
		return datosNave;
	}
	
	public DatosDimensionMapa datosDimensionFrame(){
		Element root = document.getRootElement();
		List nodes = root.elements();
			
		Element nodoDimension = (Element)nodes.get(3);
		DatosDimensionMapa dimension = new DatosDimensionMapa(nodoDimension.attributeValue("ancho"),nodoDimension.attributeValue("largo"));	
		
		return dimension;
	}
	
	public InfoNivel getInfoNivel() {
		return infoNivel;
	}
	
}
