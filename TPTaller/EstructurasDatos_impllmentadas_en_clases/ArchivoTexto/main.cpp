/**
 * Facultad de Ingeniería - Universidad de Buenos Aires
 * 75.41 - Algoritmos y Programación II
 * Archivo de Texto (Ejemplo de uso)
 * Cátedra Ing. Patricia Calvo
 * v1.0
 * Autor: Mariano Simone (marianosimone+7541@gmail.com)
 **/

#include <iostream>
#include "archivoTexto.h"

int main(int argc, char **argv) {
  ArchivoTexto miArchivo("unArchivo.txt");
  miArchivo.irAlFinal();
  miArchivo.escribir("HOLA");
  miArchivo.terminarLinea();
  std::string linea;
  miArchivo.irAlPrincipio();
  while (miArchivo.leerLinea(linea)) {
    std::cout << linea << std::endl;
  }
  return 0;
}

