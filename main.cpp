#include <iostream>
#include "Lista.h"
#include "VDinamico.h"
#include "Laboratorio.h"
#include "MediExpress.h"
#include "PaMedicamento.h"

void mostrarLista(ListaEnlazada<int> &l) {
    ListaEnlazada<int>::Iterador<int> it = l.iterador();
    while (!it.fin()) {
        std::cout<<it.dato()<<std::endl;
        it.siguiente();
    }
}

/**
 * @author Pablo Rodríguez Gniadek prg00054@red.ujaen.es
 * @author Marco Díaz Vera mdv00011@red.ujaen.es
 */
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

    //Parte 2
    MediExpress mediexpress("../pa_medicamentos.csv","../lab2.csv");
    VDinamico<Laboratorio *> labsGranada =mediexpress.buscarLabCiudad("Granada");
    std::cout<<"\n";
    std::cout<<"Laboratorios de Granada: "<<std::endl;
    for (int i=0;i<labsGranada.tamlog_();i++) {
        std::cout<<labsGranada[i]->getNomrbeLab()<<" "<<std::endl;
    }
    std::cout<<"\n";
    VDinamico<Laboratorio *> labsJaen =mediexpress.buscarLabCiudad("Jaén");
    std::cout<<"En Jaen hay "<<labsJaen.tamlog_()<<" laboratorios"<<std::endl;
    VDinamico<Laboratorio *> labsMadrid =mediexpress.buscarLabCiudad("Madrid");
    std::cout<<"En Madrid hay "<<labsMadrid.tamlog_()<<" laboratorios y los 10 primeros son: "<<std::endl;
    for (int i=0;i<10;i++) {
        std::cout<<labsMadrid[i]->getNomrbeLab()<<" "<<std::endl;
    }
    std::cout<<"\n";
    VDinamico<PaMedicamento*> labsAceite= mediexpress.buscaCompuesto("ACEITE");
    std::cout<<"Los laboratorios cuyos principios activos poseen aceite son: "<<std::endl;
    for (int i = 0; i < labsAceite.tamlog_(); i++) {
        std::cout<<labsAceite[i]->getServe()->getNomrbeLab()<<" que tiene : "<<labsAceite[i]->get_nombre()<<std::endl;
    }
    VDinamico<PaMedicamento*> labsSin = mediexpress.getMedicamentoSinLab();
    for (int i = 0; i < labsSin.tamlog_(); i++) {
        labsSin[i]->servidoPor(labsMadrid[i]);
    }
    try {
        mediexpress.borrarLaboratorio("Bruselas");
    }catch (std::invalid_argument& e) {
        std::cerr<<e.what()<<std::endl;
    }
    VDinamico<Laboratorio*> labsBruselas=mediexpress.buscarLabCiudad("Bruselas");
        std::cout<<"En Bruselas hay: "<<labsBruselas.tamlog_()<<" Laboratorios."<<std::endl;

    return 0;
}