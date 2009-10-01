package vista.componentes;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.image.BufferedImage;

import javax.swing.JComponent;
import javax.swing.JLabel;
import vista.PruebaFlujoVentanas;
import modelo.pooglins.Posicion;
public class TableroPuntuacion extends JComponent{

	private Integer tiempo;
	/*private int ganadores;
	private int perdedores;*/
	private JLabel labelTiempo;
	private JLabel titulo;
/*	private BufferedImage labelGanadores;
	private BufferedImage labelPerdedores;*/

public TableroPuntuacion(Posicion posicion, int tiempoInicial){
	this.tiempo = tiempoInicial;
	this.setBounds(posicion.getX(),posicion.getY(),130,70);

	this.titulo = new JLabel("Tiempo Restante");
	this.titulo.setBounds(2,2,130,40);
	this.titulo.setForeground(Color.GREEN);
	this.titulo.setHorizontalAlignment(JLabel.CENTER);
	this.titulo.setFont(new Font("Times New Roman",Font.BOLD,16));
		
	this.labelTiempo = new JLabel(this.armarVisualizacionTiempo());
	this.labelTiempo.setBounds(35,40,60,20);
	this.labelTiempo.setForeground(Color.GREEN);
	this.labelTiempo.setHorizontalAlignment(JLabel.CENTER);
	this.labelTiempo.setFont(new Font("Times New Roman",Font.BOLD,20));
	
	
}
private String armarVisualizacionTiempo(){
	Integer minutos = this.tiempo/60;
	Integer segundos = this.tiempo%60;
	String minutosS = new String();
	String segundosS = new String();
	
	if (minutos <10){
		minutosS = "0"+minutos.toString();
	}else{
		minutosS = minutos.toString();
	}
	if (segundos <10){
		segundosS = "0"+segundos.toString();
	}else{
		segundosS = segundos.toString();
	}
	
	
	return new String(minutosS+":"+segundosS);
	
}

@Override
public void paint(Graphics g) {
	// TODO Auto-generated method stub
	BufferedImage b = new BufferedImage(this.getWidth(),this.getHeight(),BufferedImage.BITMASK); 
	BufferedImage b2 = new BufferedImage(this.titulo.getWidth(),this.titulo.getHeight(),BufferedImage.BITMASK);
	BufferedImage b1 = new BufferedImage(this.labelTiempo.getWidth(),this.labelTiempo.getHeight(),BufferedImage.BITMASK);
	this.labelTiempo.paint(b1.getGraphics());
	this.titulo.paint(b2.getGraphics());
	b.getGraphics().drawImage(b1, this.labelTiempo.getX(), this.labelTiempo.getY(), null);
	b.getGraphics().drawImage(b2, this.titulo.getX(), this.titulo.getY(), null);
	g.drawImage(b, this.getX(), this.getY(), null);
}

public void correrContador() {
	// TODO Auto-generated method stub
	while(tiempo >= 0 && PruebaFlujoVentanas.flujo != null){
		if (!PruebaFlujoVentanas.flujo.estoyPausado()) {
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			this.tiempo--;
			this.labelTiempo.setText(this.armarVisualizacionTiempo());
		}
	}
	if (PruebaFlujoVentanas.flujo != null) PruebaFlujoVentanas.flujo.finDelTiempo();
}
}
