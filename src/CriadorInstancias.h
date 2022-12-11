#ifndef CRIADORINSTANCIAS_H_INCLUDED
#define CRIADORINSTANCIAS_H_INCLUDED
#include "Maquina.h"
#include "Processo.h"
#include "Intervalo.h"

using namespace std;


class CriadorInstancias{

    // Attributes
    private:
        int m; //num de maquinas
        int n; //num de processos
        int k; //num de intervalos de preço
        int b; //Tempo limite
       float intervalos[1440];

        float e1=0.3;
        float e2=0.2;
        float alfa=1.5;

        Maquina* primeira_maquina;
        Maquina* ultima_maquina;

        Processo* primeiro_processo;
        Processo* ultimo_processo;

        Intervalo* primeiro_intervalo;
        Intervalo* ultimo_intervalo;
        


    public:
        // Constructor
        CriadorInstancias();
        ~CriadorInstancias();
    
        void SorteiaNumProcessos();
        void SorteiaNumMaquinas();

        Maquina* get_primeira_maquina(){return this->primeira_maquina;}
        Maquina* get_ultima_maquina(){return this->ultima_maquina;}

        void GeraMaquinas();
        void GeraProcesos();

        void GeraKpadrao();

        void Calcula_b();

        int get_m(){return this->m;}
        int get_n(){return this->n;}
        int get_k(){return this->k;}
        int get_b(){return this->b;}

        int calcInicioDia();
        
        }; 

#endif 