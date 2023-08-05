#include "Lista.h"

Lista::Lista(): prim(nullptr), tail(nullptr), long_(0) {

}


Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar
    // el código de la copia de una lista.
    Lista();
    Lista() = l;
    *this = l;
}

Lista::~Lista() {
    // Completar

    this-> destruirNodos();
}

Lista& Lista::operator=(const Lista& aCopiar) {
    // Checkiar que funcione bien esto
    this->destruirNodos();
    Nodo* temp = aCopiar.prim;

    if (aCopiar.prim != nullptr) {
        Nodo* temp2 = new Nodo(temp->valor);
        this->prim = temp2;
        temp = temp->sig;
        while(temp != nullptr){
            temp2->sig = new Nodo(temp->valor);
            temp2->sig->ant = temp2;
            temp = temp->sig;
            temp2 = temp2->sig;
        }
        this->tail = temp2;
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    // Completar
    Nodo* nuevo = new Nodo(elem);
    if (longitud() == 0) {
        tail = nuevo;
    }
    nuevo->valor = elem;
    nuevo->ant = nullptr;
    nuevo->sig = this->prim;
    prim = nuevo;
}

void Lista::agregarAtras(const int& elem) {
    Nodo* nuevo = new Nodo(elem);
    if(this->prim == nullptr){
        prim = nuevo;
    }
    nuevo->valor = elem;
    nuevo->sig = nullptr;
    nuevo->ant = tail;
    if(this->tail != nullptr){
        tail->sig = nuevo;
    }
    tail = nuevo;
}





void Lista::eliminar(Nat i) {
    // Completar

    //Tomamos como premisa que i va a estar en el rango de la Lista
    //Y que la lista no va a ser vacia

    Nodo* actual = prim;
    Nat j = 0;

    if (longitud() == 1){
        delete(actual);
        tail = nullptr;
        prim = nullptr;
        ult = nullptr;
    //Si long = 1, entonces me va a quedar vacio.
    }
    else{
        if (i == 0){
            prim = actual->sig;
            actual->ant= nullptr;
            actual->sig->ant = nullptr;
            //anula el siguiente del anterior del actual
            //osea la flecha q va del 1ro al actual. (un trabalenguas)
            delete(actual);
        }
        else{
            while( actual != nullptr) {
                if (j == i) {
                    if (i < longitud() - 1){
                        actual->sig->ant = actual->ant;
                        actual->ant->sig = actual->sig;
                        delete(actual);
                        break;
                    }
                    else{
                        tail = actual->ant;
                        actual->ant->sig = nullptr;
                        delete(actual);
                        break; //uso el break para que no itere actual
                               //sino estaria iterando sobre algo que ya no existe

                    }
                }
                actual = actual->sig;
                j++;
            }
        }
    }
}

int Lista::longitud() const {
    // Completar
    int cont = 0;
    Nodo* actual = prim;
    while(actual != nullptr){
        actual = actual -> sig;
        cont++;

    }
    return cont;
}



const int& Lista::iesimo(Nat i) const {
    // Completar
    Nodo* actual= prim;
    int counter = 0;
    while(actual != nullptr) {
        if (counter == i){
            return actual->valor;
        }
        actual = actual->sig;
        counter++;
    }
}

int& Lista::iesimo(Nat i) {
    // Completar (hint: es igual a la anterior...)
    Nodo* temp = prim;
    int counter = 0;
    while(temp != nullptr) {
        if (counter == i){
            return temp->valor;
        }
        temp = temp->sig;
        counter++;

    }
}

void Lista::copiarNodos(const Lista &o) {
    Nodo* actual = o.prim;
    while(actual != nullptr){
        agregarAtras(actual->valor);
        actual = actual->sig;
    }
}

void Lista::destruirNodos() {
    Nodo* actual = prim;
    while(actual != nullptr){
        Nodo* siguiente = actual->sig;
        delete actual;
        actual = siguiente;
    }
    prim = nullptr;
}

void Lista::mostrar(ostream& o) {
    // Completar
}

