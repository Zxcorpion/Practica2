//
// Created by marco on 11/10/2025.
//

#ifndef MEDIEXPRESS_H
#define MEDIEXPRESS_H



#include <iostream>
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
    MediExpress(const MediExpress &orig);
    ~MediExpress();
    MediExpress& operator=(const MediExpress &orig);
    void suministrarMed(PaMedicamento pa,Laboratorio l);
    Laboratorio buscarLab(const std::string &nombreLab);
    VDinamico<Laboratorio*> buscarLabCiudad(const std::string &nombreCiudad);
    VDinamico<PaMedicamento*> buscaCompuesto(std::string nombrePA);
};



#endif //MEDIEXPRESS_H
