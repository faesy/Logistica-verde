#ifndef Solucao_H_INCLUDED
#define Solucao_H_INCLUDED
#include "MaquinaSol.h"

using namespace std;


class Solucao{

    // Attributes
    private:

    public:
    int id;
    int custoEnergia;
    int makespam;
    int custoMonetario;
    Solucao(){
        custoEnergia=0;
        makespam=0;
        custoMonetario=0;
    }
    MaquinaSol* primeira_maquina;
    MaquinaSol* ultima_maquina;
    MaquinaSol* procura_maquina(int id){
    for(MaquinaSol* i=this->primeira_maquina;i !=NULL;i=i->prox_maquinaSol){
        if(i->id==id){
            return i;
        }
    }
    return NULL;
    }
    
    
};

#endif 