/*
 * Bonus2.h
 *
 *  Created on: 20-jun-2009
 *      Author: pablosivori
 */

#ifndef BONUS_H_
#define BONUS_H_


class Bonus {
public:
	Bonus();

	virtual int aplicar()=0;
	int getActivo();
	/* 0  si esta activo
	 * -1 si no esta activo
	 */
	void setActivo(int activo);
	/*
	 * Metodos para guardar el estado anterior del tejo y de los pad
	 */
	void setVelocidadAnterior(int velocidadAnterior);
	int getVelocidadAnterior();
	void setAlturaAnterior(int alturaAnterior);
	int getAlturaAnterior();
	void setRadioAnterior(int radioAnterior);
	int getRadioAnterior();
	virtual ~Bonus();

private:
	int activo;
	int velocidadAnterior;
	int alturaAnterior;
	int radioAnterior;

};

#endif /* BONUS2_H_ */
