#ifndef ListaPopulacao_H_INCLUDED
#define ListaPopulacao_H_INCLUDED
#include "Solucao.h"
#include "Instancia.h"
#include "Construtivo.h"
#include <stdlib.h>

using namespace std;


class ListaPopulacao{

    // Attributes
    private:


    public:
    //Instancia *instancia;
    int tamanho;
    Solucao *primeira_sol;
    Solucao *ultima_sol;
    ListaPopulacao(Instancia *instancia);
    void ConstruirSolucoes(int qtd_sol,ofstream &output_file,Instancia* instancia);
    void Imprimir(Solucao *solucao,ofstream &output_file,Instancia* instancia);
    void AdicionaSolucao(Solucao *sol);
    Solucao* BuscaSol(int id);
    void ImprimirPython(ofstream &output_file,int num);
    //void AnaliseDeFrentes();
    //void ZeraFrentes();
    //void RemoveXsol(int x);

    
};

#endif 