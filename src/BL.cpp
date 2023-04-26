#include <iostream>
#include "BL.h"
#include "Construtor.h"

using namespace std;

void BL::BuscaLocal2(Solucao *solucao, int id_processo)
{
    // cout << "id_processo " << id_processo << endl;
    MaquinaSol *maquina1 = NULL;
    Processo *processoAux = NULL;
    ProcessoSol *processo = NULL;
    int posProcesso = 0;

    for (MaquinaSol *i = solucao->primeira_maquina; i != NULL; i = i->prox_maquinaSol)
    {

        int l = 0;
        for (ProcessoSol *j = i->primeiro_processoSol; j != NULL; j = j->prox_processoSol)
        {
            if (j->id == id_processo)
            {
                maquina1 = i;
                processoAux = this->instancia->buscaProcesso(j->id);
                processo = j;
                posProcesso = l;
            }
            l++;
        }
    }
    
    AtualizaCustos(solucao);
    float custoInicialF1 = solucao->makespam;
    float custoInicialF2 = solucao->custoEnergia;

    ProcessoSol *k;

    bool flag = false;
    // cout<<"1"<<endl;
    for (MaquinaSol *i = solucao->primeira_maquina; i != NULL; i = i->prox_maquinaSol)
    {
       
        if (maquina1->id == i->id)
        {
            i = i->prox_maquinaSol;
        }
        
        if (i == NULL)
        {
            break;
        }
        int contador = 0;
        for (ProcessoSol *j = i->primeiro_processoSol; j != NULL; j = j->prox_processoSol)
        {
          
            if (VerificaTrocaEmF1eF2_2(maquina1, i, processo, j, solucao->makespam))
            {
                    if (maquina1->id != i->id)
                    {
                        flag = true;
                        RemoveProcesso2(i, this->instancia->buscaProcesso(j->id), solucao);
                        AdicionaProcesso(maquina1, this->instancia->buscaProcesso(j->id), posProcesso);

                        RemoveProcesso2(maquina1, processoAux, solucao);
                        AdicionaProcesso(i, processoAux, contador);
                        break;
                    }
                
            }
            contador++;
        }
        if (flag)
        {
            break;
        }
    }
}

void BL::ChamadaDaBL2(Solucao *solucao, int repeticoes)
{
    for (int i = 0; i < repeticoes; i++)
    {
        //cout << i << endl;
        int id_processo = rand() % this->instancia->get_n();
        
        BuscaLocal2(solucao, id_processo);
        
    }

    for(int i=0;i<this->instancia->get_n();i++){
        for(MaquinaSol *a = solucao->primeira_maquina; a != NULL; a = a->prox_maquinaSol){
        solucao->jobs[i]=a->id;
        }

    }
}

void BL::ChamadaDaBL1(Solucao *solucao, int repeticoes)
{

    for (int i = 0; i < repeticoes; i++)
    {
        int id_processo = rand() % this->instancia->get_n();
        BuscaLocal1(solucao, id_processo);
    }

    for(int i=0;i<this->instancia->get_n();i++){
        for(MaquinaSol *a = solucao->primeira_maquina; a != NULL; a = a->prox_maquinaSol){
        solucao->jobs[i]=a->id;
        }

    }
}

void BL::BuscaLocal1(Solucao *solucao, int id_processo)
{

    MaquinaSol *maquinaremovida = NULL;
    Processo *processo = NULL;
    int posAnterior = 0;

    for (MaquinaSol *i = solucao->primeira_maquina; i != NULL; i = i->prox_maquinaSol)
    {
        int l = 0;
        for (ProcessoSol *j = i->primeiro_processoSol; j != NULL; j = j->prox_processoSol)
        {
            if (j->id == id_processo)
            {
                maquinaremovida = i;
                processo = this->instancia->buscaProcesso(j->id);
                posAnterior = l;
            }
            l++;
        }
    }
    MaquinaSol *i = solucao->primeira_maquina;
    bool flag = false;
    while (i != NULL)
    { // olho maquina a maquina
        int contador = 0;
        if (VerificaTrocaEmF1eF2(maquinaremovida, i, processo, solucao->makespam))
        { // se vale a pena (por F1 e F2) eu olho processo a processo
            for (ProcessoSol *j = i->primeiro_processoSol; j != NULL; j = j->prox_processoSol)
            {
                
                    RemoveProcesso(maquinaremovida, processo, posAnterior);
                    cout << "Adicionando o Processo " << processo->get_id() << " Na Maquina " << i->id << " Na pos " << contador << endl;
                    AdicionaProcesso(i, processo, contador);
                    AtualizaCustos(solucao);
                    posAnterior = contador;
                    flag = true;
                    maquinaremovida = i;
                    break;
                
                contador++;
            }
        }
        if (flag)
        {
            i = solucao->primeira_maquina;
            flag = false;
        }
        else
        {
            i = i->prox_maquinaSol;
        }
    }
}


