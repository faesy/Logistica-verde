#ifndef ListaSol_H_INCLUDED
#define ListaSol_H_INCLUDED
#include "Solucao.h"
#include "CriadorInstancias.h"
#include "Construtor.h"
#include <stdlib.h>

using namespace std;


class ListaSol{

    // Attributes
    private:


    public:
    CriadorInstancias *instancia;
    int tamanho;
    Solucao *primeira_sol;
    Solucao *ultima_sol;
    ListaSol(CriadorInstancias *instancia);
    void ConstruirSolucoes(int qtd_sol,ofstream &output_file);
    void Imprimir(Solucao *solucao,ofstream &output_file);
    void AdicionaSolucao(Solucao *sol);
    void RemoveSolucao(int id);
    Solucao* BuscaSol(int id);
    void ImprimirPython(ofstream &output_file,int num);
    //void AnaliseDeFrentes();
    //void ZeraFrentes();
    //void RemoveXsol(int x);

    
};

#endif 