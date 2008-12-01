package modelo.xml;

import java.io.IOException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import modelo.mapaDeJuego.Mapa;
import modelo.nivelDeJuego.InfoNivel;

import org.apache.xerces.parsers.DOMParser;
import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import com.sun.org.apache.xml.internal.serialize.XMLSerializer;
import com.sun.org.apache.xml.internal.serialize.OutputFormat;
import java.io.FileWriter;

public class XMLguarda {

	public static void guardarPartida(String nombreArch, Mapa mapa) throws IOException, ParserConfigurationException
	{
	    DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
	    DocumentBuilder loader = factory.newDocumentBuilder();
        Document doc = loader.newDocument();

        
        doc.appendChild(mapa.toXml(doc));
        
        XMLSerializer serializer = new XMLSerializer();
        
        OutputFormat outFormato = new OutputFormat();

       
        outFormato.setVersion("1.0");
        outFormato.setIndenting(true);
        outFormato.setIndent(4);
        
        serializer.setOutputFormat(outFormato);
        serializer.setOutputCharStream(
          new FileWriter(nombreArch));
        serializer.serialize(doc);
	}
	
}