bool BL::VerificaTrocaEmF1eF2_2(MaquinaSol *maquina1, MaquinaSol *maquina2, ProcessoSol *processo1, ProcessoSol *processo2, int makespam)
{
    
    Processo *processo1Aux = this->instancia->buscaProcesso(processo1->id);
    Processo *processo2Aux = this->instancia->buscaProcesso(processo2->id);
     
    int CEinicial = maquina1->CE + maquina2->CE;
    int CEfinal = maquina1->CE - processo1Aux->custos_energia[maquina1->id] + processo2Aux->custos_energia[maquina1->id] + maquina2->CE - processo2Aux->custos_energia[maquina2->id] + processo1Aux->custos_energia[maquina2->id];
    if (CEfinal >= CEinicial)
    {
        return false;
    }
     
    int novomakespam1 = maquina1->min_Atual + processo2Aux->tempos_processamento[maquina1->id] - processo1Aux->tempos_processamento[maquina1->id] - this->instancia->calcInicioDia();
    int novomakespam2 = maquina2->min_Atual + processo1Aux->tempos_processamento[maquina2->id] - processo2Aux->tempos_processamento[maquina2->id] - this->instancia->calcInicioDia();
    // cout<<"novomakespam: "<<novomakespam<<endl;
    // cout<<"makespam: "<<makespam<<endl;
    if (novomakespam1 >= makespam || novomakespam2 >= makespam)
    {
        return false;
    }
    return true;
}

bool BL::VerificaTrocaEmF1eF2(MaquinaSol *maquinaRemovida, MaquinaSol *maquinaAdicionada, Processo *processo, int makespam)
{

    int CEinicial = maquinaRemovida->CE + maquinaAdicionada->CE;
    int CEfinal = maquinaRemovida->CE - processo->custos_energia[maquinaRemovida->id] + maquinaAdicionada->CE + processo->custos_energia[maquinaAdicionada->id];
    if (CEfinal >= CEinicial)
    {
        return false;
    }

    int novomakespam = maquinaAdicionada->min_Atual + processo->tempos_processamento[maquinaAdicionada->id] - this->instancia->calcInicioDia();
    // cout<<"novomakespam: "<<novomakespam<<endl;
    // cout<<"makespam: "<<makespam<<endl;
    if (novomakespam >= makespam)
    {
        return false;
    }
    return true;
}

void BL::RemoveProcesso2(MaquinaSol *maquina, Processo *processo, Solucao *solucao)
{

    maquina->CE = maquina->CE - processo->custos_energia[maquina->id];                     // Atualizo custo de energia
    maquina->min_Atual = maquina->min_Atual - processo->tempos_processamento[maquina->id]; // Atualizo custo de tempo da maquina                                                                     // zero o custo Monetario

    int tempoAtual = this->instancia->calcInicioDia();
    int contador = 0;
    bool flag = true;
    for (ProcessoSol *i = maquina->primeiro_processoSol; i != NULL; i = i->prox_processoSol)
    {

        if (processo->get_id() == i->id)
        {

            flag = false;
            if (i->id == maquina->primeiro_processoSol->id)
            { // caso proc esteja sendo removido na pos 0
                if (i->prox_processoSol == NULL)
                {
                    maquina->primeiro_processoSol = NULL;
                    maquina->ultimo_processoSol = NULL;
                    delete i;

                    maquina->CE = 0;
                    maquina->min_Atual = 0;
                    break;
                }
                ProcessoSol *k = i;
                maquina->primeiro_processoSol = i->prox_processoSol;
                i->prox_processoSol->ant_processoSol = NULL;
                i = i->prox_processoSol;
                k->prox_processoSol = NULL;
                delete k;
            }
            else if (i->prox_processoSol == NULL)
            { // caso proc esteja sendo removido na pos final
                ProcessoSol *k = i;
                i->ant_processoSol->prox_processoSol = NULL;
                maquina->ultimo_processoSol = i->ant_processoSol;
                i = i->ant_processoSol;
                k->ant_processoSol = NULL;
                delete k;
                break;
            }
            else
            {
                ProcessoSol *k = i;
                i->ant_processoSol->prox_processoSol = i->prox_processoSol;
                i->prox_processoSol->ant_processoSol = i->ant_processoSol;
                i = i->prox_processoSol;
                k->prox_processoSol = NULL;
                k->ant_processoSol = NULL;
                delete k;
            }
        }

        tempoAtual = (tempoAtual + this->instancia->buscaProcesso(i->id)->tempos_processamento[maquina->id]);
        contador++;
    }

    if (flag)
    {
        cout << "============================================================================ ERRO em Remover =================================================================================" << endl;
    }
}

