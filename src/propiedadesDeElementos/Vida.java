package propiedadesDeElementos;

public class Vida {
	int cantidadVidas;
	
	public Vida(int cantidadVidas){
		this.cantidadVidas = cantidadVidas;
	}
	
	public int getCantidadVidas(){
		return cantidadVidas;
	}
	
	public void sacarVidas(int vidas){
		if(vidas>=cantidadVidas)
			cantidadVidas=0;
		else
			cantidadVidas = cantidadVidas-vidas;
	}
	
	public boolean hayVida(){
		return (cantidadVidas>0);
	}

}
