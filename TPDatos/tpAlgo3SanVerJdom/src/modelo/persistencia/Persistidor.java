package modelo.persistencia;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

import org.jdom.Document;
import org.jdom.JDOMException;
import org.jdom.input.SAXBuilder;
import org.jdom.output.XMLOutputter;

public class Persistidor {
	
	public static void guardar(String nombreArchivo, SerializableJDOM que) 
	throws IOException{

		Document docJDOM = new Document (que.serializarJDOM());
		XMLOutputter salidaXML = new XMLOutputter();
		/*Nombre del archivo de salida */
		PrintWriter salida = new PrintWriter (new BufferedWriter(new FileWriter(nombreArchivo)));
		salidaXML.output(docJDOM, salida);
	}

	public static void recuperar(String nombreArchivo, SerializableJDOM que) 
	{


		SAXBuilder fabrica = new SAXBuilder();
		Document docJDOM = null;
		try {
			docJDOM = fabrica.build(new File(nombreArchivo));
			
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
		que.hidratarJDOM(docJDOM.getRootElement());

	}

}


