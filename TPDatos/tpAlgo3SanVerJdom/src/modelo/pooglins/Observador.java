package modelo.pooglins;

import modelo.entornoDeJuego.EstadoPooglin;

/**
 * Clase: Interfaz Observador.
 * Utilidad: Interfaz que agrupa los metodos necesarios para poder implementar un 
 * 			 Observador, el cual detectara los cambios de estados de ciertos objetos,
 * 			 por ejemplo la muerte de un Pooglin o el caso en que un Pooglin haya pasado
 *           por la puerta de Salida (Pooglin Ganador).
 * */
public interface Observador {

	public void eventoMuertePooglin(int id);
	public void eventoPooglinGanador(int id);
	public void actualizar(Posicion posicion);
	public void actualizar(EstadoPooglin estado);
	public void actualizarAgregarPooglin(EstadoPooglin estado);
}

