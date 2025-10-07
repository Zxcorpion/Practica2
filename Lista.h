//
// Created by pablo on 06/10/2025.
//

#ifndef PRACTICA2_LISTA_H
#define PRACTICA2_LISTA_H
#include <stdexcept>

/**
 * @brief Definicion de la estructura Lista
 * @tparam L Tipo de dato de la lista
 */
template<typename L>
class ListaEnlazada {
private:
    template<typename N>
    class Nodo {
    public:
        N dato;
        Nodo *sig;
        Nodo(N &_dato, Nodo *_sig=0):
        dato(_dato), sig(_sig)
        {}
        ~Nodo(){}
    }; //Fin clase nodo
    Nodo<L> *cabecera, *cola;
    int tam=0;
    void limpia_lista();
public:
    template<typename I>
    class Iterador {
        Nodo<I> *nodo;
    public:
        friend class ListaEnlazada<I>;
        Iterador(Nodo<I> *_nodo=0): nodo (_nodo){}
        bool fin() {
            return nodo==0;
        }
        void siguiente() {
            nodo = nodo->sig;
        }
        Nodo<L> *get_nodo() const {return nodo;}
        L &dato(){ return nodo->dato; }
        L &operator*(){ return nodo->dato; }
        ~Iterador(){}
    }; //Fin clase iterador

    ListaEnlazada() : cabecera(0), cola(0), tam(0) {}
    ~ListaEnlazada();
    ListaEnlazada(const ListaEnlazada<L> &origen);
    ListaEnlazada &operator=(const ListaEnlazada<L> &origen);
    Iterador<L> iterador() {return Iterador<L>(cabecera);}
    void insertarinicio(L &dato);
    void insertarFinal(L &dato);
    void insertar_delante(Iterador<L> &i, const L &dato);
    void insertarDetras(Iterador<L> &i, const L &dato);
    void borrarInicio();
    void borrarFinal();
    void borrar(Iterador<L> &i);
    int get_tam(){ return tam; }
    L &inicio();
    L &final();
    ListaEnlazada<L> concatena(const ListaEnlazada<L> &origen);
    ListaEnlazada<L> operator+(const ListaEnlazada<L> &origen);
};

template<typename L>
ListaEnlazada<L>::ListaEnlazada(const ListaEnlazada &origen):
cabecera(origen.cabecera),
cola(origen.cola),
tam(origen.tam)
{}

template<typename L>
ListaEnlazada<L> &ListaEnlazada<L>::operator=(const ListaEnlazada<L> &origen) {
    if(cabecera != &origen.cabecera){
        while(cabecera != 0){
            Nodo<L> *aux = cabecera;
            cabecera = cabecera->sig;
            delete aux;
        }
        if(origen.cabecera==0) {
            cola=0;
            cabecera=0;
            tam=0;
        }else {
            cabecera=origen.cabecera;
            cola=origen.cola;
            tam=origen.tam;
        }
    }
    return *this;
}

/**
 * @brief Metodo que devuelve el dato del primer elemento de la lista
 * @return Dato al inicio de la lista
 */
template<typename L>
L &ListaEnlazada<L>::inicio() {
    if(cabecera==nullptr) {
        throw std::invalid_argument("Cabecera no existe");
    }
    Iterador<L> i= cabecera;
    return i.dato();
}
/**
 * @brief Metodo que devuelve el ultimo dato elemento de la lista
 * @return Dato al final de la lista
 */
template<typename L>
L &ListaEnlazada<L>::final() {
    if(cola==nullptr) {
        throw std::invalid_argument("Cola no existe");
    }
    Iterador<L> i= cola;
    return i.dato();
}

/**
 * @brief Metodo que inserta al comienzo de la lista
 * @param dato Dato que se introduce
 * @post La funcion añade un nuevo dato al comienzo de la lista, sustituyendo al que en ese momento sea la cabecera. Si no hubiera un dato, este seria tambien la cola
 */
template<typename L>
void ListaEnlazada<L>::insertarinicio(L &dato) {
    Nodo<L> *nuevo = new Nodo<L>(dato, cabecera); //aqui lo que hago es crear el nuevo nodo y ademas hago que apunte al actual primero

    if (cabecera == 0) {
        cabecera = nuevo;
        cola = nuevo;
    }
    cabecera = nuevo;
    tam++;
}

/**
 * @brief Metodo que inserta al final de la lista
 * @param dato Dato que se introduce
 * @post La funcion añade un nuevo dato al final de la lista, sustituyendo al que en ese momento sea la cola. Si no hubiera un dato, este seria tambien la cabecera
 */
