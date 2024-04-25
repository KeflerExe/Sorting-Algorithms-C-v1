/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: AyEDA
/// Curso: 2º
/// Práctica 5: Métodos de ordenación
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 15/04/2023
/// Archivo: metodo_ordenacion.h

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

// Clase abstracta que define el método de ordenación.
template<class Key>
class SortMethod {
 protected:
  unsigned size;
  std::vector<Key> sequence_;
 public:
  virtual void Sort() = 0;
  virtual int operator[](int posicion) {
    return this->sequence_[posicion];
  }
};

// Clase que implementa el método de ordenación por inserción.
template <class Key>
class OrdenacionPorInsercion : public SortMethod<Key> {
 public:
  OrdenacionPorInsercion(std::vector<Key> sequence) {
    this->sequence_ = sequence;
    this->size = sequence.size();
    this->movimientos_ = 0;
  }
  void Sort() {
    for (unsigned iterador = 1; iterador < this->size; ++iterador) {
      Key key = this->sequence_[iterador];
      int iterador2 = iterador - 1;
      while (iterador2 >= 0 && this->sequence_[iterador2] > key) {
        this->sequence_[iterador2 + 1] = this->sequence_[iterador2];
        iterador2--;
        movimientos_++;
      }
      this->sequence_[iterador2 + 1] = key;
    }
  }
  int GetMovimientos() const { return movimientos_; }
 private:
  int movimientos_;
};

// Clase que implementa el método de ordenación por mezcla.
template <class Key>
class MergeSort : public SortMethod<Key> {
 public:
  MergeSort(std::vector<Key> sequence) {
    this->sequence_ = sequence;
    this->size = sequence.size();
  }
  void Sort() {
    DivideSecuencia(this->sequence_, 0, this->size - 1);   
  }
  void Union(std::vector<Key>& vector, int indice_izq, int indice_medio, int indice_der) {
    int iterador, iterador2, iterador3;
    int tamanio_izq = indice_medio - indice_izq + 1;
    int tamanio_der = indice_der - indice_medio;
    std::vector<Key> vector_izquierda(tamanio_izq), vector_derecha(tamanio_der);
    for (iterador = 0; iterador < tamanio_izq; iterador++) {
      vector_izquierda[iterador] = vector[indice_izq + iterador];
    }
    for (iterador2 = 0; iterador2 < tamanio_der; iterador2++) {
      vector_derecha[iterador2] = vector[indice_medio + 1 + iterador2];
    }
    iterador = 0;
    iterador2 = 0;
    iterador3 = indice_izq;
    while (iterador < tamanio_izq && iterador2 < tamanio_der) {
      if (vector_izquierda[iterador] <= vector_derecha[iterador2]) {
        vector[iterador3] = vector_izquierda[iterador];
        iterador++;
      } else {
        vector[iterador3] = vector_derecha[iterador2];
        iterador2++;
      }
      iterador3++;
    }
    while (iterador < tamanio_izq) {
      vector[iterador3] = vector_izquierda[iterador];
      iterador++;
      iterador3++;
    }
    while (iterador2 < tamanio_der) {
      vector[iterador3] = vector_derecha[iterador2];
      iterador2++;
      iterador3++;
    }
  }
  void DivideSecuencia(std::vector<Key>& vector, int indice_izq, int indice_der) {
    if (indice_izq < indice_der) {
      int indice_med = indice_izq + (indice_der - indice_izq) / 2;
      DivideSecuencia(vector, indice_izq, indice_med);
      DivideSecuencia(vector, indice_med + 1, indice_der);
      Union(vector, indice_izq, indice_med, indice_der);
    }
  } 
};

// Clase que implementa el método de ordenación por montículos.
template<class Key>
class HeapSort : public SortMethod<Key> {
public:
  HeapSort(std::vector<Key> sequence) {
    this->sequence_ = sequence;
    this->size = sequence.size();
  }
  void Amontonar(std::vector<Key>& vector, int n, int i) {
    int mayor_posicion = i; 
    int aux1 = 2 * i + 1; 
    int aux2 = 2 * i + 2; 
    if (aux1 < n && vector[aux1] > vector[mayor_posicion]) {
      mayor_posicion = aux1;
    }
    if (aux2 < n && vector[aux2] > vector[mayor_posicion]) {
      mayor_posicion = aux2;
    }
    if (mayor_posicion != i) {
      std::swap(vector[i], vector[mayor_posicion]);
      Amontonar(vector, n, mayor_posicion);
    }
  }
  void Sort() {
    for (int iterador = this->size / 2 - 1; iterador >= 0; iterador--) {
      Amontonar(this->sequence_, this->size, iterador);
    }
    for (int iterador = this->size - 1; iterador >= 0; iterador--) {
      std::swap(this->sequence_[0], this->sequence_[iterador]);
      Amontonar(this->sequence_, iterador, 0);
    }
  }
};

// Clase que implementa el método de ordenación por ráfaga.
template<class Key>
class RadixSort : public SortMethod<Key> {
public:
  RadixSort(std::vector<Key> sequence) {
    this->sequence_ = sequence;
    this->size = sequence.size();
  }
  void Sort() {
    int exp = 1;
    Key valor_maximo = *std::max_element(this->sequence_.begin(), this->sequence_.end());
    while (valor_maximo / exp > 0) {
      std::vector<Key> salida(this->size);
      std::vector<int> contador(10, 0);
      for (int iterador = 0; iterador < this->size; iterador++) {
        contador[(this->sequence_[iterador] / exp) % 10]++;
      }
      for (int iterador = 1; iterador < 10; iterador++) {
        contador[iterador] += contador[iterador - 1];
      }
      for (int iterador = this->size - 1; iterador >= 0; iterador--) {
        salida[contador[(this->sequence_[iterador] / exp) % 10] - 1] = this->sequence_[iterador];
        contador[(this->sequence_[iterador] / exp) % 10]--;
      }
      for (int iterador = 0; iterador < this->size; iterador++) {
        this->sequence_[iterador] = salida[iterador];
      }
      exp *= 10;
    }    
  }
};

// Clase que implementa el método de ordenación por shell.
template <class Key>
class ShellSort : public SortMethod<Key> {
 public:
  ShellSort(std::vector<Key> sequence, double alfa) {
    this->sequence_ = sequence;
    this->size = sequence.size();
    this->alfa_ = alfa;
  }
  void Sort() {
    int intervalo = 1;
    while (intervalo < this->size / this->alfa_) {
      intervalo = intervalo * this->alfa_;
    }
    while (intervalo > 0) {
      for (int iterador = intervalo; iterador < this->size; iterador++) {
        Key key_auxiliar = this->sequence_[iterador];
        int iterador2 = iterador;
        while (iterador2 >= intervalo && this->sequence_[iterador2 - intervalo] > key_auxiliar) {
          this->sequence_[iterador2] = this->sequence_[iterador2 - intervalo];
          iterador2 -= intervalo;
        }
        this->sequence_[iterador2] = key_auxiliar;
      }
      intervalo /= this->alfa_;
    }
  }
 private:
  double alfa_;
};