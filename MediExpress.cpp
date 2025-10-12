#include "MediExpress.h"
MediExpress::MediExpress():
medication(),labs()
{}

MediExpress::MediExpress(const std::string &medicamentos, const std::string &laboratorios) {
    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;

    std::string id_number_string = "";
    std::string id_alpha="";
    std::string nombre="";



    is.open(medicamentos); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_number;id_alpha;nombre;

                getline(columnas, id_number_string, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, id_alpha,';');
                getline(columnas, nombre,';');

                int id_num = 0;
                try {
                    id_num = std::stoi(id_number_string); ///Esta funcion pasa de string a int
                }catch (std::invalid_argument &e) {
                    std::cerr<<e.what()<<std::endl;
                }

                PaMedicamento medicamento(id_num,id_alpha,nombre);
                try {
                    medication.insertar(medicamento);
                }catch (std::out_of_range &e) {
                    std::cerr<<e.what()<<std::endl;
                }

                fila="";
                columnas.clear();

                std::cout << ++contador
                          << " Medicamento: ( Id_number=" << id_num
                          << " id_alpha=" << id_alpha << " Nombre=" << nombre
                          << ")" << std::endl;
            }
        }

        is.close();

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    //Leemos el segundo fichero

    std::string id_numero_string = "";
    std::string nombreLab_ = "";
    std::string direccion_="";
    std::string codigPostal_="";
    std::string localidad_="";


    is.open(laboratorios); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_;direccion;codigPostal_;localidad_

                getline(columnas, id_numero_string, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, nombreLab_, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, direccion_, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, codigPostal_,';');
                getline(columnas, localidad_,';');

                int id_numero = 0;
                try {
                    id_numero = std::stoi(id_numero_string); ///Esta funcion pasa de string a int
                }catch (std::invalid_argument &e) {
                    std::cerr<<e.what()<<std::endl;
                }

                fila="";
                columnas.clear();

                Laboratorio lab(id_numero,nombreLab_,direccion_,codigPostal_,localidad_);
                try {
                    ListaEnlazada<Laboratorio>::Iterador it = labs.iterador();
                    while (!it.fin() && it.dato().getId() < id_numero) {
                        it.siguiente();
                    }
                    labs.insertar_delante(it,lab);
                }catch (std::out_of_range &e) {
                    std::cerr<<e.what()<<std::endl;
                }


                std::cout << ++contador
                          << " Laboratorio: ( Id= " << id_numero
                          << " Nombre= " << nombreLab_ << " Direccion= " << direccion_
                          << " Codigo Postal= " <<codigPostal_
                          << " Localidad= "<< localidad_ <<std::endl;
            }
        }

        is.close();

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    std::cout << std::endl;
}

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

VDinamico<PaMedicamento> MediExpress::get_medication() const {
    return medication;
}

void MediExpress::set_medication(const VDinamico<PaMedicamento> &medication) {
    this->medication = medication;
}

ListaEnlazada<Laboratorio> MediExpress::get_labs() const {
    return labs;
}

void MediExpress::set_labs(const ListaEnlazada<Laboratorio> &labs) {
    this->labs = labs;
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