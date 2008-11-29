package modelo.xml;

public class DatosDimensionMapa {
	private String maxX;
	private String maxY;
	
	public DatosDimensionMapa(String maxX, String maxY){
		this.maxX = maxX;
		this.maxY = maxY;
	}
	
	public String getMaxX(){
		return maxX;
	}
	
	public String getMaxY(){
		return maxY;
	}
}