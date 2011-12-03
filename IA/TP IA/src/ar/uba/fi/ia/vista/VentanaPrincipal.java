package ar.uba.fi.ia.vista;


import java.awt.Font;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.SwingUtilities;

import ar.uba.fi.ia.controlador.Controler;
import ar.uba.fi.ia.controlador.Controler.SymAction;
import ar.uba.fi.ia.controlador.Controler.SymListSelection;
import ar.uba.fi.ia.modelo.KohonenNetwork;
import ar.uba.fi.ia.modelo.SampleData;
import ar.uba.fi.ia.modelo.TrainingSet;


/**
 * 
 * @author oscar
 *
 */
public class VentanaPrincipal extends JFrame implements Runnable {

   /**
	 * 
	 */
	private static final long serialVersionUID = 1L;

/**
    * The downsample width for the application.
    */
   public static final int DOWNSAMPLE_WIDTH = 30;//20

    Integer index=1;
   public void setIndex(Integer index) {
		this.index = index;
	}




/**
    * The down sample height for the application.
    */
   public static final int DOWNSAMPLE_HEIGHT = 50;//20

   Controler controler;
   /**
    * The entry component for the user to draw into.
    */
   Grafico entry;
   /**
    * The current down sample component to display the drawing
    * downsampled.
    */
   CuadriculaGrafico currentSample;
   
   /**
    * A list of samples
    */
   List<CuadriculaGrafico> samples;
   
   /**
    * The iterator of samples
    */
   Iterator<CuadriculaGrafico> sampleIterator;

   /**
    * The figures that have been defined.
    */
   DefaultListModel letterListModel = new DefaultListModel();
   
   /**
    * The figures that have been defined in the second network.
    */
//   DefaultListModel letterListModelOptimized = new DefaultListModel();

   /**
    * The neural network.
    */
   KohonenNetwork net;
   
   /**
    * The second neural network.
    */
//   KohonenNetwork netOptimized;

   /**
    * The background thread used for training.
    */
   Thread trainThread = null;
   static final int X_BOTONES = 270;
   static final int X_BOTONES_I = 12;
   static final int Y_BOTONES_I = 380;
   static final int Y_BOTONES = 400;
   static final int ANCHO_BOTONES = 240;
   static final int ANCHO_BOTONES_I = 140;
   static final int ALTO_BOTONES = 35;
 //{{DECLARE_CONTROLS
   javax.swing.JLabel JLabel1 = new javax.swing.JLabel();
   javax.swing.JLabel JLabel2 = new javax.swing.JLabel();
   JButton selectImage = new JButton();
   /**
    * THe downsample button.
    */
   javax.swing.JButton downSample = new javax.swing.JButton();

   /**
    * The add button.
    */
   javax.swing.JButton add = new javax.swing.JButton();

   /**
    * The clear button
    */
   javax.swing.JButton clear = new javax.swing.JButton();

   /**
    * The recognize button
    */
   javax.swing.JButton recognize = new javax.swing.JButton();
   javax.swing.JScrollPane JScrollPane1 = new javax.swing.JScrollPane();

   /**
    * The letters list box
    */
   javax.swing.JList letters = new javax.swing.JList();

   /**
    * The delete button
    */
   javax.swing.JButton del = new javax.swing.JButton();

   /**
    * The load button
    */
   javax.swing.JButton load = new javax.swing.JButton();

   /**
    * The save button
    */
   javax.swing.JButton save = new javax.swing.JButton();

   /**
    * The train button
    */
   javax.swing.JButton train = new javax.swing.JButton();
   javax.swing.JLabel JLabel3 = new javax.swing.JLabel();
   javax.swing.JLabel JLabel4 = new javax.swing.JLabel();
   
   /**
    * The test button
    */
   javax.swing.JButton test = new javax.swing.JButton();
   javax.swing.JLabel JLabel6 = new javax.swing.JLabel();

   /**
    * How many tries
    */
   javax.swing.JLabel tries = new javax.swing.JLabel();

   /**
    * The last error
    */
   javax.swing.JLabel lastError = new javax.swing.JLabel();

