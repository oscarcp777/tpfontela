#include "Dibujar.h"
#include "Escenario.h"
#include <math.h>


Dibujar::Dibujar(){
}
Dibujar* Dibujar::unicaInstanciaDibujar = NULL;
Dibujar* Dibujar::obtenerInstancia(){
	
	if(!Dibujar::unicaInstanciaDibujar){
		Dibujar::unicaInstanciaDibujar = new Dibujar();
	}
	
	return Dibujar::unicaInstanciaDibujar;
}

void Dibujar::dibujarRectangulo(int posX, int posY, int ancho, int alto, int color){
	 int i, j;
	 int PITCH =(this->pantalla)->pitch / 4;
  for (i = 0; i < alto; i++)
  {
    // vertical clipping: (top and bottom)
    if ((posY + i) >= 0 && (posY + i) < Escenario::obtenerInstancia()->getAlto())
    {
      int len = ancho;
      int xofs = posX;

      // left border
      if (xofs < 0)
      {
        len += xofs;
        xofs = 0;
      }

      // right border
      if (xofs + len >= Escenario::obtenerInstancia()->getAncho())
      {
        len -= (xofs + len) - Escenario::obtenerInstancia()->getAncho();
      }
      int ofs = (i + posY) * PITCH + xofs;

      // note that len may be 0 at this point, 
      // and no pixels get drawn!
      for (j = 0; j < len; j++)
        ((unsigned int*)(this->pantalla)->pixels)[ofs + j] = color;
    }
  }

}
void Dibujar::dibujarCirculo(int posX, int posY, int radio, int color){
	
  int i, j;
  int PITCH =(this->pantalla)->pitch / 4;
  for (i = 0; i < 2 * radio; i++)
  {
    // vertical clipping: (top and bottom)
	  if ((posY - radio + i) >= 0 && (posY - radio + i) < Escenario::obtenerInstancia()->getAlto())
    {
		  int len = (int)sqrt((float)(radio * radio - (radio - i) * (radio - i))) * 2;
      int xofs = posX - len / 2;

      // left border
      if (xofs < 0)
      {
        len += xofs;
        xofs = 0;
      }

      // right border
      if (xofs + len >= Escenario::obtenerInstancia()->getAncho())
      {
        len -= (xofs + len) - Escenario::obtenerInstancia()->getAncho();
      }
      int ofs = (posY - radio + i) * PITCH + xofs;
      
      // note that len may be 0 at this point, 
      // and no pixels get drawn!
      for (j = 0; j < len; j++)
        ((unsigned int*)(this->pantalla)->pixels)[ofs + j] = color;
    }
  }
}