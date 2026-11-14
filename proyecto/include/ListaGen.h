#ifndef LISTAGEN_H
#define LISTAGEN_H

#include <iostream>

template <typename T>
struct NodoGen {
    T dato;
    NodoGen<T>* siguiente;

    NodoGen(T _dato) {
        dato = _dato;
        siguiente = nullptr;
    }
};

template <typename T>
class ListaGen {
private:
    NodoGen<T>* head;

public:
    ListaGen() {
        head = nullptr;
    }

    ~ListaGen() {
        NodoGen<T>* actual = head;

        while (actual != nullptr) {
            NodoGen<T>* siguienteNodo = actual->siguiente;
            delete actual->dato;
            delete actual;
            actual = siguienteNodo;
        }

        head = nullptr;
    }

    // Inserta al inicio: O(1).
    void insertar(T nuevoDato) {
        NodoGen<T>* nuevo = new NodoGen<T>(nuevoDato);
        nuevo->siguiente = head;
        head = nuevo;
    }

    void procesarTodo() {
        NodoGen<T>* actual = head;

        while (actual != nullptr) {
            actual->dato->procesarLectura();
            actual = actual->siguiente;
        }
    }

    // Busca por ID recorriendo la lista: O(n).
    T buscarPorID(int idBusqueda) {
        NodoGen<T>* actual = head;

        while (actual != nullptr) {
            if (actual->dato->getId() == idBusqueda) {
                return actual->dato;
            }
            actual = actual->siguiente;
        }

        return nullptr;
    }

    void eliminarInicio() {
        if (head == nullptr) {
            return;
        }

        NodoGen<T>* temporal = head;
        head = head->siguiente;

        delete temporal->dato;
        delete temporal;
    }

    void eliminarPorID(int idBusqueda) {
        if (head == nullptr) {
            return;
        }

        if (head->dato->getId() == idBusqueda) {
            eliminarInicio();
            return;
        }

        NodoGen<T>* actual = head;

        while (actual->siguiente != nullptr &&
               actual->siguiente->dato->getId() != idBusqueda) {
            actual = actual->siguiente;
        }

        if (actual->siguiente != nullptr) {
            NodoGen<T>* temporal = actual->siguiente;
            actual->siguiente = temporal->siguiente;
            delete temporal->dato;
            delete temporal;
        }
    }

    void filtrarLecturasCriticas(double limite) {
        NodoGen<T>* actual = head;

        while (actual != nullptr) {
            if (actual->dato->getLectura() > limite) {
                std::cout << "[LECTURA CRITICA] "
                          << *actual->dato << std::endl;
            }
            actual = actual->siguiente;
        }
    }
};

#endif
