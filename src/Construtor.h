#ifndef Construtor_H_INCLUDED
#define Construtor_H_INCLUDED
#include "CriadorInstancias.h"
#include "Solucao.h"

using namespace std;


class Construtor{

    // Attributes
    private:

    CriadorInstancias* instancia;
    //Lista* lista;
    Solucao* solucao;
    float media_Custo_Minuto;
    float media_Consumo_por_tempo;
    float media_trabalho_por_tempo;

    public:
    Construtor(CriadorInstancias* a);

    //Funções de Manipulação de Solução
    void Adiciona_Basico();
    void Adiciona_Processo_Na_Maquina();

    //Funções de sortear na lista
    void Calcular_media_Consumo_por_tempo();
    void Calcular_media_trabalho_por_tempo();
    void Calcular_Custo_Minuto();
    void Adicionar_na_Lista(int id_maquina);
    void Remove_na_Lista(int id_maquina);
    int Sorteia_na_Lista();
    void Zera_Lista();
};

#endif 