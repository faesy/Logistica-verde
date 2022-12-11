#ifndef Lista_H_INCLUDED
#define Lista_H_INCLUDED
#include "ElementoDaLista.h"

using namespace std;


class Lista{

    // Attributes
    private:


    public:
    int tamanho;
    ElementoDaLista* primeiro_elemento;
    ElementoDaLista* ultimo_elemento;
    Lista();
    void Adicionar_na_Lista(int id_maquina,int qtd);
    void Remove_na_Lista(int id_maquina,int qtd);
    int Sorteia_na_Lista();
    void Zera_Lista();
    void Imprime();
    
};

#endif 