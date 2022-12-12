#ifndef ConjuntoPopulacional_H_INCLUDED
#define ConjuntoPopulacional_H_INCLUDED
#include "Solucao.h"
using namespace std;

class ConjuntoPopulacional
{

    // Attributes
private:
    int *lista1;
    int *lista2;
    int *lista3;
    int *populacao;
    int tamanhoPop;
    int tamanhoLista;
    int tamanhoMaxPop;

public:
    float alfa=0.3;
    Solucao *primeira_Solucao;
    Solucao *ultima_Solucao;
    // Constructor
    ConjuntoPopulacional(int tamanhoLista);
    ~ConjuntoPopulacional(){};
    void addSolucaoAListaIndexada(Solucao *solucao);
    void preencheListasPorRequisito(Solucao *solucao);
    void selecionaPopulacao();
    void selecionaPopulacao2();
    bool verificaSeJaTem(int id);
    int insereSolNaPopDadoPosicaoJaConhecida(int posicaoOndeSeraAdicionado, int idASerAdicionado);
    void insereEmLista1(int id, int posicao);
    void insereEmLista2(int id, int posicao);
    void insereEmLista3(int id, int posicao);
    Solucao *getSolucaoPorIndex(int id);
    void printPopListaIndexSol();
    int *getPopulacao();
    int getTamanhoPop();
    void printListas123();
};

#endif