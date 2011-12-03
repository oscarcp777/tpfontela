package ar.uba.fi.ia.controlador;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.OutputStream;
import java.io.PrintStream;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;
import java.util.StringTokenizer;

import javax.swing.DefaultListModel;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.filechooser.FileFilter;

import ar.uba.fi.ia.modelo.KohonenNetwork;
import ar.uba.fi.ia.modelo.SampleData;
import ar.uba.fi.ia.vista.FiltroImagenes;
import ar.uba.fi.ia.vista.CuadriculaGrafico;
import ar.uba.fi.ia.vista.VentanaPrincipal;

public class Controler {
	   static final String PATH = "files/";
	   static final String NOMBRE_ARCH = "datos";
	    private  SymAction symAction;
	    SymListSelection symListSelection;
	   public SymAction getSymAction() {
			return symAction;
		}

		public void setSymAction(SymAction symAction) {
			this.symAction = symAction;
		}

	public Controler(VentanaPrincipal ventanaPrincipal) {
		super();
		this.ventanaPrincipal = ventanaPrincipal;
		symAction= new SymAction();
		symListSelection= new SymListSelection();
	}

	public SymListSelection getSymListSelection() {
		return symListSelection;
	}

	VentanaPrincipal ventanaPrincipal;
	public class SymAction implements java.awt.event.ActionListener {
		public void actionPerformed(java.awt.event.ActionEvent event)
		{
			Object object = event.getSource();
			if ( object == ventanaPrincipal.getDownSample() )
				downSample_actionPerformed(event);
			else if ( object == ventanaPrincipal.getClear() )
				clear_actionPerformed(event);
			else if ( object ==ventanaPrincipal.getAdd() )
				add_actionPerformed(event,ventanaPrincipal.getLetterListModel());
			else if ( object == ventanaPrincipal.getDel() )
				del_actionPerformed(event);
			else if ( object == ventanaPrincipal.getLoad() ){
				load_actionPerformed(event, ventanaPrincipal.getLetterListModel(),NOMBRE_ARCH+".dat");
			}
			else if ( object == ventanaPrincipal.getSave() )
				save_actionPerformed(event,NOMBRE_ARCH+".dat",ventanaPrincipal.getLetterListModel());
			else if ( object == ventanaPrincipal.getTrain() )
				ventanaPrincipal.train_actionPerformed(event);
			else if ( object == ventanaPrincipal.getRecognize() )
				recognize_actionPerformed(event);
			else if ( object == ventanaPrincipal.getNext() )
				next_actionPerformed(event);
		}
	}
	 /**
	    * Called to downsample the image.
	    *
	    * @param event The event
	    */
	   void downSample_actionPerformed(java.awt.event.ActionEvent event)
	   {
		   ventanaPrincipal.getEntry().downSample();

	   }

	  

	   /**
	    * Called to add the current image to the training set
	    *
	    * @param event The event
	    */
	   void add_actionPerformed(java.awt.event.ActionEvent event, DefaultListModel letterListModel)
	   {
	  

	     String letter = JOptionPane.showInputDialog(
	       "Por favor ingrese el nombre del numero o simbolos (coma,punto) de la imagen: ");
	     if ( letter==null )
	       return;

	     ventanaPrincipal.getEntry().downSample();
	     for (Iterator<CuadriculaGrafico> iterator = ventanaPrincipal.getEntry().getSamples().iterator(); iterator.hasNext();) {
			CuadriculaGrafico sample = (CuadriculaGrafico) iterator.next();
			SampleData sampleData = (SampleData)sample.getData().clone();
		    sampleData.setLetter(letter);
		    letterListModel.add(letterListModel.size(),sampleData);
		}



	     ventanaPrincipal.getLetters().setSelectedIndex(letterListModel.getSize()-1);
	     ventanaPrincipal.getEntry().clear();
	     ventanaPrincipal.getCurrentSample().repaint();

	   }

	   /**
	    * Called when the del button is pressed.
	    *
	    * @param event The event.
	    */
	   void del_actionPerformed(java.awt.event.ActionEvent event)
	   {
	     int i =  ventanaPrincipal.getLetters().getSelectedIndex();

	     if ( i==-1 ) {
	       JOptionPane.showMessageDialog(ventanaPrincipal,
	                                     "Por favor seleccione la figura a borrar.","Error",
	                                     JOptionPane.ERROR_MESSAGE);
	       return;
	     }

	     ventanaPrincipal.getLetterListModel().remove(i);
	   }

