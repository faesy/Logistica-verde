#ifndef OperadorSelecao_H_INCLUDED
#define OperadorSelecao_INCLUDED

using namespace std;
#include "ListaSol.h"
#include "Solucao.h"

class OperadorSelecao{

    // Attributes
    private:

    public:
    ListaSol* RealizaSelecao(ListaSol *listaInicial);
    Solucao* Vaga(ListaSol *listaInicial, int numContestantes);
    Solucao* crossover1(Solucao* parente1,Solucao* parente2);//unitario
    Solucao* crossover2(Solucao* parente1,Solucao* parente2);//2 pontos de corte

};

#endif 