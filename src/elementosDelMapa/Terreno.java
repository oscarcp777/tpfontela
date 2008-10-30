package elementosDelMapa;

import mapaDeJuego.Mapa;
import propiedadesDeElementos.Colisionable;
import propiedadesDeElementos.Posicionable;
import propiedadesDeElementos.Vida;
import utilitarios.Constants;
import habilidadesPooglins.Habilidad;



public abstract class Terreno extends Posicionable implements Colisionable{
	
	private String nombreTerreno;
	private Vida vida;
	
	//colisiona el poogling contra tierra o roca,
	@Override
	public void colisionarPoogling(Poogling poogling) {
		// TODO Auto-generated method stub
		if(this.obtenerPosicion().compareTo(poogling.siguientePosicion())==
			Constants.ValorComparador.IGUAL) 
		poogling.cambiarDireccionDeMovimiento();
	}
	
	public void setVida(Vida vida) {
		this.vida = vida;
	}

	public Vida getVida() {
		return vida;
	}
	
	public void setNombreTerreno(String nombreTerreno){
		this.nombreTerreno = nombreTerreno;
	}
	
	public String getNombreTerreno(){
		return nombreTerreno;
	}
	
	public void cambiarPorAire(Mapa mapa){
		mapa.cambiarTerreno(new Aire(obtenerPosicion()));
	}

}
