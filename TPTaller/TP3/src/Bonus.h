/*
 * Bonus2.h
 *
 *  Created on: 20-jun-2009
 *      Author: pablosivori
 */

#ifndef BONUS_H_
#define BONUS_H_
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_main.h>
#include <iostream>
class Bonus {
public:
	Bonus();

	virtual int aplicar()=0;
	static void desAplicar();
	int getActivo();
	/* 0  si esta activo
	 * -1 si no esta activo
	 */
	void setActivo(int activo);
	/*
	 * Metodos para guardar el estado anterior del tejo y de los pad
	 */
    void cargarImagen(std::string idTextura);
	int getTipoBonus();
	int setTipoBonus(int tipoBonus);
	virtual ~Bonus();
    SDL_Surface* getImagen();
    void setImagen(SDL_Surface *imagen);

private:
	SDL_Surface *imagen; //donde se guarda la imagen en caso de tenerla
	int tipoBonus;
};

#endif /* BONUS2_H_ */
