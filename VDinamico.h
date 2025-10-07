

#ifndef PRACTICA_1_VDINAMICO_H
#define PRACTICA_1_VDINAMICO_H
#include <limits.h>
#include <algorithm>
#include <stdexcept>
#include <cmath>

/**
 * @brief Definicion de un vector dinamico
 * @tparam T Tipo de dato del vector
 */
template<typename T>
class VDinamico {
private:
     unsigned int tamfis=1,tamlog=0;
    T *vector;
public:
    VDinamico();
    VDinamico(unsigned int tamlog_, T &dato);
    VDinamico(const VDinamico &orig);
    VDinamico(const VDinamico &orig, unsigned int posicionInicial, unsigned int numElementos);
    VDinamico &operator=(const VDinamico &orig);
    T &operator[](unsigned int posicion);

    void insertar(const T &dato, unsigned int pos = UINT_MAX);
    T borrar(unsigned int pos = UINT_MAX);
    void ordenar();
    unsigned int tamlog_() const;
    ~VDinamico();

    int busquedaBinaria(T &d);

};

/**
 * @brief Constructor por defecto
 * @post Se crea un vector dinamico por defecto
 */
template<typename T>
VDinamico<T>::VDinamico() :
tamfis(1),
tamlog(0) {
    vector = new T[tamfis];
}

/**
 * @brief Constructor parametrizado
 * @param tamlog_ Tamaño logico a insertar
 * @post Se crea un vector dinamico parametrizado con un tamaño logico
 */
template<typename T>
VDinamico<T>::VDinamico(unsigned int tamlog_, T &dato):
    tamlog(tamlog_)
{
    tamfis=1;
    while (tamfis < tamlog) {
        tamfis *= 2;
    } //Con este bucle me puedo asegurar las potencias de 2

    vector = new T[tamfis];
    for(int i=0; i<tamlog; i++){
        vector[i] = dato;
    }
}

/**
 * @brief Constructor de copia
 * @param orig Objeto que se quiere copiar
 * @post Se crea un nuevo vector con los datos de orig
 */
template<typename T>
VDinamico<T>::VDinamico(const VDinamico &orig):
tamlog(orig.tamlog),
tamfis(orig.tamfis)
{
    vector = new T[orig.tamfis];
    for (unsigned int i=0; i<orig.tamlog;i++) {
        vector[i] = orig.vector[i];
    }
}

/**
 * @brief Constructor de copia parcial
 * @param orig Objeto que se quiere copiar
 * @param posicionInicial Posicion de inicio para copiar
 * @param numElementos Numero de elementos que se quieren copiar
 * @post El constructor copia los elementos de otro desde una posicion dada y copia un numero de elementos asignado
 * @throw std::out_of_range Si se intenta acceder por fuera de los limites del vector
 */
template<typename T>
VDinamico<T>::VDinamico(const VDinamico &orig, unsigned int posicionInicial, unsigned int numElementos) {
    if (posicionInicial + numElementos > orig.tamlog) {
        throw std::out_of_range("Error en la copia parcial, se esta intentando copiar posiciones inexistentes");
    }
    if (posicionInicial >= orig.tamlog) {
        throw std::out_of_range("Error en copia parcial, se esta intentando copiar por fuera de los limites del vector");
    }
    tamlog = numElementos;

    tamfis = 1;
    while (tamfis < tamlog) {
        tamfis *= 2;
    }

    vector = new T[tamfis];
    for (unsigned int i=0;i<numElementos;i++) {
        vector[i] = orig.vector[posicionInicial + i];
    }
}

/**
 * @brief Operador de asignacion
 * @param orig Objeto a del que se extraen los datos
 * @return Referencia al objeto mismo
 * @post Los datos del vector son reemplazados por los de orig
 */
template<typename T>
VDinamico<T> &VDinamico<T>::operator=(const VDinamico &orig) {
    if (&orig != this) { //Aqui compruebo que si lo que hay en orig no coincide con lo que hay en vector, borro lo que haya en vector y hago ya los cambios
        delete[] vector;

        tamlog = orig.tamlog; //Copiamos el tamaño logico
        tamfis = orig.tamfis; //Copiamos el tamaño fisico

        vector = new T[tamfis];
        for (unsigned int i=0; i<tamlog; i++) {
            vector[i] = orig.vector[i];
        }
    }
    return (*this);
}

