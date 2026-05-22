#include <iostream>
#include <string>
#include <cctype> // Biblioteca necessária para isdigit e isalpha
#include <cmath>
#include "PilhaEncadeada.hpp"
#include "FilaEncadeada.hpp"

//#include <FilaCircular.hpp>
//#include "PilhaEstatica.hpp"
//#include <FilaEstatica.hpp>
using namespace std;
struct Variavel{
    char nome;
    float valor;
};
void InserirVarialvel (Pilha <Variavel> &v, char t, float n = 0){
    Pilha<Variavel> aux;

    Variavel a, temp;

    bool existe = false;

    inicializar(aux);

    // Procura variável na pilha
    while(!vazia(v)){
        pop(v, temp);
        if(temp.nome == t){
            existe = true;
        }
        push(aux, temp);
    }

    // Reconstrói pilha original
    while(!vazia(aux)){
        pop(aux, temp);
        push(v, temp);
    }

    // Insere apenas se não existir
    if(!existe){
        a.nome = t;
        a.valor = n;
        push(v, a);
    }

}

int Prioridade (char op){

    if(op == '(' || op == '[' || op == '{') return 1;

    if(op == '^') return 4;

    if(op == '*' || op == '/') return 3;

    if(op == '+' || op == '-') return 2;

    return -1;
}
void InserirOperador(Pilha<char>& operadores,Fila<char>& saida,char op){

    char t;
    int prioridadeAtual = Prioridade(op);
    int prioridadeTopo;

    // Se a pilha estiver vazia, apenas empilha
    if(vazia(operadores)){
        push(operadores, op);
        return;
    }

    //aberturas vão direto para pilha
    if(prioridadeAtual == 1 or prioridadeAtual == 4){
        push(operadores, op);
        return;
    }

    // Enquanto existir operador de prioridade maior no topo
    do{

        if(!vazia(operadores)){
            top(operadores, t);
            prioridadeTopo = Prioridade(t);
        }

        // Desempilha operadores de prioridade maior
        if(prioridadeTopo >= prioridadeAtual){
            pop(operadores, t);
            queue(saida, t);
        }

    }while(prioridadeTopo > prioridadeAtual and !vazia(operadores));

    // Empilha operador atual
    push(operadores, op);
}




bool NotacaoPolonesa(string expressao, Fila <char> &saida, Pilha <Variavel> &v ){
    Pilha <char> operadores;
    inicializar(operadores);
    bool temVariavel = false;
    char t;
    int prioridadeP, prioridadeS ;
    if (expressao.empty())return false;

    for(int i=0; i < expressao.length(); i++){
        prioridadeS = Prioridade(expressao[i]);
        if(isdigit(expressao[i]) or isalpha(expressao[i])) {
            queue(saida, expressao[i]);
            if(isalpha(expressao[i])){
                InserirVarialvel(v,expressao[i]);
            }
            temVariavel = true;
        }else if(expressao[i] == ')' or expressao[i] == '}' or expressao[i] == ']'){

            do{
                if(vazia(operadores)) return false;
                top(operadores,t);
                prioridadeP = Prioridade(t);
                if(prioridadeP > 1){
                    pop(operadores,t);
                    queue(saida,t);
                }

            }while(prioridadeP > 1);
            pop(operadores, t);

            // Verifica se o fechamento corresponde corretamente
            if((expressao[i] == ')' && t != '(') ||
               (expressao[i] == ']' && t != '[') ||
               (expressao[i] == '}' && t != '{')
            )return false;


        }else if (prioridadeS != -1){

            InserirOperador(operadores,saida,expressao[i]);

        }else{
            return false;

        }

    }

    while(!vazia(operadores)){

        pop(operadores,t);

        if(t == '(' || t == '[' || t == '{')return false;

        queue(saida,t);
    }

    return temVariavel;
}

void ExibirNotacao(Fila<char> saida){

    Fila<char> aux;
    char c;

    inicializar(aux);

    cout << "Notacao Polonesa Invertida: ";

    while(!vazia(saida)){

        dequeue(saida, c);
        cout << c;
        queue(aux, c);
    }

    cout << endl;

    // Reconstrói a fila original
    while(!vazia(aux)){

        dequeue(aux, c);
        queue(saida, c);
    }
}

void LerVariaveis(Pilha<Variavel>& v){
    Pilha<Variavel> aux;
    Variavel t;
    float valor;

    inicializar(aux);

    while(!vazia(v)){

        pop(v, t);

        cout << "Digite o valor de " << t.nome << ": ";
        cin >> valor;

        InserirVarialvel(aux,t.nome,valor);
    }

    // Reconstrói pilha
    while(!vazia(aux)){
        pop(aux, t);
        push(v,t);
    }
}


float ValorVariavel(Pilha<Variavel>& v, char letra){
    Pilha<Variavel> aux;
    Variavel temp;
    float valor;
    inicializar(aux);
    while(!vazia(v)){
        pop(v, temp);
        // Procura variável
        if(temp.nome == letra){
            valor = temp.valor;
        }
        push(aux, temp);
    }
    // Reconstrói pilha original
    while(!vazia(aux)){
        pop(aux, temp);
        push(v, temp);
    }
    return valor;
}


float Calcular(float a, float b, char op){

    switch(op){
        case '+':
            return a + b;

        case '-':
            return a - b;

        case '*':
            return a * b;

        case '/':
            return a / b;

        case '^':
            return pow(a, b);
    }

    return 0;
}

float ResultadoNotacao (Fila <char> &notacao, Pilha <Variavel> v){

    Pilha <float> resultado;
    char t;
    float n, m;

    inicializar(resultado);

    while(!vazia(notacao)){

        dequeue(notacao,t);

        if (isdigit(t)){
            n = t - '0';
            push(resultado,n);
        }else if (isalpha(t)){
            n = ValorVariavel(v,t);
            push(resultado,n);

        }else{
            pop(resultado,n);
            pop(resultado,m);
            n = Calcular(m,n,t);
            push(resultado,n);

        }

    }

    pop(resultado,n);

    return n;




}


int main()
{


    string expressao;
    Fila <char> saida;
    Pilha <Variavel> variaveis;
    inicializar(saida);
    inicializar(variaveis);

    float res;

    int op;


    cout<<"Insira uma expressão númérica: ";
    getline(cin, expressao);


    if(!NotacaoPolonesa(expressao,saida,variaveis)){
        cout << "expreção invalida";
    }else{
        ExibirNotacao(saida);
    }
    LerVariaveis(variaveis);


    res = ResultadoNotacao(saida,variaveis);
    cout << "resultado: "<<res;

    liberar(saida);
    liberar(variaveis);

    return 0;
}
