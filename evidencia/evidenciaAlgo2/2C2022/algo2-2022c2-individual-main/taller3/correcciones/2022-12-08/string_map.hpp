template<typename T>
string_map<T>::string_map() {
    _raiz = new Nodo;
    _size = 0;
}

template<typename T>
string_map<T>::string_map(const string_map<T> &aCopiar) : string_map() { *this = aCopiar; }

template<typename T>
string_map<T> &string_map<T>::operator=(const string_map<T> &d) {
    delete _raiz;
    _raiz = new Nodo;
    for (string c : d._calves) {
        insert(make_pair(c, d.at(c)));
    }
}

template<typename T>
string_map<T>::~string_map() {
    delete _raiz;
}

template<typename T>
string_map<T>::Nodo::~Nodo() {
    if (significado != nullptr) {
        delete significado;
        significado = nullptr;
    }
    for (int i = 0; i < 256; i++) {
        if (siguientes[i] != nullptr) {
            delete siguientes[i];
        }
    }
}

template<typename T>
void string_map<T>::insert(const pair<string, T> &aDef) {
    Nodo *actual = _raiz;
    string clave = aDef.first;
    for (int i = 0; i < clave.size(); i++) {
        if (actual->siguientes[int(clave[i])] != nullptr) {
            actual = actual->siguientes[int(clave[i])];
        } else {
            actual->Hijos++;
            actual->siguientes[int(clave[i])] = new Nodo();
            actual = actual->siguientes[int(clave[i])];
        }
    }
    if (actual->significado != nullptr) {
        delete actual->significado;
    }
    actual->significado = new T(aDef.second);
    _size++;
    _calves.insert(aDef.first);
}

template<typename T>
T &string_map<T>::operator[](const string &clave) {

}


template<typename T>
int string_map<T>::count(const string &clave) const {
    /*int res = 0;
    if(size()!=0) {
        Nodo *actual = _raiz;
        for (int i = 0; i < clave.size(); i++) {
            if (actual->siguientes[int(clave[i])] != nullptr) {
                actual = actual->siguientes[int(clave[i])];
            }
            if (actual->significado != nullptr && i == clave.size() - 1) {
                res = 1;
            }
        }
        return res;
    }
     */
    return _calves.count(clave);
}

template<typename T>
const T &string_map<T>::at(const string &clave) const {
    Nodo *actual = _raiz;
    for (int i = 0; i < clave.size(); i++) {
        actual = actual->siguientes[int(clave[i])];
    }
    return *(actual->significado);
}

template<typename T>
T &string_map<T>::at(const string &clave) {
    Nodo *actual = _raiz;
    for (int i = 0; i < clave.size(); i++) {
        actual = actual->siguientes[int(clave[i])];
    }
    return *(actual->significado);
}

template<typename T>
void string_map<T>::erase(const string &clave) {
    if (_size == 1) {
        _size = 0;
        delete _raiz;
        _raiz = new Nodo;
        _calves.clear();
    } else {
        Nodo *actual = _raiz;
        Nodo *anterior = _raiz;
        Nodo *ultimoUtil = _raiz;
        int ultCharUtil = 0;
        for (int i = 0; i < clave.size(); i++) {
            if (actual->Hijos > 1 || actual->significado != nullptr) {
                ultimoUtil = actual;
                ultCharUtil = i;
            }
            anterior = actual;
            actual = actual->siguientes[int(clave[i])];
        }
        if (actual->Hijos > 0) {
            delete actual->significado;
            actual->significado = nullptr;
        } else {
            delete actual->significado;
            actual->significado = nullptr;
            ultimoUtil->Hijos--;
            if (ultimoUtil != _raiz) {
                Nodo *inutil = ultimoUtil->siguientes[int(clave[ultCharUtil])];
                ultimoUtil->siguientes[int(clave[ultCharUtil])] = nullptr;
                for (int j = ultCharUtil + 1; j < clave.size() - 1; j++) {
                    Nodo *proxInutil = inutil->siguientes[int(clave[j])];
                    delete inutil;
                    inutil = proxInutil;
                }

            }

        }
    }
    _size--;
    _calves.erase(clave);
}

template<typename T>
int string_map<T>::size() const {
    return this->_size;
}

template<typename T>
bool string_map<T>::empty() const {
    return (this->_size == 0);
}