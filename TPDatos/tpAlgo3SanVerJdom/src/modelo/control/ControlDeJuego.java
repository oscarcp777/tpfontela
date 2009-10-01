package modelo.control;

public class ControlDeJuego {
	
	
	public Nivel inicializar(int[][] terrenoDePrueba){
		//EN ESTA CLASE ESTARIAMOS LLAMANDO A UN PARSER QUE LEVANTE A UN XML QUE LEVANTE LOS DATOS DE LA MATRIZ
		//USAREMOS EL CONOCIDO HARDCODEO PARA HACER PRUEBAS  
		Nivel atributos = new Nivel();
		atributos.setAltoTerreno(terrenoDePrueba.length);
		atributos.setAnchoTerreno(terrenoDePrueba[0].length);		
		atributos.setTerreno(terrenoDePrueba);
		atributos.setCantidadDePooglins(1);
		atributos.setTiempo(10000); //IMPLEMENTAR
		
		return atributos;
				
	}
	
}
