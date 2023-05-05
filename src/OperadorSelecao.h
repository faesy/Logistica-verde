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
    void crossover1(Solucao* parente1,Solucao* parente2,ListaSol *listaNova);//unitario
    void crossover2(Solucao* parente1,Solucao* parente2,ListaSol *listaNova);//2 pontos de corte
    void mutacao(Solucao* alvo,int chancePorJob);

};

#endif 