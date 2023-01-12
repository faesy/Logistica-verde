#include <iostream>
#include "BL.h"
#include "Construtor.h"

using namespace std;

void BL::BuscaLocal2(Solucao *solucao, int id_processo)
{
    cout<<"id_processo "<<id_processo<<endl;
    MaquinaSol *maquina1 = NULL;
    Processo *processoAux = NULL;
    ProcessoSol* processo = NULL;
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
                processo=j;
                posProcesso = l;
            }
            l++;
        }
    }

    AtualizaCustos(solucao);
    float custoInicialF1 = solucao->makespam;
    float custoInicialF2 = solucao->custoEnergia;
    float custoInicialF3 = solucao->custoMonetario;

    ProcessoSol *k;

    bool flag = false;
    bool flag2=false;
    //cout<<"1"<<endl;
    for (MaquinaSol *i = solucao->primeira_maquina; i != NULL; i = i->prox_maquinaSol)
    {
        if(maquina1->id == i->id){
            i=i->prox_maquinaSol;
        }
        if(i==NULL){
            break;
        }
        int contador = 0;
        for (ProcessoSol *j = i->primeiro_processoSol; j != NULL; j = k)
        {
            cout<<"Analisando Processo "<<j->id<<" Da Maquina "<<i->id<<endl;
            if (maquina1->id != i->id)
            {
                cout<<"Entrou ENCIMA"<<endl;
                flag2=true;
                RemoveProcesso2(i, this->instancia->buscaProcesso(j->id),solucao);
                AdicionaProcesso(maquina1, this->instancia->buscaProcesso(j->id), posProcesso);

                RemoveProcesso2(maquina1, processoAux,solucao);
                AdicionaProcesso(i, processoAux, contador);
                cout<<"Saiu ENCIMA"<<endl;

            }
            else if (maquina1->id == i->id)
            {
                // cout<<"4"<<endl;

                // RemoveProcesso2(i, this->instancia->buscaProcesso(j->id));
                // RemoveProcesso2(maquina1, processo);

                // if (contador > posProcesso)
                // {
                //     //cout<<"5"<<endl;
                //     AdicionaProcesso(i, processo, contador);
                //     AdicionaProcesso(maquina1, this->instancia->buscaProcesso(j->id), posProcesso);

                // }
                // else if (contador < posProcesso)
                // {
                //     //cout<<"6"<<endl;
                //     AdicionaProcesso(maquina1, this->instancia->buscaProcesso(j->id), posProcesso);
                //     AdicionaProcesso(i, processo, contador);
                //}else{
                //}
            }

            AtualizaCustos(solucao);
            float custoFinalF1 = solucao->makespam;
            float custoFinalF2 = solucao->custoEnergia;
            float custoFinalF3 = solucao->custoMonetario;
            //cout<<"7"<<endl;

            if(flag2){

                flag2=false;

            if(custoInicialF1 > custoFinalF1 && custoInicialF2 > custoFinalF2 && custoInicialF3 > custoFinalF3)
            {
                cout<<"Trocou o Processo "<<processo->id<<" da maquina "<<maquina1->id<<" com o processo "<<j->id<<" da maquina "<<i->id<<endl;
                flag = true;
                AtualizaCustos(solucao);
                break;
            }
            else
            {
                if (maquina1->id != i->id)
                {
                    cout<<"Entrou ENbaixo"<<endl;
                    //cout<<"9"<<endl;

                    RemoveProcesso2(maquina1, this->instancia->buscaProcesso(j->id),solucao);
                    AdicionaProcesso(i, this->instancia->buscaProcesso(j->id), contador);

                    RemoveProcesso2(i, processoAux,solucao);
                    AdicionaProcesso(maquina1, processoAux, posProcesso);


                    AtualizaCustos(solucao);
                    cout<<"saiu ENbaixo"<<endl;
                }
                else if (maquina1->id == i->id)
                {
                    // //cout<<"10"<<endl;
                    // RemoveProcesso2(maquina1, this->instancia->buscaProcesso(j->id));
                    // RemoveProcesso2(i, processo);

                    // if (contador > posProcesso)
                    // {
                    //     //cout<<"11"<<endl;
                    //     AdicionaProcesso(maquina1, processo, posProcesso);
                    //     AdicionaProcesso(i, this->instancia->buscaProcesso(j->id), contador);

                    // }
                    // else if (contador < posProcesso)
                    // {
                    //     //cout<<"12"<<endl;
                    //     AdicionaProcesso(maquina1, this->instancia->buscaProcesso(j->id), posProcesso);
                    //     AdicionaProcesso(i, processo, contador);
                    // }
                    // //cout<<"13"<<endl;
                    // AtualizaCustos(solucao);
                }
            }

            }
            contador++;
        }
        if (flag)
        {
            //cout<<"14"<<endl;
            break;
        }
    }
    //cout<<"fim"<<endl;
}

