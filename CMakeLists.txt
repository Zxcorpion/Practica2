cmake_minimum_required(VERSION 4.0)
project(Practica2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Practica2 main.cpp
        Lista.h
        VDinamico.h
        PaMedicamento.h
        Laboratorio.cpp
        Laboratorio.h
        MediExpress.cpp
        MediExpress.h)
