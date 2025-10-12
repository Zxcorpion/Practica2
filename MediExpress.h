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

    VDinamico<PaMedicamento> get_medication() const;
    void set_medication(const VDinamico<PaMedicamento> &medication);
    ListaEnlazada<Laboratorio> get_labs() const;
    void set_labs(const ListaEnlazada<Laboratorio> &labs);

    void suministrarMed(PaMedicamento pa,Laboratorio l);
    Laboratorio buscarLab(const std::string &nombreLab);
    VDinamico<Laboratorio*> buscarLabCiudad(const std::string &nombreCiudad);
    VDinamico<PaMedicamento*> buscaCompuesto(std::string nombrePA);
};



#endif //MEDIEXPRESS_H