void BL::ChamadaDaBL2(Solucao* solucao,int  repeticoes){
    for (int i = 0; i < repeticoes; i++)
    {
        int id_processo = rand() % this->instancia->get_n();
        BuscaLocal2(solucao, id_processo);
    }
}

void BL::ChamadaDaBL1(Solucao *solucao, int repeticoes)
{

    for (int i = 0; i < repeticoes; i++)
    {
        int id_processo = rand() % this->instancia->get_n();
        BuscaLocal1(solucao, id_processo);
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
                if (VerificaTrocaEmF3(maquinaremovida, i, processo, contador, posAnterior))
                { // se vale a pena por F3
                    // cout<<"Removendo o Processo "<<processo->get_id()<<" Da Maquina "<<maquinaremovida->id<<" Da pos "<<posAnterior<<endl;
                    RemoveProcesso(maquinaremovida, processo, posAnterior);
                    cout << "Adicionando o Processo " << processo->get_id() << " Na Maquina " << i->id << " Na pos " << contador << endl;
                    AdicionaProcesso(i, processo, contador);
                    AtualizaCustos(solucao);
                    posAnterior = contador;
                    flag = true;
                    maquinaremovida = i;
                    break;
                }
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

bool BL::VerificaTrocaEmF3(MaquinaSol *maquinaRemovida, MaquinaSol *maquinaAdicionada, Processo *processo, int posAdc, int posRem)
{

    float CMinicial = maquinaRemovida->CM + maquinaAdicionada->CM;
    // cout<<"Custo Monetario Maq "<<maquinaRemovida->id<<" Rem: "<<maquinaRemovida->CM<<endl;
    // cout<<"Custo Monetario Maq "<<maquinaAdicionada->id<<" Adc: "<<maquinaAdicionada->CM<<endl;

    float CMfinal_maqRem = 0;
    float CMfinal_maqAdc = 0;

    int tempoAtual = 0;
    int contador = 0;
    for (ProcessoSol *i = maquinaRemovida->primeiro_processoSol; i != NULL; i = i->prox_processoSol)
    {

        if (processo->get_id() == i->id && contador == posRem)
        {
            if (i->prox_processoSol == NULL)
            { // caso proc esteja sendo removido na pos final
                break;
            }
            else
            {
                i = i->prox_processoSol;
            }
        }

        float customedioEnergia = 0;
        for (int f = 0; f < this->instancia->buscaProcesso(i->id)->tempos_processamento[maquinaRemovida->id]; f++)
        {
            customedioEnergia = customedioEnergia + instancia->intervalos[(tempoAtual + f) % 1440];
        }
        customedioEnergia = customedioEnergia / (float)this->instancia->buscaProcesso(i->id)->tempos_processamento[maquinaRemovida->id];
        CMfinal_maqRem = CMfinal_maqRem + this->instancia->buscaProcesso(i->id)->custos_energia[maquinaRemovida->id] * customedioEnergia;

        tempoAtual = (tempoAtual + this->instancia->buscaProcesso(i->id)->tempos_processamento[maquinaRemovida->id]);
        contador++;
    }

    tempoAtual = 0;
    contador = 0;
    for (ProcessoSol *i = maquinaAdicionada->primeiro_processoSol; i != NULL; i = i->prox_processoSol)
    {

        if (contador == posAdc)
        {

            float customedioEnergia = 0;
            for (int f = 0; f < this->instancia->buscaProcesso(processo->get_id())->tempos_processamento[maquinaAdicionada->id]; f++)
            {
                customedioEnergia = customedioEnergia + instancia->intervalos[(tempoAtual + f) % 1440];
            }
            customedioEnergia = customedioEnergia / (float)this->instancia->buscaProcesso(processo->get_id())->tempos_processamento[maquinaAdicionada->id];
            CMfinal_maqAdc = CMfinal_maqAdc + this->instancia->buscaProcesso(processo->get_id())->custos_energia[maquinaAdicionada->id] * customedioEnergia;

            tempoAtual = (tempoAtual + this->instancia->buscaProcesso(processo->get_id())->tempos_processamento[maquinaAdicionada->id]);
        }

        float customedioEnergia = 0;
        for (int f = 0; f < this->instancia->buscaProcesso(i->id)->tempos_processamento[maquinaAdicionada->id]; f++)
        {
            customedioEnergia = customedioEnergia + instancia->intervalos[(tempoAtual + f) % 1440];
        }
        customedioEnergia = customedioEnergia / (float)this->instancia->buscaProcesso(i->id)->tempos_processamento[maquinaAdicionada->id];
        CMfinal_maqAdc = CMfinal_maqAdc + this->instancia->buscaProcesso(i->id)->custos_energia[maquinaAdicionada->id] * customedioEnergia;

        tempoAtual = (tempoAtual + this->instancia->buscaProcesso(i->id)->tempos_processamento[maquinaAdicionada->id]);
    }
    contador++;

    float CMfinal = CMfinal_maqAdc + CMfinal_maqRem;

    // cout<<endl<<"Custo monetario Inicial: "<<CMinicial<<endl;
    // cout<<"Custo monetario final: "<<CMfinal<<endl;

    if (CMfinal >= CMinicial)
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

void BL::RemoveProcesso2(MaquinaSol *maquina, Processo *processo,Solucao* solucao)
{
    cout<<"Removendo o processo "<<processo->get_id()<<" da maquina "<<maquina->id<<endl;

    maquina->CE = maquina->CE - processo->custos_energia[maquina->id];                     // Atualizo custo de energia
    maquina->min_Atual = maquina->min_Atual - processo->tempos_processamento[maquina->id]; // Atualizo custo de tempo da maquina
    maquina->CM = 0;                                                                       // zero o custo Monetario

    int tempoAtual = this->instancia->calcInicioDia();
    int contador = 0;
    bool flag=true;
    for (ProcessoSol *i = maquina->primeiro_processoSol; i != NULL; i = i->prox_processoSol)
    {

        if (processo->get_id() == i->id)
        {

            flag=false;
            if (i->id == maquina->primeiro_processoSol->id)
            { // caso proc esteja sendo removido na pos 0
                if (i->prox_processoSol == NULL)
                {
                    maquina->primeiro_processoSol = NULL;
                    maquina->ultimo_processoSol = NULL;
                    delete i;

                    maquina->CE = 0;
                    maquina->CM = 0;
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

        float customedioEnergia = 0;
        for (int f = 0; f < this->instancia->buscaProcesso(i->id)->tempos_processamento[maquina->id]; f++)
        {
            customedioEnergia = customedioEnergia + instancia->intervalos[(tempoAtual + f) % 1440];
        }
        customedioEnergia = customedioEnergia / (float)this->instancia->buscaProcesso(i->id)->tempos_processamento[maquina->id];
        maquina->CM = maquina->CM + this->instancia->buscaProcesso(i->id)->custos_energia[maquina->id] * customedioEnergia;

        tempoAtual = (tempoAtual + this->instancia->buscaProcesso(i->id)->tempos_processamento[maquina->id]);
        contador++;
    }

    if(flag){
        cout<<"============================================================================ ERRO em Remover ================================================================================="<<endl;
        
    }
}

void BL::RemoveProcesso(MaquinaSol *maquina, Processo *processo, int pos)
{
    maquina->CE = maquina->CE - processo->custos_energia[maquina->id];                     // Atualizo custo de energia
    maquina->min_Atual = maquina->min_Atual - processo->tempos_processamento[maquina->id]; // Atualizo custo de tempo da maquina
    maquina->CM = 0;                                                                       // zero o custo Monetario

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
                        maquina->CM = 0;
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
        for (int f = 0; f < this->instancia->buscaProcesso(i->id)->tempos_processamento[maquina->id]; f++)
        {
            customedioEnergia = customedioEnergia + instancia->intervalos[(tempoAtual + f) % 1440];
        }
        customedioEnergia = customedioEnergia / (float)this->instancia->buscaProcesso(i->id)->tempos_processamento[maquina->id];
        maquina->CM = maquina->CM + this->instancia->buscaProcesso(i->id)->custos_energia[maquina->id] * customedioEnergia;

        tempoAtual = (tempoAtual + this->instancia->buscaProcesso(i->id)->tempos_processamento[maquina->id]);
        contador++;
    }

}

void BL::AtualizaCustos(Solucao *sol)
{
    sol->custoEnergia = 0;
    sol->makespam = 0;
    sol->custoMonetario = 0;

    for (MaquinaSol *i = sol->primeira_maquina; i != NULL; i = i->prox_maquinaSol)
    {
        sol->custoEnergia = sol->custoEnergia + i->CE;
        sol->custoMonetario = sol->custoMonetario + i->CM;
        if (i->min_Atual - this->instancia->calcInicioDia() > sol->makespam)
        {
            sol->makespam = i->min_Atual - this->instancia->calcInicioDia();
        }
    }
}

void BL::AdicionaProcesso(MaquinaSol *maquina, Processo *processo, int pos)
{

    cout<<"Adicionando o processo "<<processo->get_id()<<" na maquina "<<maquina->id<<" na pos "<<pos<<endl;

    maquina->CE = maquina->CE + processo->custos_energia[maquina->id];                     // Atualizo custo de energia
    maquina->min_Atual = maquina->min_Atual + processo->tempos_processamento[maquina->id]; // Atualizo custo de tempo da maquina
    maquina->CM = 0;                                                                       // zero o custo Monetario

    int contador = 0;
    int tempoAtual = this->instancia->calcInicioDia();
    bool flag=true;
    for (ProcessoSol *i = maquina->primeiro_processoSol; i != NULL; i = i->prox_processoSol)
    {

        if (contador == pos)
        {
            flag=false;
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

        float customedioEnergia = 0;
        for (int f = 0; f < this->instancia->buscaProcesso(i->id)->tempos_processamento[maquina->id]; f++)
        {
            customedioEnergia = customedioEnergia + instancia->intervalos[(tempoAtual + f) % 1440];
        }
        customedioEnergia = customedioEnergia / (float)this->instancia->buscaProcesso(i->id)->tempos_processamento[maquina->id];
        maquina->CM = maquina->CM + this->instancia->buscaProcesso(i->id)->custos_energia[maquina->id] * customedioEnergia;

        tempoAtual = (tempoAtual + this->instancia->buscaProcesso(i->id)->tempos_processamento[maquina->id]);

        if (contador + 1 == pos && i->prox_processoSol == NULL)
        {
            flag=false;
            ProcessoSol *novoProc = new ProcessoSol();
            novoProc->id = processo->get_id();

            maquina->ultimo_processoSol = novoProc;
            novoProc->prox_processoSol = NULL;
            novoProc->ant_processoSol = i;
            i->prox_processoSol = novoProc;

            i = novoProc;

            float customedioEnergia = 0;
            for (int f = 0; f < this->instancia->buscaProcesso(i->id)->tempos_processamento[maquina->id]; f++)
            {
                customedioEnergia = customedioEnergia + instancia->intervalos[(tempoAtual + f) % 1440];
            }
            customedioEnergia = customedioEnergia / (float)this->instancia->buscaProcesso(i->id)->tempos_processamento[maquina->id];
            maquina->CM = maquina->CM + this->instancia->buscaProcesso(i->id)->custos_energia[maquina->id] * customedioEnergia;

            tempoAtual = (tempoAtual + this->instancia->buscaProcesso(i->id)->tempos_processamento[maquina->id]);

            break;
        }

        contador++;
    }
    if(flag){
        cout<<"====================================== ERRO ADICIONANDO ==================================================="<<endl;
    }
}