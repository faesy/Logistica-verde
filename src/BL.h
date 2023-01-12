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

    void BuscaLocal2(Solucao* solucao, int id_processo);

    void AdicionaProcesso(MaquinaSol* maquina,Processo* processo,int pos);

    void RemoveProcesso(MaquinaSol* maquina,Processo* processo,int pos);

    void RemoveProcesso2(MaquinaSol* maquina,Processo* processo,Solucao* solucao);

    bool VerificaTrocaEmF1eF2(MaquinaSol* maquinaRemovida,MaquinaSol* maquinaAdicionada,Processo* processo,int makespam);

    bool VerificaTrocaEmF1eF2_2(MaquinaSol *maquina1, MaquinaSol *maquina2, ProcessoSol *processo1,ProcessoSol *processo2, int makespam);

    bool VerificaTrocaEmF3(MaquinaSol* maquinaRemovida,MaquinaSol* maquinaAdicionada,Processo* processo,int pos, int posRem);

    bool VerificaTrocaEmF3_2(MaquinaSol *maquina1, MaquinaSol *maquina2, Processo *processo1,Processo *processo2, int pos1, int pos2);

    void BuscaLocal1(Solucao* solucao,int id_processo);

    void AtualizaCustos(Solucao* sol);

    
};

#endif 