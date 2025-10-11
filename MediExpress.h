//
// Created by admin on 07/10/2025.
//

#ifndef PRACTICA2_MEDIEXPRESS_H
#define PRACTICA2_MEDIEXPRESS_H
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

    void suministrarMed(PaMedicamento pa, Laboratorio l);
    Laboratorio buscarLab(std::string nombreLab);
    VDinamico<Laboratorio*> buscarLabCiudad(std::string nombreCiudad);
    VDinamico<PaMedicamento*> buscaCompuesto(std::string nombrePA);
};


#endif //PRACTICA2_MEDIEXPRESS_H
