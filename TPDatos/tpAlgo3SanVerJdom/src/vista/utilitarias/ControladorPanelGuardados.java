package vista.utilitarias;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.LinkedList;

public class ControladorPanelGuardados {
	
	public LinkedList<String> leerArchivo(){

		  File archivo = null;
	      FileReader fr = null;
	      BufferedReader br = null;
	      LinkedList<String> partidas = new LinkedList<String>();

	      try {
	         // Apertura del fichero y creacion de BufferedReader para poder
	         // hacer una lectura comoda (disponer del metodo readLine()).
	         archivo = new File ("niveles\\partidasGuardadas.txt");
	         fr = new FileReader (archivo);
	         br = new BufferedReader(fr);

	         // Lectura del fichero
	         String linea;
	         while((linea=br.readLine())!=null){
	            System.out.println(linea);
	            partidas.add(linea);	            
	         }
	      }
	      catch(Exception e){
	         e.printStackTrace();
	      }finally{
	         // En el finally cerramos el fichero, para asegurarnos
	         // que se cierra tanto si todo va bien como si salta 
	         // una excepcion.
	         try{                    
	            if( null != fr ){  
	          
	               fr.close();  
	               
	            }                  
	         }catch (Exception e2){ 
	            e2.printStackTrace();
	         }
	      }
		return partidas;
	      
	}
}