	public   class SymListSelection implements javax.swing.event.ListSelectionListener {
	     public void valueChanged(javax.swing.event.ListSelectionEvent event)
	     {
	       Object object = event.getSource();
	       if ( object ==  ventanaPrincipal.getLetters() )
	         letters_valueChanged(event);
	     }
	   }

	   /**
	    * Called when a letter is selected from the list box.
	    *
	    * @param event The event
	    */
	   void letters_valueChanged(javax.swing.event.ListSelectionEvent event)
	   {
	     if (  ventanaPrincipal.getLetters().getSelectedIndex()==-1 )
	       return;
	     SampleData selected =
	       (SampleData) ventanaPrincipal.getLetterListModel().getElementAt( ventanaPrincipal.getLetters().getSelectedIndex());
	     ventanaPrincipal.getCurrentSample().setData((SampleData)selected.clone());
	     ventanaPrincipal.getCurrentSample().repaint();
	     ventanaPrincipal.getEntry().clear();

	   }

	  
	 /**
	    * Called when the load button is pressed.
	    *
	    * @param event The event
	    */
	   void load_actionPerformed(java.awt.event.ActionEvent event, DefaultListModel letterListModel,String arch)
	   {
	     try {
	       FileReader f;// the actual file stream
	       BufferedReader r;// used to read the file line by line
	       f = new FileReader( new File(PATH+arch) );
	       r = new BufferedReader(f);
	       String line;
	       int i=0;

	       letterListModel.clear();

	       while ( (line=r.readLine()) !=null ) {
	    	   StringTokenizer tokenizer= new StringTokenizer(line,":");
	    	  
	         SampleData ds =new SampleData(tokenizer.nextToken(),VentanaPrincipal.DOWNSAMPLE_WIDTH,VentanaPrincipal.DOWNSAMPLE_HEIGHT); 
	    	   String serieBits=tokenizer.nextToken();
	         letterListModel.add(i++,ds);
	         int idx=0;
	         for ( int y=0;y<ds.getHeight();y++ ) {
	           for ( int x=0;x<ds.getWidth();x++ ) {
	             ds.setData(x,y,serieBits.charAt(idx++)=='1');
	           }
	         }
	       }

	       r.close();
	       f.close();
	       clear_actionPerformed(null);
	       JOptionPane.showMessageDialog(ventanaPrincipal,
	                                     "Cargando de '"+arch+"'.","Training",
	                                     JOptionPane.PLAIN_MESSAGE);

	     } catch ( Exception e ) {
	    	 e.printStackTrace();
	       JOptionPane.showMessageDialog(ventanaPrincipal,
	                                     "Error: " + e,"Training",
	                                     JOptionPane.ERROR_MESSAGE);
	     }

	   }

	   /**
	    * Called when the save button is clicked.
	    *
	    * @param event The event
	    */
	   void save_actionPerformed(java.awt.event.ActionEvent event,String arch,DefaultListModel letterListModel)
	   {
	     try {
	       OutputStream os;// the actual file stream
	       PrintStream ps;// used to read the file line by line
	       os = new FileOutputStream( PATH+arch,false );
	       ps = new PrintStream(os);

	       for ( int i=0;i<letterListModel.size();i++ ) {
	         SampleData ds = (SampleData)letterListModel.elementAt(i);
	         ps.print( ds.getLetter() + ":" );
	         for ( int y=0;y<ds.getHeight();y++ ) {
	           for ( int x=0;x<ds.getWidth();x++ ) {
	             ps.print( ds.getData(x,y)?"1":"0" );
	           }
	         }
	         ps.println("");
	       }

	       ps.close();
	       os.close();
	       clear_actionPerformed(null);
	       JOptionPane.showMessageDialog(ventanaPrincipal,
	                                     "Guardado en  '"+arch+"' .",
	                                     "Training",
	                                     JOptionPane.PLAIN_MESSAGE);

	     } catch ( Exception e ) {
	    	 e.printStackTrace();
	       JOptionPane.showMessageDialog(ventanaPrincipal,"Error: " +
	                                     e,"Training",
	                                     JOptionPane.ERROR_MESSAGE);
	     }

	   }
	   public ActionListener getImageSelectAction()
	   {
	       return new ActionListener()
	       {

	           public void actionPerformed(ActionEvent e)
	           {
	               JFileChooser chooser = new JFileChooser(new File("/home/oscar/workspace/TPInteligencia/TP Inteligencia//imagenes/importes/"));
	               chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
	               Set<String> filters= new HashSet<String>();
	               filters.add("jpg");
	               filters.add("png");
	               filters.add("PNG");
	               filters.add("JPG");
	               FileFilter filter1 = new FiltroImagenes(filters);
	               chooser.setFileFilter(filter1);
	               int returnVal = chooser.showOpenDialog(null);
	               if (returnVal == JFileChooser.APPROVE_OPTION)
	               {
	                   ventanaPrincipal.getEntry().initImage(chooser.getSelectedFile());
	               }
	           }
	       };
	   }
	 
	   
	   /**
	    * Called when the next button is pressed.
	    *
	    * @param event The event.
	    */
	   void next_actionPerformed(java.awt.event.ActionEvent event)
	   {
		   if(ventanaPrincipal.getIndex().intValue()<ventanaPrincipal.getSamples().size()){
		  CuadriculaGrafico currentSample= ventanaPrincipal.getSamples().get(ventanaPrincipal.getIndex());
		  currentSample.setBounds(520,350,250,250);
		  System.out.println(currentSample.hashCode());
		  ventanaPrincipal.getContentPane().add(currentSample);
		  currentSample.repaint();
		  ventanaPrincipal.incrementarIndex();
		   }else{
			   ventanaPrincipal.setIndex(0);
		   }
		   
	     }

