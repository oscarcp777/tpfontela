package habilidadesPooglins;

import propiedadesDeElementos.Posicion;
import mapaDeJuego.Mapa;
import utilitarios.Constants;
import elementosDelMapa.Aire;
import elementosDelMapa.Poogling;
import elementosDelMapa.Terreno;

public class Congelamiento extends Habilidad{

	public Congelamiento() {
		estadoHabilidad = new EstadoHabilidad();
		estadoHabilidad.activarHabilidad();
	}

	@Override
	public void aplicarApooglin(Mapa mapa, Poogling poogling,Terreno terreno) {
		// TODO Auto-generated method stub
		/*le quita vidas al pooglin (lo mata)y en esa 
		 * posicion se debe reemplazar el bloque de 
		 * aire (porque alli hay un pooglin) por un 
		 * bloque de hielo*/
		poogling.quitarVida();
		 
	}

	@Override
	public String getNombre() {
		// TODO Auto-generated method stub
		return Constants.NombreHabilidades.CONGELAMIENTO;
	}

	@Override
	public void aplicarAterreno(Mapa mapa, Terreno terreno, Poogling poogling) {
		if(poogling.obtenerPosicion().compareTo(terreno.obtenerPosicion())==Constants.ValorComparador.IGUAL){//si la posicion del pooglin coincide con la del terreno
		Aire aire = (Aire)terreno;																			 //es porque esta sobre aire.		
		aire.cambiarPorHielo(mapa);
		}
	}

	
}
