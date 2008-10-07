package TipoPosicion;

import Utilidades.Constants;

public class Velocidad {
	private int velocidad;
	
	public Velocidad(){
		
	}
	
	public void velocidadNormal(){
		this.velocidad=Constants.TipoVelocidad.VELOCIDAD_NORMAL;
	}
	
	public void velocidadMedia(){
		this.velocidad=Constants.TipoVelocidad.VELOCIDAD_MEDIA;
	}
	
	public void velocidadRapida(){
		this.velocidad=Constants.TipoVelocidad.VELOCIDAD_RAPIDA;
	}
	
	public void velocidadMuyRapida(){
		this.velocidad=Constants.TipoVelocidad.VELOCIDAD_MUYRAPIDA;
	}
	
	public int getVelocidad(){
		return this.velocidad;
	}
	
}
