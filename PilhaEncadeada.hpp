#ifndef PILHA_ENCADEADA_HPP
#define PILHA_ENCADEADA_HPP



template <typename T>
struct No{
    T info;
    No <T> *eloA, *eloP;
};

template <typename T>
struct Pilha{
    No <T> *comeco, *fim;
};

template <typename T>
void inicializar(Pilha <T> &p){
    p.comeco = NULL;
    p.fim = NULL;
}

template <typename T>
bool vazia(Pilha <T> p){
    return (p.fim == NULL) ? true : false;
}

template <typename T>
bool cheia(Pilha <T> p){
    return false;
}

template <typename T>
bool push(Pilha <T> &p, T valor){
    No <T> *novo = new No<T>;

    if( novo == NULL ) return false;
    novo->info = valor;
    novo->eloP = NULL;
    novo->eloA = NULL;

    if( p.comeco == NULL ){
        p.comeco = novo;
        p.fim = novo;
    }
    else{
        p.fim->eloP = novo;
        novo->eloA = p.fim;
        p.fim = novo;
    }
    return true;
}

template <typename T>
bool pop(Pilha <T> &p, T &valor){
    if( vazia(p) ) return false;

    No <T> *aux = p.fim;
    if( aux == NULL ) return false;
    valor = aux->info;

    if( aux == p.comeco && aux == p.fim  ){
        p.comeco = NULL;
        p.fim = NULL;
    }
    else {
        p.fim = aux->eloA;
        p.fim->eloP = NULL;
    }
    delete aux;
    return true;
}

template <typename T>
bool top(Pilha <T> &p, T &valor){
    if( vazia(p) ) return false;
    valor = p.fim->info;
    return true;
}

template <typename T>
void liberar(Pilha <T> &p){
    No <T> *aux = p.comeco;
    No <T> *aux2;
    while( aux != NULL ){
        aux2 = aux;
        aux = aux->eloP;
        delete aux2;
    }
}

// namespace PilhaEncadeada

#endif
