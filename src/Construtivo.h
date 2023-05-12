#ifndef Construtivo_H_INCLUDED
#define Construtivo_H_INCLUDED
#include "Instancia.h"
#include "Solucao.h"
#include "ListaCandidatos.h"
#include "Maquina.h"
#include "Processo.h"

using namespace std;


class Construtivo{

    // Attributes
    private:

    public:
    //Instancia* instancia;
    //Lista* lista;
    //Solucao* solucao;

    Construtivo(){};
    Solucao* criaSol(Instancia* instancia);
    void embaralhar(int *vet, int vetSize);
    void Imprime(Solucao* solucao,Instancia* instancia);

    //Funções de Manipulação de Solução
    void Adiciona_Basico(Solucao* solucao,Instancia* instancia);
    void Adiciona_Processo_Na_Maquina(int id_processo,int id_maquina,Solucao* solucao,Instancia* instancia);
    void AdicionaPontos(int id_Processo,Solucao* solucao,Instancia* instancia,ListaCandidatos *lista);
    void RemovePontos(int id_Processo,Solucao* solucao,Instancia* instancia,ListaCandidatos *lista);

    //Funções de sortear na lista
    void Calcular_media_Consumo_por_tempo(Instancia* instancia);
    void Calcular_media_trabalho_por_tempo(Instancia* instancia);

    
};

#endif 