package modelo.persistencia;


import org.jdom.Element;

public interface SerializableJDOM {
	
	public Element serializarJDOM();
	
	public void hidratarJDOM (Element desde);

}
