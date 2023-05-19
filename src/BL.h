#ifndef BL_H_INCLUDED
#define BL_H_INCLUDED
#include "Solucao.h"
#include "ProcessoSol.h"
#include "Processo.h"
#include "Instancia.h"

using namespace std;


class BL{

    // Attributes
    private:

    public:

    BL(){
    }

    //Instancia* instancia;

    void ChamadaDaBL1(Solucao* solucao,int  repeticoes,Instancia* instancia);

    void ChamadaDaBL2(Solucao* solucao,int  repeticoes,Instancia* instancia);

    bool BuscaLocal2(Solucao* solucao, int id_processo,Instancia* instancia);

    bool BuscaLocal1(Solucao* solucao,int id_processo,Instancia* instancia);

    void ChamadaDaBL(Solucao *solucao,Instancia* instancia);


    
};

#endif 