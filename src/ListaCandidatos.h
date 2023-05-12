#ifndef ListaCandidatos_H_INCLUDED
#define ListaCandidatos_H_INCLUDED
#include "Candidato.h"

using namespace std;


class ListaCandidatos{

    // Attributes
    private:


    public:
    int tamanho;
    Candidato* primeiro_elemento;
    Candidato* ultimo_elemento;
    ListaCandidatos();
    void Adicionar_na_Lista(int id_maquina,int qtd);
    void Remove_na_Lista(int id_maquina,int qtd);
    int Sorteia_na_Lista();
    void Zera_Lista();
    void Imprime();
    
};

#endif 