   /**
    * The best error
    */
   javax.swing.JLabel bestError = new javax.swing.JLabel();
   javax.swing.JLabel JLabel8 = new javax.swing.JLabel();
   javax.swing.JLabel JLabel5 = new javax.swing.JLabel();
   
   /**
    * The next button
    */
   javax.swing.JButton next = new javax.swing.JButton();

   /**
    * The constructor.
    */
  
VentanaPrincipal()
   {
	 controler= new Controler(this);
     getContentPane().setLayout(null);
     entry = new Grafico();
//     entry.reshape(250,25,200,200);
     entry.setBounds(X_BOTONES,25,500,310);
     getContentPane().add(entry);

     initSamples();

     //{{INIT_CONTROLS
     setTitle("Java Neural Network");
     getContentPane().setLayout(null);
     setSize(800,650);
     setVisible(false);
     JLabel1.setText("Figuras reconocidas");
     getContentPane().add(JLabel1);
     JLabel1.setBounds(X_BOTONES_I,12,200,12);
     selectImage.setText("Cargar Imagen");
     selectImage.addActionListener(controler.getImageSelectAction());
     selectImage.setBounds(X_BOTONES,Y_BOTONES-40,ANCHO_BOTONES,ALTO_BOTONES);
     getContentPane().add(selectImage);
     downSample.setText("Mostrar ejemplo en mapa");
     downSample.setActionCommand("Down Sample");
     getContentPane().add(downSample);
     downSample.setBounds(X_BOTONES,Y_BOTONES+40,ANCHO_BOTONES,ALTO_BOTONES);
     add.setText("Agregar");
     add.setActionCommand("Add");
     getContentPane().add(add);
     add.setBounds(X_BOTONES,Y_BOTONES+80,ANCHO_BOTONES,ALTO_BOTONES);
     clear.setText("Limpiar");
     clear.setActionCommand("Clear");
     getContentPane().add(clear);
     clear.setBounds(X_BOTONES,Y_BOTONES+120,ANCHO_BOTONES,ALTO_BOTONES);
     recognize.setText("Reconocer");
     recognize.setActionCommand("Recognize");
     getContentPane().add(recognize);
     recognize.setBounds(X_BOTONES,Y_BOTONES,ANCHO_BOTONES,ALTO_BOTONES);

     next.setText("Siguiente.");
     next.setActionCommand("Next");
     getContentPane().add(next);
     next.setBounds(X_BOTONES,Y_BOTONES+160,ANCHO_BOTONES,ALTO_BOTONES);

     JScrollPane1.setVerticalScrollBarPolicy(
       javax.swing.ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
     JScrollPane1.setOpaque(true);
     getContentPane().add(JScrollPane1);
     JScrollPane1.setBounds(X_BOTONES_I,24,250,350);
     JScrollPane1.getViewport().add(letters);
     letters.setBounds(0,0,126,129);
     del.setText("Borrar");
     del.setActionCommand("Delete");
     getContentPane().add(del);
     del.setBounds(X_BOTONES_I,Y_BOTONES_I+40,ANCHO_BOTONES_I+100,ALTO_BOTONES);
     load.setText("Cargar");
     load.setActionCommand("Load");
     getContentPane().add(load);
     load.setBounds(X_BOTONES_I,Y_BOTONES_I,ANCHO_BOTONES_I-10,ALTO_BOTONES);
     save.setText("Guardar");
     save.setActionCommand("Save");
     getContentPane().add(save);
     save.setBounds(X_BOTONES_I+110,Y_BOTONES_I,ANCHO_BOTONES_I-10,ALTO_BOTONES);
     train.setText("Empezar entrenamiento");
     train.setActionCommand("Begin Training");
     getContentPane().add(train);
     train.setBounds(X_BOTONES_I,Y_BOTONES_I+80,ANCHO_BOTONES_I+100,ALTO_BOTONES);
     JLabel2.setText("Tries:");
     getContentPane().add(JLabel2);
     JLabel2.setBounds(X_BOTONES_I,Y_BOTONES_I+152,ANCHO_BOTONES_I,24);
     tries.setText("0");
     getContentPane().add(tries);
     tries.setBounds(X_BOTONES_I+100,Y_BOTONES_I+152,ANCHO_BOTONES_I,24);
     JLabel3.setText("Ultimo Error:");
     getContentPane().add(JLabel3);
     JLabel3.setBounds(X_BOTONES_I,Y_BOTONES_I+200,ANCHO_BOTONES_I,24);
     lastError.setText("0");
     getContentPane().add(lastError);
     lastError.setBounds(X_BOTONES_I+100,Y_BOTONES_I+200,ANCHO_BOTONES_I,24);
     JLabel4.setText("Mejor Error:");
     getContentPane().add(JLabel4);
     JLabel4.setBounds(X_BOTONES_I,Y_BOTONES_I+176,ANCHO_BOTONES_I,24);
     bestError.setText("0");
     getContentPane().add(bestError);
     bestError.setBounds(X_BOTONES_I+100,Y_BOTONES_I+176,ANCHO_BOTONES_I,24);

     JLabel8.setHorizontalTextPosition(
    		 javax.swing.SwingConstants.CENTER);
     JLabel8.setHorizontalAlignment(
       javax.swing.SwingConstants.CENTER);
     JLabel8.setText("Resultados del entrenamiento");
     getContentPane().add(JLabel8);
     JLabel8.setFont(new Font("Dialog", Font.BOLD, 14));
     JLabel8.setBounds(X_BOTONES_I,Y_BOTONES_I+125,ANCHO_BOTONES_I+100,24);
     JLabel5.setText("Imagen a reconocer :");
     getContentPane().add(JLabel5);
     JLabel5.setBounds(X_BOTONES,12,200,12);
     //}}

     //{{REGISTER_LISTENERS
     SymAction lSymAction = controler.getSymAction();
     downSample.addActionListener(lSymAction);
     clear.addActionListener(lSymAction);
     add.addActionListener(lSymAction);
     del.addActionListener(lSymAction);
     next.addActionListener(lSymAction);
     SymListSelection lSymListSelection = controler.getSymListSelection();
     letters.addListSelectionListener(lSymListSelection);
     load.addActionListener(lSymAction);
     save.addActionListener(lSymAction);
     train.addActionListener(lSymAction);
     recognize.addActionListener(lSymAction);
     test.addActionListener(lSymAction);
     //}}
     letters.setModel(letterListModel);
     //{{INIT_MENUS
     //}}
   }


   public void initSamples(){
	   	 samples = new ArrayList<CuadriculaGrafico>();
	     sampleIterator = samples.iterator();
	     currentSample = new CuadriculaGrafico(DOWNSAMPLE_WIDTH,DOWNSAMPLE_HEIGHT);
	     currentSample.setBounds(520,350,250,250);
	     samples.add(currentSample);
	     entry.setSamples(samples);
	     getContentPane().add(currentSample);
   }

 


   

   

   /**
    * Called when the train button is pressed.
    *
    * @param event The event.
    */
   public void train_actionPerformed(java.awt.event.ActionEvent event)
   {
     if ( trainThread==null ) {
       train.setText("Parar entrenamiento");
       train.repaint();
       trainThread = new Thread(this);
       trainThread.start();
     } else {
       net.halt=true;
//       netOptimized.halt=true;
     }
   }
   /**
    * Run method for the background training thread.
    */
   public void run()
   {
	   net= entrenar( letterListModel,1);
//	   netOptimized=entrenar( letterListModelOptimized,2);
   }
public KohonenNetwork entrenar( DefaultListModel letterListModel,int numeroDeRed){
	KohonenNetwork net = null;
    try {
      int inputNeuron = VentanaPrincipal.DOWNSAMPLE_HEIGHT*
        VentanaPrincipal.DOWNSAMPLE_WIDTH;
      int outputNeuron = letterListModel.size();

      TrainingSet set = new TrainingSet(inputNeuron,outputNeuron);
      set.setTrainingSetCount(letterListModel.size());

      for ( int t=0;t<letterListModel.size();t++ ) {
        int idx=0;
        SampleData ds = (SampleData)letterListModel.getElementAt(t);
        for ( int y=0;y<ds.getHeight();y++ ) {
          for ( int x=0;x<ds.getWidth();x++ ) {
            set.setInput(t,idx++,ds.getData(x,y)?.5:-.5);
          }
        }
      }

      net = new KohonenNetwork(inputNeuron,outputNeuron,this);
      net.setTrainingSet(set);
      net.learn();
    } catch ( Exception e ) {
   	 e.printStackTrace();
      JOptionPane.showMessageDialog(this,"Error: " + e,
                                    "Entrenando",
                                    JOptionPane.ERROR_MESSAGE);
    }
   return net;
  
}
   /**
    * Called to update the stats, from the neural network.
    *
    * @param trial How many tries.
    * @param error The current error.
    * @param best The best error.
    */
   public void updateStats(long trial,double error,double best,KohonenNetwork net)
   {
     if ( (((trial%100)!=0) || (trial==10)) && !net.halt )
       return;

     if ( net.halt ) {
       trainThread = null;
       train.setText("Empezar el entrenamiento");
       JOptionPane.showMessageDialog(this,
                                     "Ha terminado el entrenamiento de la red ","Entrenando",
                                     JOptionPane.PLAIN_MESSAGE);
     }
     UpdateStats stats = new UpdateStats();
     stats._tries = trial;
     stats._lastError=error;
     stats._bestError=best;
     try {
       SwingUtilities.invokeAndWait(stats);
     } catch ( Exception e ) {
    	 e.printStackTrace();
       JOptionPane.showMessageDialog(this,"Error: " + e,"Training",
                                     JOptionPane.ERROR_MESSAGE);
     }
   }

  
   
  

  
   public class UpdateStats implements Runnable {
     long _tries;
     double _lastError;
     double _bestError;

     public void run()
     {
       tries.setText(""+_tries);
       lastError.setText(""+_lastError*100+" %");
       bestError.setText(""+_bestError*100+" %");
     }
   }

public Integer getIndex() {
	return index;
}
public Controler getControler() {
	return controler;
}
public Grafico getEntry() {
	return entry;
}
public CuadriculaGrafico getCurrentSample() {
	return currentSample;
}
public List<CuadriculaGrafico> getSamples() {
	return samples;
}
public Iterator<CuadriculaGrafico> getSampleIterator() {
	return sampleIterator;
}
public DefaultListModel getLetterListModel() {
	return letterListModel;
}
public KohonenNetwork getNet() {
	return net;
}
public Thread getTrainThread() {
	return trainThread;
}
public javax.swing.JLabel getJLabel1() {
	return JLabel1;
}
public javax.swing.JLabel getJLabel2() {
	return JLabel2;
}
public JButton getSelectImage() {
	return selectImage;
}
public javax.swing.JButton getDownSample() {
	return downSample;
}
public javax.swing.JButton getAdd() {
	return add;
}
public javax.swing.JButton getClear() {
	return clear;
}
public javax.swing.JButton getRecognize() {
	return recognize;
}
public javax.swing.JScrollPane getJScrollPane1() {
	return JScrollPane1;
}
public javax.swing.JList getLetters() {
	return letters;
}
public javax.swing.JButton getDel() {
	return del;
}
public javax.swing.JButton getLoad() {
	return load;
}
public javax.swing.JButton getSave() {
	return save;
}
public javax.swing.JButton getTrain() {
	return train;
}
public javax.swing.JLabel getJLabel3() {
	return JLabel3;
}
public javax.swing.JLabel getJLabel4() {
	return JLabel4;
}
public javax.swing.JButton getTest() {
	return test;
}
public javax.swing.JLabel getJLabel6() {
	return JLabel6;
}
public javax.swing.JLabel getTries() {
	return tries;
}
public javax.swing.JLabel getLastError() {
	return lastError;
}
public javax.swing.JLabel getBestError() {
	return bestError;
}
public javax.swing.JLabel getJLabel8() {
	return JLabel8;
}
public javax.swing.JLabel getJLabel5() {
	return JLabel5;
}
public javax.swing.JButton getNext() {
	return next;
}


public void incrementarIndex() {
	this.index++;
	
}





}