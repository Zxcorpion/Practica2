#include "MediExpress.h"

/**
 * @brief Constructor por defecto de la clase MediExpress
 * @post Se crea un objeto con los valores asignados por defecto
 */
MediExpress::MediExpress():
medication(),labs()
{}

/**
 * @brief Constructor parametrizado de la clase MediExpress
 * @param medicamentos pasados por referencia
 * @param laboratorios pasador por referencia
 * @post Se crea un objeto de la clase MediExpress con los valores pasados por cabecera
 */
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

    //Insertar
    ListaEnlazada<Laboratorio>::Iterador<Laboratorio> itLaboratorio = labs.iterador();
    int tam = 0;

    while (!itLaboratorio.fin() && tam +1 < medication.tamlog_()) {
        this->suministrarMed(&medication[tam],&itLaboratorio.dato());
        this->suministrarMed(&medication[tam+1],&itLaboratorio.dato());
        tam+=2;
        itLaboratorio.siguiente();
    }
    int cont=0;
    for (int i=0; i<medication.tamlog_(); i++){
        if (medication[i].getServe())
            std::cout << "ID del PaMedicamento: " << medication[i].get_id_num()<<
                ", ID del Laboratorio asociado: " << medication[i].getServe()->getId() << std::endl;
        else
            cont++;
    }
    std::cout << "Medicamentos sin asignar: " << cont << std::endl;
}

/**
 * @brief Constructor de copia de la clase MediExpress
 * @param orig objeto que vamos a copiar
 * @post Se crea un objeto de la clase MediExpress copiando el objeto pasado por cabecera
 */
MediExpress::MediExpress(const MediExpress &orig):
medication(orig.medication),labs(orig.labs)
{}
/**
 * @brief Operador de igualacion
 * @param orig objeto de la clase MediExpress del que quieren coger los datos
 * @return Devuelve *this ya modificado o no
 * @post El metodo asigna los mismos valores del objeto pasado por cabecera
 */
MediExpress &MediExpress::operator=(const MediExpress &orig) {
    if(this!=&orig) {
        medication = orig.medication;
        labs = orig.labs;
    }
    return *this;
}

/**
 * @brief Funcion para establecer un valor al atributo medication
 * @param medication valor que queremos asignar a medication
 * @post El atributo medication es modificado por un nuevo valor
 */
void MediExpress::set_medication(const VDinamico<PaMedicamento> &medication) {
    this->medication = medication;
}


/**
 * @brief Funcion para establecer un valor al atributo labs
 * @param labs valor que queremos asignar a nuestro atributo labs
 * @post El atributo labs es modificado por un nuevo valor
 */
void MediExpress::set_labs(const ListaEnlazada<Laboratorio> &labs) {
    this->labs = labs;
}

/**
 * @brief Destructor de los objetos MediExpress
 * @post Se libera la memoria
 */
MediExpress::~MediExpress() {
}

/**
 * @brief Funcion para asociar un laboratorio a un medicamento
 * @param pa Puntero de Pamedicamento
 * @param l Puntero de Laboratorio
 * @post PaMedicamento pasado por cabecera es asociado con un laboratorio
 */
void MediExpress::suministrarMed(PaMedicamento *pa, Laboratorio *l) {
    pa->servidoPor(l);
}

/**
 * @brief Funcion para buscar un laboratorio
 * @param nombreLab pasado por referencia
 * @return &aux.dato si se ha encontrado el laboratorio o 0 si no se ha encontrado
 */
Laboratorio *MediExpress::buscarLab(const std::string &nombreLab) {
    ListaEnlazada<Laboratorio>::Iterador<Laboratorio> aux=labs.iterador();
    for(int i = 0; i < labs.get_tam(); i++){
        if(aux.dato().getNomrbeLab().find(nombreLab) != std::string::npos){
            return &aux.dato();
        }else{
            aux.siguiente();
        }
    }
    return 0;
}

/**
 * @brief Funcion para buscar laboratorios de una ciudad
 * @param nombreCiudad pasada por referencia
 * @return vector con los laboratorios que se encuentran en la ciudad pasada por cabecera
 */
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

/**
 * @brief Funcion para buscar compuestos en un vector dinamico de PaMedicamento
 * @param nombrePA  pasado por referencia
 * @return vector con los medicamentos que contienen el nombre pasado por referencia
 * @post se crea un vector auxiliar y se inserta en el lo medicametnos convenientes
 */
VDinamico<PaMedicamento*> MediExpress::buscaCompuesto(const std::string &nombrePA) {
    VDinamico<PaMedicamento*>auxiliar;
    for(unsigned int i=0;i<medication.tamlog_();i++) {
        if(medication[i].get_nombre().find(nombrePA) != std::string::npos) {
            auxiliar.insertar(&medication[i]);
        }
    }
    return auxiliar;
}

/**
 * @brief Funcion para leer un vector de medicamentos que no tienen asociados un laboratorio
 * @return aux, vector con todos los medicamentos sin laboratorio asociado
 * @post se crea y se modifica un vector con medicamentos dentro del él
 */
VDinamico<PaMedicamento*> MediExpress::getMedicamentoSinLab() {
    VDinamico<PaMedicamento*> aux;
    for (int i=0;i< medication.tamlog_();i++) {
        if (!medication[i].getServe())
        aux.insertar(&medication[i]);
    }
    return aux;
}

/**
 * @brief Funcion para borrar laboratorios de forma correcta
 * @param nombreCiudad pasado por referencia
 * @post se borran todos los medicamentos que coinciden con el nombre pasado por referencia y desenlaza el laboratorio de sus medicamentos
 */
void MediExpress::borrarLaboratorio(const std::string &nombreCiudad) {
    ListaEnlazada<Laboratorio>::Iterador<Laboratorio> encontrado=labs.iterador();
    ListaEnlazada<Laboratorio>::Iterador<Laboratorio> aux;
    int cont=0;
    for(int i=0;i<medication.tamlog_();i++) {
        if(medication[i].getServe() !=nullptr && medication[i].getServe()->getLocalidad().find(nombreCiudad) != std::string::npos) {
            medication[i].servidoPor(nullptr);
        }else {
            cont++;
        }
    }
    if(cont==medication.tamlog_()) {
        throw std::invalid_argument("Error al localizar la localidad");
    }
    while(!encontrado.fin()) {
        if(encontrado.dato().getLocalidad().find(nombreCiudad) != std::string::npos) {
            aux=encontrado;
            aux.siguiente();
            labs.borrar(encontrado);
            encontrado=aux;
        }else
            encontrado.siguiente();
    }
}
