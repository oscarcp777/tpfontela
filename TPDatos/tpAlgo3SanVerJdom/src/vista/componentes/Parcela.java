package vista.componentes;

import java.awt.Graphics;
import java.awt.Image;
import java.awt.Component;
import modelo.pooglins.Posicion;

import vista.utilitarias.ConstantesVista;
import vista.utilitarias.ConversorDeEscalas;
import vista.utilitarias.ImagenesParcela;

public class Parcela extends Component implements Sprite {


	private SpriteSimple sprite;
	
	public Parcela(int idParcela, Posicion posicion) {
		this.setPosicion(posicion);
		ImagenesParcela img = ImagenesParcela.getInstance();
		this.sprite = img.getImagen(idParcela);
		
	}

	public void dibujar(Graphics g) {
		g.drawImage(this.sprite.getImage(),0, 0, null);
		// TODO Auto-generated method stub
	}

	
	@Override
	public void paint(Graphics g) {
		// TODO Auto-generated method stub
		this.dibujar(g);
		
	}

	public Image getImage() {
		// TODO Auto-generated method stub
		return this.sprite.getImage();
	}

	public void setPosicion(Posicion posicionRelativaMapa){
		/* 
		 * La posicion relativa al mapa del modelo no coincide con la posicion de dibujo. Uno arranca en la esquina inferior
		 * derecha y el otro en la esquina superior izquierda.
		 */
			Posicion p = ConversorDeEscalas.ajustarEscala(posicionRelativaMapa);
			this.setLocation(p.getX(), p.getY()); 
		}

	
	
}
