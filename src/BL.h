#ifndef BL_H_INCLUDED
#define BL_H_INCLUDED
#include "Solucao.h"
#include "ProcessoSol.h"
#include "Processo.h"
#include "CriadorInstancias.h"

using namespace std;


class BL{

    // Attributes
    private:

    public:

    BL(CriadorInstancias* a){
        this->instancia=a;
    }

    CriadorInstancias* instancia;

    void ChamadaDaBL1(Solucao* solucao,int  repeticoes);

    void ChamadaDaBL2(Solucao* solucao,int  repeticoes);

    void BuscaLocal2(Solucao* solucao, int id_processo);//falta atualizar

    bool VerificaTrocaEmF1eF2_2(MaquinaSol *maquina1, MaquinaSol *maquina2, ProcessoSol *processo1,ProcessoSol *processo2, int makespam);

    void BuscaLocal1(Solucao* solucao,int id_processo);


    
};

#endif 