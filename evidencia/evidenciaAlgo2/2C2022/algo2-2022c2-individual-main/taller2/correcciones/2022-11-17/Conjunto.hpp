
#include "Conjunto.h"

//Constructor de nodo
template<class T>
Conjunto<T>::Nodo::Nodo(const T &v) : valor(v), izq(nullptr), der(nullptr) {};

//Constructor
template <class T>
Conjunto<T>::Conjunto() : _cardinal(0), _raiz(nullptr){};


template <class T>
Conjunto<T>::~Conjunto() { 
    // Completar
    this ->destruir(_raiz);
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    bool esta = false;
    if (_raiz == nullptr){
        esta = false;
    }
    if (_raiz != nullptr && _raiz->valor == clave){
        esta = true;
    }
    if( _raiz != nullptr && _raiz->valor != clave){
        Nodo* actual = _raiz;
        while (actual != nullptr){
            if (actual->valor == clave){
                esta = true;
                break;
            }
            else{
                if (actual->valor > clave){
                    actual = actual->izq;
                }
                else{
                    actual = actual->der;
                }
            }
        }
        if (actual == nullptr){
            esta = false;
        }
    }
    return esta;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {

    if ( _raiz != nullptr){
        Nodo* actual = _raiz;

        while (actual->valor != clave && !pertenece(clave)){

            if (actual->valor > clave){

                if (actual->izq == nullptr){
                //si el izq es nullptr, creo nuevo nodo e inserto valor
                    Nodo* hijo = new Nodo(clave);
                    actual->izq = hijo;
                    _cardinal++;
                } //sino sigo mi loop
                else{
                    actual = actual->izq;
                }
            }
            else{
                if (actual->valor < clave){

                    if(actual->der == nullptr){
                        Nodo* hijo = new Nodo(clave);
                        actual->der = hijo;
                        _cardinal++;
                    }
                    else{
                        actual = actual->der;
                    }
                }
            }
        }
        if (actual == nullptr){
            actual->valor = clave;

        }
    }
    if (_raiz == nullptr){
        Nodo* nuevo = new Nodo(clave);
        _raiz = nuevo;
        _cardinal++;
    }
}


template <class T>
void Conjunto<T>::remover(const T& clave) {

    if (pertenece(clave)) {
        Nodo *actual = _raiz;
        Nodo *padre = nullptr;
        while (actual->valor != clave) {
            padre = actual;
            if (actual->valor > clave) {
                actual = actual->izq;
            } else {
                actual = actual->der;
            }
        }// actual es ahora el nodo con el valor de clave, padre (en caso de haber) es el padre de actual
        if (actual->izq == nullptr && actual->der == nullptr) {//borrar hoja
            if (padre != nullptr) {
                if (padre->valor > actual->valor) { padre->izq = nullptr; }
                else { padre->der = nullptr; }

            } else {//es la raiz
                _raiz = nullptr;
            }
            delete actual;
        } else {///borra el nodo que tiene una sola rama y lo reemplaza por la unica rama que tiene
            if (actual->izq == nullptr) { //actual solo tiene rama derecha
                if (padre == nullptr) {//es raiz
                    _raiz = actual->der;
                    delete actual;
                } else {
                    if (padre->valor < actual->valor) {//encuentra la direccion
                        padre->der = actual->der;
                    } else {
                        padre->izq = actual->der;
                    }
                    delete actual;
                }
            } else {
                if (actual->der == nullptr) { //actual solo tiene rama izquierda
                    if (padre == nullptr) {//es raiz
                        _raiz = actual->izq;
                        delete actual;
                    } else {
                        if (padre->valor < actual->valor) {//encuentra si actual venia por la rama izq o der
                            padre->der = actual->izq;
                        } else {
                            padre->izq = actual->izq;
                        }
                        actual->izq = nullptr;
                        delete actual;
                    }
                } else { /// actual tiene dos ramas
                    Nodo *sig = actual->der;
                    Nodo *padreSig = actual;
                    while (sig->izq != nullptr) {
                        padreSig = sig;
                        sig = sig->izq;
                    }
                    if (padreSig->valor == actual->valor){
                        padreSig->der = sig->der;
                    } else {
                        padreSig->izq = sig->der;
                    }
                    actual->valor = sig->valor;
                    delete sig;
                }
            }
        }
        _cardinal--;
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    ///suponemos que el elemento esta en el ABB, y que tiene al menos 1 hijo
    Nodo* actual = _raiz;
    Nodo* padre = nullptr;
    Nodo* nuevo = _raiz;
    while (actual->valor != clave){
        if (actual->valor < clave){
            padre = actual;
            actual = actual->der;
        }
        else{
            padre = actual;
            actual = actual->izq;
        } ///navego
    }
    if (actual->valor == clave){
        if (actual->der != nullptr){
            padre = actual;
            actual = actual->der;
            while(actual->valor > padre->valor){
                if (actual->izq != nullptr && actual->izq->valor > padre->valor){
                    actual = actual->izq;
                }
                if (actual->izq == nullptr){
                    break;
                }

            }
            return actual->valor;
        } /// Si la clave tiene hijo der, printeo eso

        if (actual->der == nullptr){ ///sino, 2 casos:
            if (padre->valor > actual->valor){
                return padre->valor;
            }                        /// o actual es rama izq de padre (padre.valor > actual.valor)

            if (padre->valor < actual->valor){
                while ((nuevo->izq->valor < actual->valor && nuevo->der->valor > actual->valor) == false && nuevo->valor < actual->valor){
                    if (nuevo->valor < actual->valor){
                        nuevo = nuevo->der;
                    }
                    else{
                        nuevo = nuevo->izq;
                    }
                }
                return nuevo->valor;
            }                        /// o actual es rama der de padre (padre.valor < actual.valor)
        }
    }
}


template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* actual = _raiz;
    Nodo* padre = nullptr;
    if( _raiz->izq == nullptr ){
        return _raiz->valor;
    }
    else{
        while(actual != nullptr){
            padre = actual;
            actual = actual->izq;
        }
    }
    return padre->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* actual = _raiz;
    Nodo* padre = nullptr;
    if( _raiz->izq == nullptr ){
        return _raiz->valor;
    }
    else{
        while(actual != nullptr){
            padre = actual;
            actual = actual->der;
        }
    }
    return padre->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return this->_cardinal;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

template <class T>
void Conjunto<T>::destruirABB(){
    Nodo* actual = _raiz;
    while(actual != nullptr){
        Nodo* hijoIzq = actual->izq;
        Nodo* hijoDer = actual->der;

        delete actual;
        actual = hijoDer;
        actual = hijoIzq;
    }
    _raiz = nullptr;
}

template<class T>
void Conjunto<T>::destruir(Conjunto::Nodo *n) {
    if(n != nullptr) {
        destruir(n->izq);
        destruir(n->der);
        delete (n);
        _cardinal--;
    }
}
