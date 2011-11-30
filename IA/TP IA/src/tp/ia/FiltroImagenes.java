/**
 * 
 */
package tp.ia;

import java.io.File;
import java.util.Set;

import javax.swing.filechooser.FileFilter;

/**
 * @author oscar
 *
 */
public class FiltroImagenes extends FileFilter {

	public FiltroImagenes(Set<String> filters) {
		super();
		this.filters = filters;
	}
	private Set<String> filters;
	/* (non-Javadoc)
	 * @see javax.swing.filechooser.FileFilter#accept(java.io.File)
	 */
	@Override
	public boolean accept(File f) {
		if(f != null) {
			if(f.isDirectory()) {
				return true;
			    }
		    String extension = getExtension(f);
		    if(extension != null && filters.contains(getExtension(f))) {
			return true;
		    };
		}
		return false;
	}

	/* (non-Javadoc)
	 * @see javax.swing.filechooser.FileFilter#getDescription()
	 */
	@Override
	public String getDescription() {
		
		return "JPEG and GIF Image Files (*.jpg, *.gif)";
	}
	 /**
     * Return the extension portion of the file's name .
     *
     * @see #getExtension
     * @see FileFilter#accept
     */
     public String getExtension(File f) {
	if(f != null) {
	    String filename = f.getName();
	    int i = filename.lastIndexOf('.');
	    if(i>0 && i<filename.length()-1) {
		return filename.substring(i+1).toLowerCase();
	    };
	}
	return null;
    }

}