template<typename L>
void ListaEnlazada<L>::insertarFinal(L &dato) {
    Nodo<L> *nuevo = new Nodo<L>(dato, 0); //aqui lo que hago es crear el nuevo nodo y ademas hago que apunte al actual ultimo
    if (cola != 0) { //Si la lista no esta vacia, el siguiente a el ultimo es el nuevo
        cola->sig = nuevo;
    }

    if (cabecera == 0) {
        cabecera = nuevo;
    }
        cola = nuevo; //Aqui el nuevo pasa a ser la nueva cola ya que apunta a null
        tam++;
}

template<typename L>
void ListaEnlazada<L>::insertarDetras(Iterador<L> &i, const L &dato) {
    Nodo<L> *nuevo = new Nodo<L>(dato, i->sig);
    i->sig=nuevo;
    if(cola==i) {
        cola=nuevo;
    }
    tam++;
}
template<typename L>
void ListaEnlazada<L>::insertar_delante(Iterador<L> &i, const L &dato) {
    Nodo<L> *nuevo = new Nodo<L>(dato, i);
    if(i==cabecera) {
        cabecera = nuevo;
    }
    Nodo<L> *anterior= 0;
    if(cabecera!=cola) {
        anterior=cabecera;
        while(anterior->sig !=i) {
            anterior=anterior->sig;
        }
        anterior->sig=nuevo;
    }
    if(cabecera==0) {
        cola=cabecera=nuevo;
    }
    tam++;
}

/**
 * @brief Metodo que elimina el primer nodo de la lista
 * @post El primer nodo de la lista es borrado, en caso de que solo hubiera 1 nodo, la cabecera y la cola apuntan al mismo nodo
 * @throw Se lanza una excepcion si se intenta eliminar un nodo de una lista vacia
 */
template<typename L>
void ListaEnlazada<L>::borrarInicio(){
    if (cabecera == 0) {
       throw std::invalid_argument("Error al borrar por el principio, la lista está vacia");
    }
    Nodo<L> *borrado = cabecera;
    cabecera = cabecera->sig;
    delete borrado;

    if (cabecera == 0) {
        cola=0;
    }
    tam--;
}
/**
 * @brief Metodo que elimina el último nodo de la lista
 * @post El ultimo nodo de la lista es borrado, en caso de no haber nada cabecera y cola apuntan a 0
 */
template<typename L>
void ListaEnlazada<L>::borrarFinal(){
    Nodo<L> *borrado = 0;
    if(cabecera != cola) {
        borrado=cabecera;
        while(borrado->sig != cola) {
            borrado=borrado->sig;
        }
    }
    delete cola;
    cola=borrado;
    if(borrado != 0) {
        borrado->sig=0;
    }else {
        cabecera=0;
    }
    tam--;
}

template<typename L>
void ListaEnlazada<L>::borrar(Iterador<L> &i) {
    Nodo<L> *borrado = 0;
    if(cabecera != cola) {
        borrado=cabecera;
        while(borrado->sig != i) {
            borrado=borrado->sig;
        }
    }
    borrado->sig=i->sig;
    delete i;
    tam--;
}
template<typename L>
ListaEnlazada<L>::~ListaEnlazada() {
    while(cabecera != 0){
        Nodo<L> *aux = cabecera;
        cabecera = cabecera->sig;
        delete aux;
    }
}

template<typename L>
void ListaEnlazada<L>::limpia_lista() {
    if(cabecera) {
        throw std::invalid_argument("No hay nada que limpiar");
    }
        while(cabecera != 0){
            Nodo<L> *aux = cabecera;
            cabecera = cabecera->sig;
            delete aux;
    }
}
template<typename L>
ListaEnlazada<L> ListaEnlazada<L>::concatena(const ListaEnlazada<L> &origen) {
    ListaEnlazada<L> nueva;
    Nodo<L> *aux = cabecera;
    while(aux->sig != 0) {
        nueva.insertarFinal(aux->dato);
        aux=aux->sig;
    }
    aux=origen.cabecera;
    while(aux->sig != 0) {
        nueva.insertarFinal(aux->dato);
        aux=aux->sig;
    }
    return nueva;
}

template<typename L>
ListaEnlazada<L> ListaEnlazada<L>::operator+(const ListaEnlazada<L> &origen) {
    this->cola = origen.cabecera;
    Nodo<L> *aux = origen.cabecera;
    while(aux->sig != 0) {
        this->insertarFinal(aux->dato);
        aux=aux->sig;
    }
    return this;
}






#endif //PRACTICA2_LISTA_H