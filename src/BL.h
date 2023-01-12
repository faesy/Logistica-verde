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

    void AdicionaProcesso(MaquinaSol* maquina,Processo* processo,int pos);

    void RemoveProcesso(MaquinaSol* maquina,Processo* processo,int pos);

    bool VerificaTrocaEmF1eF2(MaquinaSol* maquinaRemovida,MaquinaSol* maquinaAdicionada,Processo* processo,int makespam);

    bool VerificaTrocaEmF3(MaquinaSol* maquinaRemovida,MaquinaSol* maquinaAdicionada,Processo* processo,int pos, int posRem);

    void BuscaLocal1(Solucao* Solucao,int id_processo);

    void AtualizaCustos(Solucao* sol);

    
};

#endif 