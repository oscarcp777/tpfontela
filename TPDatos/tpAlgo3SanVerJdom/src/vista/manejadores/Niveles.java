package vista.manejadores;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

public class Niveles implements Serializable{
	
	private  int idNivel;
	private  String nombreNivel;
	
	public int getIdNivel() {
		return idNivel;
	}
	public void setIdNivel(int idNivel) {
		this.idNivel = idNivel;
	}
	public String getNombreNivel() {
		return nombreNivel;
	}
	public void setNombreNivel(String nombreNivel) {
		this.nombreNivel = nombreNivel;
	}
	public String toString() {
		return nombreNivel.toString();
	}
	
	public void guardarIdNivel(String nombreArchivo) 
	throws IOException,FileNotFoundException{
		ObjectOutputStream salida= new ObjectOutputStream(new FileOutputStream(nombreArchivo));
		salida.writeObject(this.idNivel);	
	}
	
	public static int recuperarIdNivel(String nombreArchivo) 
	throws Exception{

		ObjectInputStream entrada= new ObjectInputStream(new FileInputStream (nombreArchivo));

		int idNivel = 0;

		idNivel=(Integer)entrada.readObject();
		
		return idNivel;

	}
	
	
	
	

}
