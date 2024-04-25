/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: AyEDA
/// Curso: 2º
/// Práctica 5: Métodos de ordenación
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 15/04/2023
/// Archivo: main_ordenacion.cc

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "metodo_ordenacion.h"

typedef long key;

// Función principal donde se pregunta al usuario qué algoritmo de ordenación desea ejecutar y se le pide que ingrese los datos de la secuencia a ordenar.
int main() {
  std::cout << "1. Ordenacion por insercion" << std::endl;
  std::cout << "2. Merge sort" << std::endl;
  std::cout << "3. Shell sort" << std::endl;
  std::cout << "4. Heap sort" << std::endl;
  std::cout << "5. Radix sort" << std::endl;
  std::cout << "Seleccione un algoritmo a ejecutar: ";
  int opcion_escogida{0};
  std::cin >> opcion_escogida;
  std::cout << "Ingrese tamaño de la secuencia: ";
  int tamanio_secuencia{0};
  std::cin >> tamanio_secuencia;
  std::vector<int> sequencia(tamanio_secuencia);
  std::cout << "¿Desea ingresar los valores manualmente? (s/n): ";
  char respuesta;
  std::cin >> respuesta;
  if (respuesta == 's') {
    for (int iterador = 0; iterador < tamanio_secuencia; ++iterador) {
      std::cout << "Ingrese el valor " << iterador + 1 << ": ";
      std::cin >> sequencia[iterador];
    }
  } else {
    srand(time(NULL));
    for (int iterador = 0; iterador < tamanio_secuencia; ++iterador) {
      sequencia[iterador] = rand() % 9000 + 1000;
    }
  }
  switch (opcion_escogida) {
    case 1: {
      OrdenacionPorInsercion<int> ordenacion_por_insercion(sequencia);
      std::cout << std::endl << "Secuencia original: " << std::endl;
      for (int iterador = 0; iterador < tamanio_secuencia; ++iterador) {
        std::cout << ordenacion_por_insercion[iterador] << " ";
      }
      ordenacion_por_insercion.Sort();
      std::cout << std::endl << "Secuencia ordenada: " << std::endl;
      for (int iterador = 0; iterador < tamanio_secuencia; ++iterador) {
        std::cout << ordenacion_por_insercion[iterador] << " ";
      }
      std::cout << std::endl;
      std::cout << "Movimientos realizados: " << ordenacion_por_insercion.GetMovimientos() << std::endl;
      break;
    }
    case 2: {
      MergeSort<int> merge_sort(sequencia);
      std::cout << std::endl << "Secuencia original: " << std::endl;
      for (int iterador = 0; iterador < tamanio_secuencia; ++iterador) {
        std::cout << merge_sort[iterador] << " ";
      }
      merge_sort.Sort();
      std::cout << std::endl << "Secuencia ordenada: " << std::endl;
      for (int iterador = 0; iterador < tamanio_secuencia; ++iterador) {
        std::cout << merge_sort[iterador] << " ";
      }
      std::cout << std::endl;
      break;
    }
    case 3: {
      double constante_reduccion{0};
      std::cout << "Introduzca la constante de reducción: ";
      std::cin >> constante_reduccion;
      ShellSort<int> shell_sort(sequencia, constante_reduccion);
      std::cout << std::endl << "Secuencia original: " << std::endl;
      for (int iterador = 0; iterador < tamanio_secuencia; ++iterador) {
        std::cout << shell_sort[iterador] << " ";
      }
      shell_sort.Sort();
      std::cout << std::endl << "Secuencia ordenada: " << std::endl;
      for (int iterador = 0; iterador < tamanio_secuencia; ++iterador) {
        std::cout << shell_sort[iterador] << " ";
      }
      std::cout << std::endl;     
      break;
    }
    case 4: {
      HeapSort<int> heap_sort(sequencia);
      std::cout << std::endl << "Secuencia original: " << std::endl;
      for (int iterador = 0; iterador < tamanio_secuencia; ++iterador) {
        std::cout << heap_sort[iterador] << " ";
      }
      heap_sort.Sort();
      std::cout << std::endl << "Secuencia ordenada: " << std::endl;
      for (int iterador = 0; iterador < tamanio_secuencia; ++iterador) {
        std::cout << heap_sort[iterador] << " ";
      }
      std::cout << std::endl;
      break;
    }
    case 5: {
      RadixSort<int> radix_sort(sequencia);
      std::cout << std::endl << "Secuencia original: " << std::endl;
      for (int iterador = 0; iterador < tamanio_secuencia; ++iterador) {
        std::cout << radix_sort[iterador] << " ";
      }
      radix_sort.Sort();
      std::cout << std::endl << "Secuencia ordenada: " << std::endl;
      for (int iterador = 0; iterador < tamanio_secuencia; ++iterador) {
        std::cout << radix_sort[iterador] << " ";
      }
      std::cout << std::endl;
      break;
    }
    default: {
      std::cout << "Opcion invalida. Finalizando programa..." << std::endl;
      exit(EXIT_SUCCESS);
      break;
    }
  }
}