#ifndef MaquinaSol_H_INCLUDED
#define MaquinaSol_INCLUDED
#include "ProcessoSol.h"

using namespace std;


class MaquinaSol{

    // Attributes
    private:
    int id;

    MaquinaSol* prox_maquinaSol;
    MaquinaSol* ant_maquinaSol;
    
    ProcessoSol* primeiro_processoSol;
    ProcessoSol* ultimo_processoSol;

    public:
    
};

#endif 