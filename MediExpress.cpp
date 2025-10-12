//
// Created by marco on 11/10/2025.
//

#include "MediExpress.h"
MediExpress::MediExpress():
medication(),labs()
{}
MediExpress::MediExpress(const MediExpress &orig):
medication(orig.medication),labs(orig.labs)
{}
MediExpress &MediExpress::operator=(const MediExpress &orig) {
    if(this!=&orig) {
        medication = orig.medication;
        labs = orig.labs;
    }
    return *this;
}
MediExpress::~MediExpress() {
}

void MediExpress::suministrarMed(PaMedicamento pa, Laboratorio l) {
    pa.servidoPor(&l);
}

Laboratorio MediExpress::buscarLab(const std::string &nombreLab) {
    ListaEnlazada<Laboratorio>::Iterador<Laboratorio> aux=labs.iterador();
    for(int i = 0; i < labs.get_tam(); i++){
        if(aux.dato().getNomrbeLab().find(nombreLab) != std::string::npos){
            return aux.dato();
        }else{
            aux.siguiente();
        }
    }
    return 0;
}
VDinamico<Laboratorio*> MediExpress::buscarLabCiudad(const std::string &nombreCiudad) {
    VDinamico<Laboratorio*> vector;
    ListaEnlazada<Laboratorio>::Iterador<Laboratorio> aux=labs.iterador();
    for(int i = 0; i < labs.get_tam(); i++) {
        if(aux.dato().getLocalidad().find(nombreCiudad) != std::string::npos) {
            vector.insertar(&aux.dato());
        }
        aux.siguiente();
    }
        return vector;
}
VDinamico<PaMedicamento*> MediExpress::buscaCompuesto(std::string nombrePA) {
        VDinamico<PaMedicamento*>auxiliar;
        for(unsigned int i=0;i<medication.tamlog_();i++) {
            if(medication[i].get_nombre().find(nombrePA) != std::string::npos) {
                auxiliar.insertar(&medication[i]);
            }
        }
        return auxiliar;
    }


