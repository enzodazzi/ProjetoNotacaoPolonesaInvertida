#ifndef FILA_ENCADEADA_HPP
#define FILA_ENCADEADA_HPP



template <typename T>
struct no{
    T info;
    No <T> *eloA, *eloP;
};

template <typename T>
struct Fila{
    No <T> *comeco, *fim;
};

template <typename T>
void inicializar(Fila <T> &f){
    f.comeco = NULL;
    f.fim = NULL;
}

template <typename T>
bool vazia(Fila <T> f){
    return (f.fim == NULL) ? true : false;
}

template <typename T>
bool cheia(Fila <T> p){
    return false;
}

template <typename T>
bool queue(Fila <T> &f, T valor){
    No <T> *novo = new No<T>;

    if( novo == NULL ) return false;
    novo->info = valor;
    novo->eloP = NULL;
    novo->eloA = NULL;

    if( f.comeco == NULL ){
        f.comeco = novo;
        f.fim = novo;
    }
    else{
        f.fim->eloP = novo;
        novo->eloA = f.fim;
        f.fim = novo;
    }
    return true;
}

template <typename T>
bool dequeue(Fila <T> &f, T &valor){
    if( vazia(f) ) return false;

    No <T> *aux = f.comeco;
    if( aux == NULL ) return false;
    valor = aux->info;

    if( aux == f.comeco && aux == f.fim  ){
        f.comeco = NULL;
        f.fim = NULL;
    }
    else {
        f.comeco = aux->eloP;
        f.comeco->eloA = NULL;
    }
    delete aux;
    return true;
}

template <typename T>
void liberar(Fila <T> &f){
    No <T> *aux = f.comeco;
    No <T> *aux2;
    while( aux != NULL ){
        aux2 = aux;
        aux = aux->eloP;
        delete aux2;
    }
}



#endif
