#ifndef Solucao_H_INCLUDED
#define Solucao_H_INCLUDED
#include "MaquinaSol.h"
#include "CriadorInstancias.h"

using namespace std;

class Solucao
{

    // Attributes
private:
    Solucao *prox_Solucao;
    Solucao *ant_Solucao;

public:
    CriadorInstancias* instancia;
    int *jobs;
    int frente;
    int id;
    int pos;
    float custoEnergia;
    float makespam;
    Solucao()
    {
        custoEnergia = 0;
        makespam = 0;
    }
    MaquinaSol *primeira_maquina;
    MaquinaSol *ultima_maquina;
    MaquinaSol *procura_maquina(int id)
    {
        for (MaquinaSol *i = this->primeira_maquina; i != NULL; i = i->prox_maquinaSol)
        {
            if (i->id == id)
            {
                return i;
            }
        }
        return NULL;
    }

    void set_prox_solucao(Solucao *a);
    void set_ant_solucao(Solucao *a);
    Solucao *get_prox_solucao();
    Solucao *get_ant_solucao();

};

#endif