#include <iostream>
#include "Lista.h"
#include "VDinamico.h"
#include "Laboratorio.h"
#include "PaMedicamento.h"

void mostrarLista(ListaEnlazada<int> &l) {
    ListaEnlazada<int>::Iterador<int> it = l.iterador();
    while (!it.fin()) {
        std::cout<<it.dato()<<std::endl;
        it.siguiente();
    }
}


int main() {
    ListaEnlazada<int> listaEnteros;
    for (int i = 101; i <= 200; i++){
        listaEnteros.insertarFinal(i);
    }
    for (int i = 98; i>=1; i--) {
        listaEnteros.insertarinicio(i);
    }

    ListaEnlazada<int>::Iterador<int> it = listaEnteros.iterador();
    while (!it.fin() && it.dato() != 101) {
        it.siguiente();
    }
    int dato1=100;
    int dato2=99;

    if (!it.fin()) {
        listaEnteros.insertar_delante(it,dato1);
    }
    it = listaEnteros.iterador(); //Reiniciamos el iterador ya que este apunta al nodo 101
    while (!it.fin() && it.dato() != 98) {
        it.siguiente();
    }
    if (!it.fin()) {
        listaEnteros.insertarDetras(it,dato2);
    }

    mostrarLista(listaEnteros);
    std::cout<<"\n";
    std::cout<<"Borrado"<<std::endl;
    std::cout<<"\n";

    it = listaEnteros.iterador();
    for (int i = 0; i < 10; i++) {
        listaEnteros.borrarFinal();
        listaEnteros.borrarInicio();
    }
    mostrarLista(listaEnteros);

    it = listaEnteros.iterador();
    while (!it.fin()) {
        if (it.dato() % 10 == 0) {
            listaEnteros.borrar(it);
            it = listaEnteros.iterador(); //tenemos que resetear el iterador para que tenga los indices correctos
        } else {
            it.siguiente();
        }
    }
    mostrarLista(listaEnteros);

    return 0;
}