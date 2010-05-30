package tp.robots;

import java.awt.Font;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.OutputStream;
import java.io.PrintStream;
import java.util.StringTokenizer;

import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.SwingUtilities;

/**
  * Java Neural Network Example
  * Handwriting Recognition
  * by Jeff Heaton (http://www.jeffheaton.com) 1-2002
  * -------------------------------------------------
  * This class presents the main application window.
  *
  * @author Jeff Heaton (http://www.jeffheaton.com)
  * @version 1.0
  */

public class MainEntry extends JFrame implements Runnable {

   /**
	 * 
	 */
	private static final long serialVersionUID = 1L;

/**
    * The downsample width for the application.
    */
   static final int DOWNSAMPLE_WIDTH = 20;

   /**
    * The down sample height for the application.
    */
   static final int DOWNSAMPLE_HEIGHT = 20;

   /**
    * The entry component for the user to draw into.
    */
   Entry entry;

   /**
    * The down sample component to display the drawing
    * downsampled.
    */
   Sample sample;

   /**
    * The letters that have been defined.
    */
   DefaultListModel letterListModel = new DefaultListModel();

   /**
    * The neural network.
    */
   KohonenNetwork net;

   /**
    * The background thread used for training.
    */
   Thread trainThread = null;

   /**
    * The constructor.
    */
   @SuppressWarnings("deprecation")
MainEntry()
   {
     getContentPane().setLayout(null);
     entry = new Entry();
     entry.reshape(250,25,200,200);
     getContentPane().add(entry);

     sample = new Sample(DOWNSAMPLE_WIDTH,DOWNSAMPLE_HEIGHT);
     sample.reshape(307,300,100,100);
     entry.setSample(sample);
     getContentPane().add(sample);

     //{{INIT_CONTROLS
     setTitle("Java Neural Network");
     getContentPane().setLayout(null);
     setSize(500,450);
     setVisible(false);
     JLabel1.setText("Figuras reconocidas");
     getContentPane().add(JLabel1);
     JLabel1.setBounds(12,12,200,12);
     JLabel2.setText("Tries:");
     getContentPane().add(JLabel2);
     JLabel2.setBounds(12,300,72,24);
     downSample.setText("Mostrar ejemplo en mapa");
     downSample.setActionCommand("Down Sample");
     getContentPane().add(downSample);
     downSample.setBounds(250,273,200,24);
     add.setText("Agregar");
     add.setActionCommand("Add");
     getContentPane().add(add);
     add.setBounds(250,226,100,24);
     clear.setText("Limpiar");
     clear.setActionCommand("Clear");
     getContentPane().add(clear);
     clear.setBounds(350,226,100,24);
     recognize.setText("Reconocer");
     recognize.setActionCommand("Recognize");
     getContentPane().add(recognize);
     recognize.setBounds(250,250,200,24);
     JScrollPane1.setVerticalScrollBarPolicy(
       javax.swing.ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
     JScrollPane1.setOpaque(true);
     getContentPane().add(JScrollPane1);
     JScrollPane1.setBounds(12,24,200,200);
     JScrollPane1.getViewport().add(letters);
     letters.setBounds(0,0,126,129);
     del.setText("Borrar");
     del.setActionCommand("Delete");
     getContentPane().add(del);
     del.setBounds(12,250,200,24);
     load.setText("Cargar");
     load.setActionCommand("Load");
     getContentPane().add(load);
     load.setBounds(12,226,100,24);
     save.setText("Guardar");
     save.setActionCommand("Save");
     getContentPane().add(save);
     save.setBounds(112,226,100,24);
     train.setText("Empezar entrenamiento");
     train.setActionCommand("Begin Training");
     getContentPane().add(train);
     train.setBounds(12,274,200,24);
     JLabel3.setText("Ultimo Error:");
     getContentPane().add(JLabel3);
     JLabel3.setBounds(12,324,72,24);
     JLabel4.setText("Mejor Error:");
     getContentPane().add(JLabel4);
     JLabel4.setBounds(12,348,72,24);
     tries.setText("0");
     getContentPane().add(tries);
     tries.setBounds(96,300,72,24);
     lastError.setText("0");
     getContentPane().add(lastError);
     lastError.setBounds(96,324,200,24);
     bestError.setText("0");
     getContentPane().add(bestError);
     bestError.setBounds(96,348,200,24);
     JLabel8.setHorizontalTextPosition(
       javax.swing.SwingConstants.CENTER);
     JLabel8.setHorizontalAlignment(
       javax.swing.SwingConstants.CENTER);
     JLabel8.setText("Resultados del entrenamiento");
     getContentPane().add(JLabel8);
     JLabel8.setFont(new Font("Dialog", Font.BOLD, 14));
     JLabel8.setBounds(12,240,120,24);
     JLabel5.setText("Dibuje la letra aqui :");
     getContentPane().add(JLabel5);
     JLabel5.setBounds(250,12,200,12);
     //}}

     //{{REGISTER_LISTENERS
     SymAction lSymAction = new SymAction();
     downSample.addActionListener(lSymAction);
     clear.addActionListener(lSymAction);
     add.addActionListener(lSymAction);
     del.addActionListener(lSymAction);
     SymListSelection lSymListSelection = new SymListSelection();
     letters.addListSelectionListener(lSymListSelection);
     load.addActionListener(lSymAction);
     save.addActionListener(lSymAction);
     train.addActionListener(lSymAction);
     recognize.addActionListener(lSymAction);
     //}}
     letters.setModel(letterListModel);
     //{{INIT_MENUS
     //}}
   }


   /**
    * The main method.
    *
    * @param args Args not really used.
    */
   @SuppressWarnings("deprecation")
public static void main(String args[])
   {
     (new MainEntry()).show();
   }
   //{{DECLARE_CONTROLS
   javax.swing.JLabel JLabel1 = new javax.swing.JLabel();
   javax.swing.JLabel JLabel2 = new javax.swing.JLabel();

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
   //}}
   //{{DECLARE_MENUS
   //}}

   class SymAction implements java.awt.event.ActionListener {
     public void actionPerformed(java.awt.event.ActionEvent event)
     {
       Object object = event.getSource();
       if ( object == downSample )
         downSample_actionPerformed(event);
       else if ( object == clear )
         clear_actionPerformed(event);
       else if ( object == add )
         add_actionPerformed(event);
       else if ( object == del )
         del_actionPerformed(event);
       else if ( object == load )
         load_actionPerformed(event);
       else if ( object == save )
         save_actionPerformed(event);
       else if ( object == train )
         train_actionPerformed(event);
       else if ( object == recognize )
         recognize_actionPerformed(event);
     }
   }

   /**
    * Called to downsample the image.
    *
    * @param event The event
    */
   void downSample_actionPerformed(java.awt.event.ActionEvent event)
   {
     entry.downSample();

   }

   /**
    * Called to clear the image.
    *
    * @param event The event
    */
   void clear_actionPerformed(java.awt.event.ActionEvent event)
   {
     entry.clear();
     sample.getData().clear();
     sample.repaint();

   }

   /**
    * Called to add the current image to the training set
    *
    * @param event The event
    */
   void add_actionPerformed(java.awt.event.ActionEvent event)
   {
  

     String letter = JOptionPane.showInputDialog(
       "Por favor ingrese el nombre de la figura que dibujo: ");
     if ( letter==null )
       return;

   

     entry.downSample();
     SampleData sampleData = (SampleData)sample.getData().clone();
     sampleData.setLetter(letter);

//     for ( i=0;i<letterListModel.size();i++ ) {
//    	 SampleData str = (SampleData)letterListModel.getElementAt(i);
//       if ( str.equals(letter) ) {
//         JOptionPane.showMessageDialog(this,
//                                       "That letter is already defined, delete it first!","Error",
//                                       JOptionPane.ERROR_MESSAGE);
//         return;
//       }
//
//       if ( str.compareTo(sampleData)>0 ) {
//         letterListModel.add(i,sampleData);
//         return;
//       }
//     }
    letterListModel.add(letterListModel.size(),sampleData);
     letters.setSelectedIndex(letterListModel.getSize()-1);
     entry.clear();
     sample.repaint();

   }

   /**
    * Called when the del button is pressed.
    *
    * @param event The event.
    */
   void del_actionPerformed(java.awt.event.ActionEvent event)
   {
     int i = letters.getSelectedIndex();

     if ( i==-1 ) {
       JOptionPane.showMessageDialog(this,
                                     "Por favor seleccione la figura a borrar.","Error",
                                     JOptionPane.ERROR_MESSAGE);
       return;
     }

     letterListModel.remove(i);
   }

   class SymListSelection implements javax.swing.event.ListSelectionListener {
     public void valueChanged(javax.swing.event.ListSelectionEvent event)
     {
       Object object = event.getSource();
       if ( object == letters )
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
     if ( letters.getSelectedIndex()==-1 )
       return;
     SampleData selected =
       (SampleData)letterListModel.getElementAt(letters.getSelectedIndex());
     sample.setData((SampleData)selected.clone());
     sample.repaint();
     entry.clear();

   }

   /**
    * Called when the load button is pressed.
    *
    * @param event The event
    */
   void load_actionPerformed(java.awt.event.ActionEvent event)
   {
     try {
       FileReader f;// the actual file stream
       BufferedReader r;// used to read the file line by line

       f = new FileReader( new File("C:\\eclipse\\workspaces\\Robots\\Robots\\files\\figuras.dat") );
       r = new BufferedReader(f);
       String line;
       int i=0;

       letterListModel.clear();

       while ( (line=r.readLine()) !=null ) {
    	   StringTokenizer tokenizer= new StringTokenizer(line,":");
    	  
         SampleData ds =new SampleData(tokenizer.nextToken(),MainEntry.DOWNSAMPLE_WIDTH,MainEntry.DOWNSAMPLE_HEIGHT); 
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
       JOptionPane.showMessageDialog(this,
                                     "Cargando de 'figuras.dat'.","Training",
                                     JOptionPane.PLAIN_MESSAGE);

     } catch ( Exception e ) {
    	 e.printStackTrace();
       JOptionPane.showMessageDialog(this,
                                     "Error: " + e,"Training",
                                     JOptionPane.ERROR_MESSAGE);
     }

   }

   /**
    * Called when the save button is clicked.
    *
    * @param event The event
    */
   void save_actionPerformed(java.awt.event.ActionEvent event)
   {
     try {
       OutputStream os;// the actual file stream
       PrintStream ps;// used to read the file line by line

       os = new FileOutputStream( "C:\\eclipse\\workspaces\\Robots\\Robots\\files\\figuras.dat",false );
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
       JOptionPane.showMessageDialog(this,
                                     "Guardado en  'figuras.dat' .",
                                     "Training",
                                     JOptionPane.PLAIN_MESSAGE);

     } catch ( Exception e ) {
    	 e.printStackTrace();
       JOptionPane.showMessageDialog(this,"Error: " +
                                     e,"Training",
                                     JOptionPane.ERROR_MESSAGE);
     }

   }

   /**
    * Run method for the background training thread.
    */
   public void run()
   {
     try {
       int inputNeuron = MainEntry.DOWNSAMPLE_HEIGHT*
         MainEntry.DOWNSAMPLE_WIDTH;
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
                                     "Training",
                                     JOptionPane.ERROR_MESSAGE);
     }

   }

   /**
    * Called to update the stats, from the neural network.
    *
    * @param trial How many tries.
    * @param error The current error.
    * @param best The best error.
    */
   void updateStats(long trial,double error,double best)
   {
     if ( (((trial%100)!=0) || (trial==10)) && !net.halt )
       return;

     if ( net.halt ) {
       trainThread = null;
       train.setText("Begin Training");
       JOptionPane.showMessageDialog(this,
                                     "El entenamineto ha terminado.","Training",
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

   /**
    * Called when the train button is pressed.
    *
    * @param event The event.
    */
   void train_actionPerformed(java.awt.event.ActionEvent event)
   {
     if ( trainThread==null ) {
       train.setText("Stop Training");
       train.repaint();
       trainThread = new Thread(this);
       trainThread.start();
     } else {
       net.halt=true;
     }
   }

   /**
    * Called when the recognize button is pressed.
    *
    * @param event The event.
    */
   void recognize_actionPerformed(java.awt.event.ActionEvent event)
   {
     if ( net==null ) {
       JOptionPane.showMessageDialog(this,
                                     "Se necesita entrenar primero la red !","Error",
                                     JOptionPane.ERROR_MESSAGE);
       return;
     }
     entry.downSample();
//TODO
     double input[] = new double[DOWNSAMPLE_WIDTH*DOWNSAMPLE_HEIGHT];
     int idx=0;
     SampleData ds = sample.getData();
     for ( int y=0;y<ds.getHeight();y++ ) {
       for ( int x=0;x<ds.getWidth();x++ ) {
         input[idx++] = ds.getData(x,y)?.5:-.5;
       }
     }

     double normfac[] = new double[1];
     double synth[] = new double[1];

     int best = net.winner ( input , normfac , synth ) ;
     String map[] = mapNeurons();
     JOptionPane.showMessageDialog(this,
                                   "  " + map[best] + "   (La neurona #"
                                   + best + " es la ganadora)","La figura es",
                                   JOptionPane.PLAIN_MESSAGE);
     clear_actionPerformed(null);

   }

   /**
    * Used to map neurons to actual letters.
    *
    * @return The current mapping between neurons and letters as an array.
    */
   String []mapNeurons()
   {
	   String map[] = new String[letterListModel.size()];
     double normfac[] = new double[1];
     double synth[] = new double[1];

     for ( int i=0;i<map.length;i++ )
       map[i]="?";
     for ( int i=0;i<letterListModel.size();i++ ) {
    	 double input[] = new double[DOWNSAMPLE_WIDTH*DOWNSAMPLE_HEIGHT];
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


   public class UpdateStats implements Runnable {
     long _tries;
     double _lastError;
     double _bestError;

     public void run()
     {
       tries.setText(""+_tries);
       lastError.setText(""+_lastError);
       bestError.setText(""+_bestError);
     }
   }


}