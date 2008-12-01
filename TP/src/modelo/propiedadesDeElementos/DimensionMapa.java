package modelo.propiedadesDeElementos;

public class DimensionMapa {
	private int dimX;
	private int dimY;
	
	public DimensionMapa(){
		
	}
	
	public DimensionMapa(int dimX,int dimY){
		this.dimX = dimX;
		this.dimY = dimY;
	}
	
	public int getDimX(){
		return dimX;
	}
	
	public int getDimY(){
		return dimY;
	}
}
