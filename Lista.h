//
// Created by pablo on 06/10/2025.
//

#ifndef PRACTICA2_LISTA_H
#define PRACTICA2_LISTA_H

template<typename L>
class ListaEnlazada {
private:
    template<typename N>
    class Nodo {
    public:
        N dato;
        Nodo *sig;
        Nodo(N &dato, Nodo *sig=0);
    };
    Nodo<L> *cabecera, *cola;
    int tam=0;
public:
    template<typename I>
    class Iterador {
        Nodo<I> *nodo;
    public:
        Iterador(Nodo<I> *_nodo): nodo (_nodo){}
        bool fin(){return nodo==0;}
        void siguiente() {
            nodo=nodo->sig;
        }
        I &dato(){return nodo->dato;}
        I &operator*(){return nodo->dato;}
    };
    ListaEnlazada() : cabecera(0), cola(0), tam(0) {}
    ~ListaEnlazada(){}
    ListaEnlazada(const ListaEnlazada &origen);
    ListaEnlazada &operator=(const ListaEnlazada &origen);
    Iterador<L> iterador() {return Iterador<L>(cabecera);}
    void insertarinicio(L &dato);
    void insertarFinal(L &dato);
    void insertar(Iterator<L> &i, L &dato);
    void borrarInicio();
    void borrarFinal(Iterador<L> &i);
    L &inicio();
    L &final();
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
            Nodo<T> aux=cabecera;
            cabecera=cabecera->sig;
            delete aux;
        }
        if(origen.cabecera==0) {
            cola=0;
            cabecera=0;
            tam=0;
        }else {
            cabecera=origen.cabecera;
            cola=orig.cola;
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
    Iterador<L> i= cabecera;
    return i.dato();
}
/**
 * @brief Metodo que devuelve el ultimo dato elemento de la lista
 * @return Dato al final de la lista
 */
template<typename L>
L &ListaEnlazada<L>::fin() {
    Iterador<L> i= cola;
    return i.dato();
}

/**
 * @brief Metodo que inserta al comienzo de la lista
 * @param dato Dato que se introduce
 * @post La funcion añade un nuevo dato al comienzo de la lista, sustituyendo al que en ese momento sea la cabecera. Si no hubiera un dato, este seria tambien la cola
 */
template<typename L>
void ListaEnlazada<L>::insertaInicio(L &dato) {
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
void ListaEnlazada<L>::insertaFin(L &dato) {
    Nodo<L> *nuevo = new Nodo<L>(dato, cola); //aqui lo que hago es crear el nuevo nodo y ademas hago que apunte al actual ultimo
    if (cola == 0) {
        cola = nuevo;
        cabecera = nuevo;
    }
    cola = nuevo;
    tam++;
}

template<typename L>
void ListaEnlazada<L>::insertaDetras(Iterador &i, L &dato) {
    Nodo<L> *nuevo = new Nodo<L>(dato, i->);

}





#endif //PRACTICA2_LISTA_H