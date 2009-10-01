package vista.componentes;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JComponent;

import vista.utilitarias.ConstantesVista;
import vista.utilitarias.ConversorDeEscalas;
import vista.utilitarias.ImagenesParcela;

import modelo.constantes.Constantes;
import modelo.entornoDeJuego.EstadoParcela;
import modelo.pooglins.Posicion;


@SuppressWarnings("serial")
public class TerrenoNivel extends JComponent {
	
	private BufferedImage buffer;

	
	public TerrenoNivel(List<EstadoParcela> listaParcelas, int x, int y){
		Posicion p = ConversorDeEscalas.ajustarEscala(new Posicion(x,y));
		this.setSize(new Dimension(p.getX(),p.getY()));
		buffer = new BufferedImage(p.getX(),p.getY(),BufferedImage.BITMASK);
		this.setBackground(null);
		//buffer.coerceData(true);
		
		Iterator<EstadoParcela> i = listaParcelas.iterator();
		
		while (i.hasNext()) {
			EstadoParcela est = i.next();
			Posicion pos = ConversorDeEscalas.ajustarEscala(new Posicion(est.getPosX(),est.getPosY()));
			SpriteSimple sprite = ImagenesParcela.getInstance().getImagen(est.getTipoMaterial());
			if(est.getTipoMaterial() == Constantes.PUERTA_ENTRADA || est.getTipoMaterial() == Constantes.PUERTA_SALIDA){
			    this.buffer.getGraphics().drawImage(sprite.getImage(), pos.getX(),pos.getY()-15, null);
			}
			else this.buffer.getGraphics().drawImage(sprite.getImage(), pos.getX(),pos.getY(), null);
				
		}		
	}

	public BufferedImage getImagen(){
		return this.buffer;
	}
	public void paint(Graphics g) {
		// TODO Auto-generated method stub
		g.drawImage(this.buffer, 0, 0, null);
	}
	public void dibujarParcela(Posicion posicion, int idParcela){
		SpriteSimple sprite = ImagenesParcela.getInstance().getImagen(idParcela);
		this.buffer.getGraphics().clearRect(posicion.getX(),posicion.getY(), ConstantesVista.ANCHO_PARCELA, ConstantesVista.ALTO_PARCELA);
		this.buffer.getGraphics().drawImage(sprite.getImage(), posicion.getX(),posicion.getY(), null);
	}
	
	
}