	   /**
	    * Called when the recognize button is pressed.
	    *
	    * @param event The event.
	    */
	   void recognize_actionPerformed(java.awt.event.ActionEvent event)
	   {
		   ventanaPrincipal.initSamples();
		   ventanaPrincipal.setIndex(1);
	     if ( ventanaPrincipal.getNet()==null ) {
	       JOptionPane.showMessageDialog(ventanaPrincipal,
	                                     "Se necesita entrenar primero la red !","Error",
	                                     JOptionPane.ERROR_MESSAGE);
	       return;
	     }
	     ventanaPrincipal.getEntry().downSample();
	     String finalNumber = "";
	     for (Iterator<CuadriculaGrafico> iterator = ventanaPrincipal.getSamples().iterator(); iterator.hasNext();) {
	    	 CuadriculaGrafico sample = (CuadriculaGrafico) iterator.next();
	    	 double input[] = new double[VentanaPrincipal.DOWNSAMPLE_WIDTH*VentanaPrincipal.DOWNSAMPLE_HEIGHT];
	    	 int idx=0;
	    	 SampleData ds = sample.getData();
	    	 for ( int y=0;y<ds.getHeight();y++ ) {
	    		 for ( int x=0;x<ds.getWidth();x++ ) {
	    			 input[idx++] = ds.getData(x,y)?.5:-.5;
	    		 }
	    	 }

	    	 double normfac[] = new double[1];
	    	 double synth[] = new double[1];
	    	 int best = ventanaPrincipal.getNet().winner ( input , normfac , synth ) ;
	    	 String map[];
	    	 map = mapNeurons(ventanaPrincipal.getLetterListModel(),ventanaPrincipal.getNet());
	   	 
	    	finalNumber+=map[best];
	    	 //   clear_actionPerformed(null);
	     }
	     JOptionPane.showMessageDialog(ventanaPrincipal,
				 "  El numero es: " + finalNumber,"Resultado",
						 JOptionPane.PLAIN_MESSAGE);
	    
	   }
	   /**
	    * Used to map neurons to actual letters.
	    *
	    * @return The current mapping between neurons and letters as an array.
	    */
	   String []mapNeurons( DefaultListModel letterListModel, KohonenNetwork net)
	   {
		   String map[] = new String[letterListModel.size()];
	     double normfac[] = new double[1];
	     double synth[] = new double[1];

	     for ( int i=0;i<map.length;i++ )
	       map[i]="?";
	     for ( int i=0;i<letterListModel.size();i++ ) {
	    	 double input[] = new double[VentanaPrincipal.DOWNSAMPLE_WIDTH*VentanaPrincipal.DOWNSAMPLE_HEIGHT];
	       int idx=0;
	       SampleData ds = (SampleData)letterListModel.getElementAt(i);
	       for ( int y=0;y<ds.getHeight();y++ ) {
	         for ( int x=0;x<ds.getWidth();x++ ) {
	           input[idx++] = ds.getData(x,y)?.5:-.5;
	         }
	       }

	       int best = net.winner ( input , normfac , synth ) ;
	       map[best] = ds.getLetter();
	     }
	     return map;
	   }


	   /**
	    * Called to clear the image.
	    *
	    * @param event The event
	    */
	   void clear_actionPerformed(java.awt.event.ActionEvent event)
	   {
	     ventanaPrincipal.getEntry().clear();
	     ventanaPrincipal.initSamples();
	     ventanaPrincipal.getCurrentSample().repaint();

	   }
}
