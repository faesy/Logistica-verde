#ifndef OperadorSelecao_H_INCLUDED
#define OperadorSelecao_INCLUDED

using namespace std;
#include "ListaPopulacao.h"
#include "Solucao.h"

class OperadorSelecao{

    // Attributes
    private:

    public:
    ListaPopulacao* RealizaSelecao(ListaPopulacao *listaInicial,Instancia *instancia);
    Solucao* Vaga(ListaPopulacao *listaInicial, int numContestantes,Instancia *instancia);
    void crossover1(Solucao* parente1,Solucao* parente2,ListaPopulacao *listaNova, int chanceDeMut,Instancia *instancia);//unitario
    void crossover2(Solucao* parente1,Solucao* parente2,ListaPopulacao *listaNova, int chanceDeMut,Instancia *instancia);//2 pontos de corte
    void mutacao(Solucao* alvo,int chancePorJob,Instancia *instancia);

};

#endif 