void BL::RemoveProcesso(MaquinaSol *maquina, Processo *processo, int pos)
{
    maquina->CE = maquina->CE - processo->custos_energia[maquina->id];                     // Atualizo custo de energia
    maquina->min_Atual = maquina->min_Atual - processo->tempos_processamento[maquina->id]; // Atualizo custo de tempo da maquina                                                                     // zero o custo Monetario

    int tempoAtual = this->instancia->calcInicioDia();
    int contador = 0;
    for (ProcessoSol *i = maquina->primeiro_processoSol; i != NULL; i = i->prox_processoSol)
    {

        if (pos == contador)
        {

            if (processo->get_id() == i->id)
            {

                if (i->id == maquina->primeiro_processoSol->id)
                { // caso proc esteja sendo removido na pos 0
                    if (i->prox_processoSol == NULL)
                    {
                        maquina->primeiro_processoSol = NULL;
                        maquina->ultimo_processoSol = NULL;
                        delete i;

                        maquina->CE = 0;
                        maquina->min_Atual = 0;
                        break;
                    }
                    ProcessoSol *k = i;
                    maquina->primeiro_processoSol = i->prox_processoSol;
                    i->prox_processoSol->ant_processoSol = NULL;
                    i = i->prox_processoSol;
                    k->prox_processoSol = NULL;
                    delete k;
                }
                else if (i->prox_processoSol == NULL)
                { // caso proc esteja sendo removido na pos final
                    ProcessoSol *k = i;
                    i->ant_processoSol->prox_processoSol = NULL;
                    maquina->ultimo_processoSol = i->ant_processoSol;
                    i = i->ant_processoSol;
                    k->ant_processoSol = NULL;
                    delete k;
                    break;
                }
                else
                {
                    ProcessoSol *k = i;
                    i->ant_processoSol->prox_processoSol = i->prox_processoSol;
                    i->prox_processoSol->ant_processoSol = i->ant_processoSol;
                    i = i->prox_processoSol;
                    k->prox_processoSol = NULL;
                    k->ant_processoSol = NULL;
                    delete k;
                }
            }
        }

        float customedioEnergia = 0;
        tempoAtual = (tempoAtual + this->instancia->buscaProcesso(i->id)->tempos_processamento[maquina->id]);
        contador++;
    }
}

void BL::AtualizaCustos(Solucao *sol)
{
    sol->custoEnergia = 0;
    sol->makespam = 0;

    for (MaquinaSol *i = sol->primeira_maquina; i != NULL; i = i->prox_maquinaSol)
    {
        sol->custoEnergia = sol->custoEnergia + i->CE;
        if (i->min_Atual - this->instancia->calcInicioDia() > sol->makespam)
        {
            sol->makespam = i->min_Atual - this->instancia->calcInicioDia();
        }
    }
}

void BL::AdicionaProcesso(MaquinaSol *maquina, Processo *processo, int pos)
{

    maquina->CE = maquina->CE + processo->custos_energia[maquina->id];                     // Atualizo custo de energia
    maquina->min_Atual = maquina->min_Atual + processo->tempos_processamento[maquina->id]; // Atualizo custo de tempo da maquina                                                                     // zero o custo Monetario

    int contador = 0;
    int tempoAtual = this->instancia->calcInicioDia();
    bool flag = true;
    for (ProcessoSol *i = maquina->primeiro_processoSol; i != NULL; i = i->prox_processoSol)
    {

        if (contador == pos)
        {
            flag = false;
            ProcessoSol *novoProc = new ProcessoSol();
            novoProc->id = processo->get_id();

            if (pos == 0)
            {                                             // caso proc esteja sendo adicionado na pos 0
                maquina->primeiro_processoSol = novoProc; // maquina recebe o novo processo como primeiro processo
                novoProc->ant_processoSol = NULL;         // processo anterior ao novo processo é nulo
                novoProc->prox_processoSol = i;           // prox processo do novo processo é o i
                i->ant_processoSol = novoProc;            // processo anterior ao i é o novoProc

                i = novoProc;
            }
            // else if(i->prox_processoSol==NULL){ //caso proc esteja sendo adicionado na pos final
            //    maquina->ultimo_processoSol=novoProc;
            //  novoProc->prox_processoSol=NULL;
            //   novoProc->ant_processoSol=i;
            //   i->prox_processoSol=novoProc;

            //   i=novoProc;
            //}
            else
            {

                i->ant_processoSol->prox_processoSol = novoProc;
                novoProc->prox_processoSol = i;
                novoProc->ant_processoSol = i->ant_processoSol;
                i->ant_processoSol = novoProc;

                i = novoProc;
            }
        }

        tempoAtual = (tempoAtual + this->instancia->buscaProcesso(i->id)->tempos_processamento[maquina->id]);

        if (contador + 1 == pos && i->prox_processoSol == NULL)
        {
            flag = false;
            ProcessoSol *novoProc = new ProcessoSol();
            novoProc->id = processo->get_id();

            maquina->ultimo_processoSol = novoProc;
            novoProc->prox_processoSol = NULL;
            novoProc->ant_processoSol = i;
            i->prox_processoSol = novoProc;

            i = novoProc;
            tempoAtual = (tempoAtual + this->instancia->buscaProcesso(i->id)->tempos_processamento[maquina->id]);

            break;
        }

        contador++;
    }
    if (flag)
    {
        cout << "====================================== ERRO ADICIONANDO ===================================================" << endl;
    }
}