/**
 * @brief Operador []
 * @param posicion Posicion a la que queremos acceder
 * @return Lo que se encuentra en esa posicion
 * @throw std::out_of_range Si se intenta acceder por fuera de los limites del vector
 */
template<typename T>
T &VDinamico<T>::operator[](unsigned int posicion) {
    if (posicion >= tamlog)
        throw std::out_of_range("Error en operator[], posicion fuera del limite");
    return vector[posicion];
}

/**
 *@brief El metodo isnerta un dato en una posicion indicada, en caso de quedarse sin espacio, se aumenta el tamaño del vector
 * @param dato Dato que se quiere insertar
 * @param pos Posicion sobre laque queremos insertar
 * @throw std::out_of_range Si se intenta acceder por fuera de los limites del vector
 */
template<typename T>
void VDinamico<T>::insertar(const T &dato, unsigned int pos) {
    if (pos != UINT_MAX && pos > tamlog) { //Si me paso o si esta vacio
        throw std::out_of_range("Error al insertar, indice fuera de los limites");
    }

    if (tamlog == tamfis) {
        tamfis *= 2;
        T *aux = new T[tamfis];
        for (unsigned int i=0; i<tamlog; ++i) {
            aux[i] = vector[i];
        }
        delete[] vector;
        vector = aux;
    }
    if (pos == UINT_MAX) {
        pos = tamlog;
    }else{
        for (unsigned int i=tamlog; i >= pos ; i--) {
            vector[i] = vector[i-1];
        }
    }
    vector[pos] = dato;
    tamlog++;
}

/**
 * @brief El metodo se encarga de borrar el dato de una posicion, si un tercio de la capacidad total del vector esta vacio, este reduce su tamaño fisico a la mitad
 * @param pos
 * @return El dato eliminado
 * @throw std::out_of_range Si se intenta eliminar un dato de un vector vacio
 * @throw std::out_of_range Si se intenta eliminar un dato por fuera de los limites del vector
 */
template<typename T>
T VDinamico<T>::borrar(unsigned int pos) {
    if (tamlog == 0) {
        throw std::out_of_range("Error, no se puede borrar nada de un vector vacio");
    }

    if (pos == UINT_MAX) {
        //Con esto digo que si no defino una posicion, el dato ira en la posicion maxima que acepte clion
        pos = tamlog - 1;
    }
    if (pos >= tamlog) { //Si me paso o si esta vacio
        throw std::out_of_range("Error al insertar, indice fuera de los limites");
    }

    T borrado = vector[pos];

    for (unsigned int i=pos; i<tamlog-1; ++i) {
        vector[i] = vector[i+1];
    }
    tamlog--;

    //Con esto reduzco a la mitad el tamaño total si el usado es un tercio del total
    if (tamlog*3 < tamfis) {
        tamfis /= 2;
        T *aux = new T[tamfis];
        for (unsigned int i=0; i<tamlog; ++i) {
            aux[i] = vector[i];
        }
        delete[] vector;
        vector = aux;
    }
    return borrado;
}

/**
 * @brief La funcion ordena el vector segun el id_num del medicamento
 * @tparam T tipo de dato
 */
template<typename T>
void VDinamico<T>::ordenar() {
    std::sort(vector, vector + tamlog);
}
/**
 * @brief Getter del atributo tamlog
 * @tparam T tipo de dato
 * @return Devuelve el tamaño logico del vector
 */
template<typename T>
unsigned int VDinamico<T>::tamlog_() const {
    return tamlog;
}

/**
 * @brief Destructor de la clase
 */
template<typename T>
VDinamico<T>::~VDinamico() {
    if (!(vector != nullptr)) {
        delete [] vector;
        vector = nullptr;
    }
}

/**
 * @brief Se busca un dato partiendo de la mitad del vector, reduciendolo cada vez mas si no se encuentra dicho dato hasta que se encuentre
 * @param d Dato que buscamos
 * @return Dato encontrado
 */
template<typename T>
int VDinamico<T>::busquedaBinaria(T &d) {
    int inf=0;
    int sup=tamlog-1;
    int curIn; //Esta es la cota inf actual

    while (inf <= sup) {
        curIn = (inf+sup)/2;
        if (vector[curIn] == d) {
            return curIn;
        }else if (vector[curIn] < d) {
            inf = curIn+1; //Me quito datos por la izquierda
        }else {
            sup = curIn-1;  //Me quito datos por la derecha
        }
    }
    return -1; //Si no se encuentra lanzo -1
}


#endif //PRACTICA_1_VDINAMICO_H