package controlador;

import modelo.pooglins.Posicion;

public class PooglinPosicion {

private MarcoPosicion miMarco;
private Posicion miPosicion;
private int idPooglin;

public PooglinPosicion(int idPooglin, Posicion pos) {
	this.idPooglin = idPooglin;
	this.miPosicion = pos;
	this.miMarco = new MarcoPosicion(pos);
}

public int getIdPooglin() {
	return idPooglin;
}


public boolean estaDentro(Posicion pos){
	return this.miMarco.estaDentro(pos);
}

public void setNuevaPosicion(Posicion pos) {
	// TODO Auto-generated method stub
	this.miPosicion = pos;
	this.miMarco = new MarcoPosicion(pos);
	
}

public Posicion getPosicion() {
	// TODO Auto-generated method stub
	return this.miPosicion;
}

}
