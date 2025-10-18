#ifndef MEDIEXPRESS_H
#define MEDIEXPRESS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "PaMedicamento.h"
#include "Laboratorio.h"
#include "VDinamico.h"
#include "Lista.h"


class MediExpress {
private:
    VDinamico<PaMedicamento> medication;
    ListaEnlazada<Laboratorio> labs;
public:
    MediExpress();
    MediExpress(const std::string &medicamentos, const std::string &laboratorios);
    MediExpress(const MediExpress &orig);
    ~MediExpress();

    MediExpress& operator=(const MediExpress &orig);


    void set_medication(const VDinamico<PaMedicamento> &medication);
    void set_labs(const ListaEnlazada<Laboratorio> &labs);

    void suministrarMed(PaMedicamento *pa,Laboratorio *l);
    Laboratorio *buscarLab(const std::string &nombreLab);
    VDinamico<Laboratorio*> buscarLabCiudad(const std::string &nombreCiudad);
    VDinamico<PaMedicamento*> buscaCompuesto(const std::string &nombrePA);
    VDinamico<PaMedicamento*> getMedicamentoSinLab();
    void borrarLaboratorio(const std::string &nombreCiudad);
};



#endif //MEDIEXPRESS_H