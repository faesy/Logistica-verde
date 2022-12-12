#ifndef Construtor_H_INCLUDED
#define Construtor_H_INCLUDED
#include "CriadorInstancias.h"
#include "Solucao.h"
#include "Lista.h"

using namespace std;


class Construtor{

    // Attributes
    private:

    public:
    CriadorInstancias* instancia;
    Lista* lista;
    Solucao* solucao;
    float media_Custo_Minuto;
    float media_Consumo_por_tempo;
    float media_trabalho_por_tempo;


    float importanciaf1=2;
    float importanciaf2=1;
    float importanciaf3=1;
    //float parametro_de_analise=0.79;

    Construtor(CriadorInstancias* a);
    void embaralhar(int *vet, int vetSize);
    void Imprime();

    //Funções de Manipulação de Solução
    void Adiciona_Basico();
    void Adiciona_Processo_Na_Maquina(int id_processo,int id_maquina);
    void AdicionaPontos(int id_Processo);
    void RemovePontos(int id_Processo);

    //Funções de sortear na lista
    void Calcular_media_Consumo_por_tempo();
    void Calcular_media_trabalho_por_tempo();
    void Calcular_Custo_Minuto();

    
};

#endif 