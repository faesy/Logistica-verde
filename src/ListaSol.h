#ifndef ListaSol_H_INCLUDED
#define ListaSol_H_INCLUDED
#include "Solucao.h"
#include "CriadorInstancias.h"
#include "Construtor.h"

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
    void ConstruirSolucoes(int qtd_sol);
    void AdicionaSolucao(Solucao *sol);
    void RemoveSolucao(int id);
    Solucao* BuscaSol(int id);
    //void AnaliseDeFrentes();
    //void ZeraFrentes();
    //void RemoveXsol(int x);
    
};

#endif 