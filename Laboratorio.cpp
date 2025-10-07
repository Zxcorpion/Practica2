//
// Created by admin on 07/10/2025.
//

#include "Laboratorio.h"
Laboratorio::Laboratorio(int id_, std::string nombreLab_, std::string direccion_, std::string codiPostal_,std::string localidad_):
id(id_),
nombreLab(nombreLab_),
direccion(direccion_),
codiPostal(codiPostal_),
localidad(localidad_)
{}


Laboratorio::Laboratorio(const Laboratorio &orig):
id(orig.id),
nombreLab(orig.nombreLab),
direccion(orig.direccion),
codiPostal(orig.codiPostal),
localidad(orig.localidad)

{}
Laboratorio::~Laboratorio() {}

int Laboratorio::getId() const {
    return id;
}

void Laboratorio::setId(int id) {
    Laboratorio::id = id;
}

const std::string &Laboratorio::getNomrbeLab() const {
    return nombreLab;
}

void Laboratorio::setNomrbeLab(const std::string &nomrbeLab) {
    Laboratorio::nombreLab = nomrbeLab;
}

const std::string &Laboratorio::getDireccion() const {
    return direccion;
}

void Laboratorio::setDireccion(const std::string &direccion) {
    Laboratorio::direccion = direccion;
}

const std::string &Laboratorio::getCodiPostal() const {
    return codiPostal;
}

void Laboratorio::setCodiPostal(const std::string &codiPostal) {
    Laboratorio::codiPostal = codiPostal;
}

const std::string &Laboratorio::getLocalidad() const {
    return localidad;
}

void Laboratorio::setLocalidad(const std::string &localidad) {
    Laboratorio::localidad = localidad;
}
