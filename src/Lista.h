#ifndef Lista_H_INCLUDED
#define Lista_H_INCLUDED
#include "ElementoDaLista.h"

using namespace std;


class Lista{

    // Attributes
    private:
    ElementoDaLista* primeiro_elemento;
    ElementoDaLista* ultimo_elemento;


    public:
    void Adicionar_na_Lista(int id_maquina);
    void Remove_na_Lista(int id_maquina);
    int Sorteia_na_Lista();
    void Zera_Lista();
    
};

#endif 