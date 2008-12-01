package modelo.xml;

import java.io.FileWriter;
import java.io.IOException;
import java.util.Iterator;


import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.Node;
import org.dom4j.io.SAXReader;
import org.dom4j.io.XMLWriter;
import org.dom4j.io.OutputFormat;

public abstract class ParserXML {

	    public Document parse(String url) throws DocumentException {
	        SAXReader reader = new SAXReader();
	        Document document = reader.read(url);
	        return document;
	    }
	    
	    	            
		/********************************************************************/    
	    public void writeXML(Document document,String filename ) throws IOException
	    {
    	    FileWriter out = new FileWriter( filename );
	    	    OutputFormat format = OutputFormat.createPrettyPrint();
	            XMLWriter writer = new XMLWriter(out,format);
	            writer.write( document );
	            writer.close();
	    }    
	    
	}
	    

