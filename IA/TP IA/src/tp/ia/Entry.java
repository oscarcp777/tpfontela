package tp.ia;

import java.awt.AWTEvent;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.RenderingHints;
import java.awt.event.MouseEvent;
import java.awt.geom.Line2D;
import java.awt.image.BufferedImage;
import java.awt.image.PixelGrabber;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import javax.imageio.ImageIO;
import javax.swing.JPanel;

/**
 * Java Neural Network Example
 * Handwriting Recognition
 * by Jeff Heaton (http://www.jeffheaton.com) 1-2002
 * -------------------------------------------------
 * This class is used to provide a small component that
 * the user can draw handwritten letters into. This class
 * also contains the routines necessary to crop and downsample
 * the written character.
 *
 * @author Jeff Heaton (http://www.jeffheaton.com)
 * @version 1.0
 */
public class Entry extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * The image that the user is drawing into.
	 */
	protected Image entryImage;
	private final static BasicStroke grosor1 = new BasicStroke(3.5f); //thickness
	/**
	 * A graphics handle to the image that the
	 * user is drawing into.
	 */
	protected Graphics entryGraphics;

	/**
	 * The last x that the user was drawing at.
	 */
	protected int lastX = -1;

	/**
	 * The last y that the user was drawing at.
	 */
	protected int lastY = -1;

	/**
	 * The list of down sample component used with this
	 * component.
	 */
	protected List<Sample> samples;

	/**
	 * Specifies the left boundary of the cropping
	 * rectangle.
	 */
	protected List<Integer> downSampleLeft;

	/**
	 * Specifies the right boundary of the cropping
	 * rectangle.
	 */
	protected List<Integer> downSampleRight;

	/**
	 * Specifies the top boundary of the cropping
	 * rectangle.
	 */
	protected List<Integer> downSampleTop;

	/**
	 * Specifies the bottom boundary of the cropping
	 * rectangle.
	 */
	protected List<Integer> downSampleBottom;

	/**
	 * The downsample ratio for x.
	 */
	protected double ratioX;

	/**
	 * The downsample ratio for y
	 */
	protected double ratioY;

	/**
	 * The pixel map of what the user has drawn.
	 * Used to downsample it.
	 */
	protected int pixelMap[];

	private int width;

	private int height;


	/**
	 * The constructor.
	 */
	Entry()
	{
		enableEvents(AWTEvent.MOUSE_MOTION_EVENT_MASK|
				AWTEvent.MOUSE_EVENT_MASK|
				AWTEvent.COMPONENT_EVENT_MASK);
		downSampleLeft = new ArrayList<Integer>();
		downSampleRight = new ArrayList<Integer>();
		downSampleTop = new ArrayList<Integer>();
		downSampleBottom = new ArrayList<Integer>();
		downSampleLeft.add(0);
		downSampleRight.add(0);
		downSampleTop.add(0);
		downSampleBottom.add(0);

	}


	/**
	 * Setup the internal image that the user
	 * draws onto.
	 * @throws IOException 
	 */
	protected void initImage(File file) 
	{
		height=getHeight();
		width=getWidth();
		System.out.println(width+"---ancho -------alto-----"+height);
		//     entryImage = createImage(getWidth(),getHeight());
		try {
			BufferedImage originalImage =ImageIO.read(file);
			int type = originalImage.getType() == 0? BufferedImage.TYPE_INT_ARGB : originalImage.getType();
			entryImage=resizeImage(originalImage, height, width, type);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		 
		
		entryGraphics = entryImage.getGraphics();
		entryGraphics.setColor(Color.white);
		//     entryGraphics.fillRect(0,0,ancho,alto);
		repaint();
	}
	private static BufferedImage resizeImage(BufferedImage originalImage,int height,int width, int type){
		BufferedImage resizedImage = new BufferedImage(width, height, BufferedImage.TYPE_BYTE_BINARY);
		Graphics2D g = resizedImage.createGraphics();
		g.drawImage(originalImage, 0, 0, width, height, null);
		g.dispose();
	
		return resizedImage;
	}
	 /**
	   * Setup the internal image that the user draws onto.
	   */
	  protected void initImage()
	  {
	    entryImage = createImage(getBounds().width, getBounds().height);
	    entryGraphics = entryImage.getGraphics();
	    entryGraphics.setColor(Color.white);
	    entryGraphics.fillRect(0, 0, getBounds().width, getBounds().height);
	  }
	/**
	 * Paint the drawn image and cropping box
	 * (if active).
	 *
	 * @param g The graphics context
	 */
	public void paint(Graphics g)
	{
	 if (entryImage == null)
		      initImage();
		g.drawImage(entryImage,0,0,this);
		g.setColor(Color.black);
		g.drawRect(0,0,getWidth(),getHeight());
		
		g.setColor(Color.red);
		for (int i = 0; i < samples.size(); i++) {
			if (downSampleLeft.size()>0)
				g.drawRect(downSampleLeft.get(i),downSampleTop.get(i),
						   downSampleRight.get(i)-downSampleLeft.get(i),
						   downSampleBottom.get(i)-downSampleTop.get(i)); 
//			System.out.println("-----------------------------------------");
//			System.out.println("downSampleLeft "+downSampleLeft.get(i));
//			System.out.println("downSampleTop "+downSampleTop.get(i));
//			System.out.println("downSampleRight: "+(downSampleRight.get(i)-downSampleLeft.get(i)));
//			System.out.println("downSampleBottom : "+(downSampleBottom.get(i)-downSampleTop.get(i)));
//			System.out.println("area ocupada : "+(downSampleRight.get(i)-downSampleLeft.get(i))*(downSampleBottom.get(i)-downSampleTop.get(i)));
		}


	}

	/**
	 * Process messages.
	 *
	 * @param e The event.
	 */
	protected void processMouseEvent(MouseEvent e)
	{
		if ( e.getID()!=MouseEvent.MOUSE_PRESSED )
			return;
		lastX = e.getX();
		lastY = e.getY();
	}

	/**
	 * Process messages.
	 *
	 * @param e The event.
	 */
	protected void processMouseMotionEvent(MouseEvent e)
	{
		if ( e.getID()!=MouseEvent.MOUSE_DRAGGED )
			return;

		entryGraphics.setColor(Color.black);
		
		Graphics2D grafico = (Graphics2D) entryGraphics;
		grafico.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		grafico.setStroke(grosor1);
		grafico.draw(new Line2D.Double(lastX,lastY,e.getX(),e.getY()));
//		entryGraphics.drawLine(lastX,lastY,e.getX(),e.getY());
//		entryGraphics.drawLine(lastX,lastY,e.getX()+1,e.getY()+1);
//		entryGraphics.drawLine(lastX,lastY,e.getX()-1,e.getY()-1);
		getGraphics().drawImage(entryImage,0,0,this);
		lastX = e.getX();
		lastY = e.getY();
	}

	/**
	 * Set the samples control to use. The
	 * samples control displays a downsampled
	 * version of the characters.
	 *
	 * @param s
	 */
	public void setSamples(List<Sample> s)
	{
		samples = s;
	}

	/**
	 * Get the down sample components to be used
	 * with this component.
	 *
	 * @return The down sample component.
	 */
	public List<Sample> getSamples()
	{
		return samples;
	}

	/**
	 * This method is called internally to
	 * see if there are any pixels in the given
	 * scan line. This method is used to perform
	 * autocropping.
	 *
	 * @param y The horizontal line to scan.
	 * @param start When start the horizontal line
	 * @param end When ends the horizontal line
	 * @return True if there were any pixels in this
	 * horizontal line.
	 */
	protected boolean hLineClear(int y, int start, int end)
	{
		int w = entryImage.getWidth(this);
		for ( int i=start;i<end;i++ ) {
			if ( pixelMap[(y*w)+i] !=-1 )
				return false;
		}
		return true;
	}

	/**
	 * This method is called to determine ....
	 *
	 * @param x The vertical line to scan.
	 * @return True if there are any pixels in the
	 * specified vertical line.
	 */
	protected boolean vLineClear(int x)
	{
		int w = entryImage.getWidth(this);
		int h = entryImage.getHeight(this);
		for ( int i=0;i<h;i++ ) {
			if ( pixelMap[(i*w)+x] !=-1 )
				return false;
		}
		return true;
	}

	// this.entryGraphics.setColor(Color.white);
	// this.entryGraphics.fillRect(0,0,getWidth(),getHeight());
	// this.downSampleBottom.clear();
	// this.downSampleTop.clear();
	// this.downSampleLeft.clear();
	// this.downSampleRight.clear();
	// this.downSampleLeft.add(0);
	// this.downSampleRight.add(0);
	// this.downSampleTop.add(0);
	// this.downSampleBottom.add(0);
	// repaint();
	protected List<Integer> findStartsSamples(int w, int h){
		List<Integer> result = new ArrayList<Integer>();
		Boolean isSample = false;
		result.add(0);
		// left line
		for ( int x=0;x<w;x++ ) {
			Boolean lineClear = vLineClear(x);	 
			if(lineClear && isSample) {
				result.add(x);
				isSample=false;
			}
			if(!lineClear)
				isSample = true;
		}
		return result;
	}

	/**
	 * This method is called to automatically
	 * crop the image so that whitespace is
	 * removed.
	 *
	 * @param w The width of the image
	 * @param h The height of the image
	 */
	protected int findBounds(int w,int h)
	{
		List<Integer> starts = findStartsSamples(w,h);

		for (int j = 0; j < starts.size()-1; j++) {

			// top line
			for ( int y=0;y<h;y++ ) {
				if ( !hLineClear(y, starts.get(j), starts.get(j+1)) ) {
					downSampleTop.add(j, y);
					break;
				}
			}
			// bottom line
			for ( int y=h-1;y>=0;y-- ) {
				if ( !hLineClear(y, starts.get(j), starts.get(j+1)) ) {
					downSampleBottom.add(j, y);
					break;
				}
			}
			// left line
			for ( int x=starts.get(j);x<starts.get(j+1);x++ ) {
				if ( !vLineClear(x) ) {
					downSampleLeft.add(j, x);
					break;
				}
			}

			// right line
			for ( int x=starts.get(j+1)-1;x>=starts.get(j);x-- ) {
				if ( !vLineClear(x) ) {
					downSampleRight.add(j, x);
					break;
				}
			}
		}
		return starts.size()-1;
	}

	/**
	 * Called to downsample a quadrant of the image.
	 *
	 * @param x The x coordinate of the resulting
	 * downsample.
	 * @param y The y coordinate of the resulting
	 * downsample.
	 * @return Returns true if there were ANY pixels
	 * in the specified quadrant.
	 */
	protected boolean downSampleQuadrant(int x,int y, int i)
	{
		int w = entryImage.getWidth(this);
		int startX = (int)(downSampleLeft.get(i)+(x*ratioX));
		int startY = (int)(downSampleTop.get(i)+(y*ratioY));
		int endX = (int)(startX + ratioX);
		int endY = (int)(startY + ratioY);

		for ( int yy=startY;yy<=endY;yy++ ) {
			for ( int xx=startX;xx<=endX;xx++ ) {
				int loc = xx+(yy*w);

				if ( pixelMap[ loc  ]!= -1 )
					return true;
			}
		}

		return false;
	}

     private int limpiarSamplesInvalidos(int nSamples){
    	 Integer rihgt,left,top,bottom;
    	 double ancho,alto;
    	 int samplesValidos=nSamples;
    	 List<Integer> invalidosRihgt= new ArrayList<Integer>();
    	 List<Integer> invalidosleft= new ArrayList<Integer>();
    	 List<Integer> invalidostop= new ArrayList<Integer>();
    	 List<Integer> invalidosbottom= new ArrayList<Integer>();
    	 
    	 for (int i = 0; i < nSamples; i++) {
    		 rihgt=downSampleRight.get(i);
    		 left=downSampleLeft.get(i);
    		 top=downSampleTop.get(i);
    		 bottom=downSampleBottom.get(i);
 			 ancho = (double)(rihgt-left)/(double)samples.get(0).getData().getWidth();
 			alto = (double)(bottom-top)/(double)samples.get(0).getData().getHeight();
			System.out.println(i+" 1 ratioX "+(downSampleRight.get(i)-downSampleLeft.get(i))+" ratioY "+(downSampleBottom.get(i)-downSampleTop.get(i)));
 			System.out.println(" 1 area "+alto*ancho);
 			if(alto*ancho<0.2){
				invalidosRihgt.add(rihgt);
				invalidosleft.add(left);
				invalidostop.add(top);
				invalidosbottom.add(bottom);
				samplesValidos--;
			}
    	 }
    		downSampleRight.removeAll(invalidosRihgt);
			downSampleLeft.removeAll(invalidosleft);
			downSampleBottom.removeAll(invalidosbottom);
			downSampleTop.removeAll(invalidostop);
		
    	 for (int i = 0; i < samplesValidos; i++) {
 			ancho = (double)(downSampleRight.get(i)-downSampleLeft.get(i));//(double)samples.get(0).getData().getWidth();
 			alto = (double)(downSampleBottom.get(i)-downSampleTop.get(i));//(double)samples.get(0).getData().getHeight();
 			System.out.println(i+" _ratioX "+ancho+" ratioY "+alto);
 			System.out.println(" area "+alto*ancho);

    	 }
    	 return samplesValidos;
     }
	/**
	 * Called to downsample the image and store
	 * it in the down sample component.
	 */
	public void downSample()
	{
		int w = entryImage.getWidth(this);
		int h = entryImage.getHeight(this);
		PixelGrabber grabber = new PixelGrabber(entryImage,0,0,	w,h,true);
		try {

			grabber.grabPixels();
			pixelMap = (int[])grabber.getPixels();
			int nSamples = findBounds(w,h);
			nSamples=limpiarSamplesInvalidos(nSamples);
			for (int i = 0; i < nSamples; i++) {

				if (i>0){
					Sample newSample = new Sample(samples.get(0).getData().getWidth(),samples.get(0).getData().getHeight());
					newSample.setBounds(samples.get(0).getX(),samples.get(0).getY(),samples.get(0).getWidth(),samples.get(0).getHeight());
					samples.add(newSample);
				}

				SampleData data = samples.get(i).getData();
				ratioX = (double)(downSampleRight.get(i)-
						downSampleLeft.get(i))/(double)data.getWidth();
				ratioY = (double)(downSampleBottom.get(i)-
						downSampleTop.get(i))/(double)data.getHeight();
              
				for ( int y=0;y<data.getHeight();y++ ) {
					for ( int x=0;x<data.getWidth();x++ ) {
						if ( downSampleQuadrant(x,y,i) )
							data.setData(x,y,true);
						else
							data.setData(x,y,false);
					}
				}
				
			}

			samples.get(0).repaint();
			repaint();
		} catch ( InterruptedException e ) {
			e.printStackTrace();
		}
	}

	/**
	 * Called to clear the image.
	 */
	public void clear()
	{
		this.entryGraphics.setColor(Color.white);
		this.entryGraphics.fillRect(0,0,getWidth(),getHeight());
		this.downSampleBottom.clear();
		this.downSampleTop.clear();
		this.downSampleLeft.clear();
		this.downSampleRight.clear();
		this.downSampleLeft.add(0);
		this.downSampleRight.add(0);
		this.downSampleTop.add(0);
		this.downSampleBottom.add(0);
		repaint();
	}
}