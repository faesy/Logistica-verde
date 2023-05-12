#include <iostream>
#include "BL.h"
#include "Construtor.h"

using namespace std;


void BL::ChamadaDaBL2(Solucao *solucao, int repeticoes)
{
    for (int i = 0; i < repeticoes; i++)
    {
        //cout << i << endl;
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

void BL::BuscaLocal2(Solucao *solucao, int id_processo)
{
    int melhorMakespam=solucao->makespam;
    int melhorCustoEnergetico=solucao->custoEnergia;
    int maquinaAtual=solucao->jobs[id_processo];

    //cout<<"2.1"<<endl;

    //simular trocar o processo sorteado com todos os processos e verificar se em alguma o custo energetico total da solução diminuiu
    for(int i=0;i<solucao->instancia->get_n();i++){
        //cout<<"2.2"<<endl;
        //cout<<i<<endl;
        int novoCustoEnergetico = melhorCustoEnergetico - solucao->instancia->buscaProcesso(id_processo)->custos_energia[maquinaAtual] + solucao->instancia->buscaProcesso(i)->custos_energia[maquinaAtual] + solucao->instancia->buscaProcesso(id_processo)->custos_energia[solucao->jobs[i]] - solucao->instancia->buscaProcesso(i)->custos_energia[solucao->jobs[i]];
    //                                                      menos o custo do job sorteado na maquina inicial                                    mais o custo do job analisado na maquina inicial                    mais o custo do job sorteado na maquina do job atual                                menos o custo do job analisado na maquina dele
    //cout<<"2.3"<<endl;
    if(melhorCustoEnergetico > novoCustoEnergetico){
        //cout<<"2.4"<<endl;
        int makespams[20];

            for(int j=0;j<20;j++){
                makespams[j]=0;
            }

            for(int j=0;j<solucao->instancia->get_n();j++){

                makespams[solucao->jobs[j]]= makespams[solucao->jobs[j]] + solucao->instancia->buscaProcesso(i)->tempos_processamento[solucao->jobs[j]];

            }
            //cout<<"2.5"<<endl;
            makespams[maquinaAtual]=makespams[maquinaAtual] - solucao->instancia->buscaProcesso(id_processo)->tempos_processamento[maquinaAtual] + solucao->instancia->buscaProcesso(i)->tempos_processamento[maquinaAtual];
            //                          ele mesmo                   menos o tempo de processamento do processo sorteado                                    mais o tempo de processamento do processo analisado

            makespams[solucao->jobs[i]]=makespams[solucao->jobs[i]] + solucao->instancia->buscaProcesso(id_processo)->tempos_processamento[solucao->jobs[i]] - solucao->instancia->buscaProcesso(i)->tempos_processamento[maquinaAtual];
            //                                  ele mesmo                   mais o tempo de processamento do processo sorteado
            //cout<<"2.6"<<endl;
            int maiorMakespam=0;
            for(int j=0;j<20;j++){
                if( makespams[j]>maiorMakespam){
                    maiorMakespam=makespams[j];
                }
            }
            //cout<<"2.7"<<endl;
            if(melhorMakespam > maiorMakespam){
                //ao final de simular todas as maquinas fazer a troca do processo-maquina e atualizar os parametros
                //cout<<"2.8"<<endl;
                solucao->jobs[id_processo]=solucao->jobs[i];
                solucao->jobs[i]=maquinaAtual;

                solucao->makespam=maiorMakespam;
                melhorMakespam=maiorMakespam;

                solucao->custoEnergia=novoCustoEnergetico;
                melhorCustoEnergetico=novoCustoEnergetico;

                maquinaAtual=solucao->jobs[i];
                //cout<<"2.9"<<endl;
            }

    }

    }

}

void BL::BuscaLocal1(Solucao *solucao, int id_processo)
{

    int melhorMakespam=solucao->makespam;
    int melhorCustoEnergetico=solucao->custoEnergia;
    int melhorMaquina=solucao->jobs[id_processo];

    //simular colocar o processo sorteado em todas as maquinas e verificar se em alguma o custo energetico total da solução diminuiu
    for(int i=0;i<solucao->instancia->get_m();i++){

        int novoCustoEnergetico = melhorCustoEnergetico - solucao->instancia->buscaProcesso(id_processo)->custos_energia[melhorMaquina] + solucao->instancia->buscaProcesso(id_processo)->custos_energia[i];
                                    /*menos o custo energetico do processo na melhor maquina*/                       /*mais o custo energetico do processo na maquina a ser verificada)*/
        
        
        if(melhorCustoEnergetico > novoCustoEnergetico){

            //se o custo energetico total da solução diminuiu calcular o makespam total da solução e verificar se ele diminuiu

            int makespams[20];

            for(int j=0;j<20;j++){
                makespams[j]=0;
            }

            for(int j=0;j<solucao->instancia->get_n();j++){

                makespams[solucao->jobs[j]]= makespams[solucao->jobs[j]] + solucao->instancia->buscaProcesso(i)->tempos_processamento[solucao->jobs[j]];

            }

            makespams[melhorMaquina]=makespams[melhorMaquina]-solucao->instancia->buscaProcesso(id_processo)->tempos_processamento[melhorMaquina];

            makespams[i]=makespams[i]+solucao->instancia->buscaProcesso(id_processo)->tempos_processamento[i];

            int maiorMakespam=0;
            for(int j=0;j<20;j++){
                if( makespams[j]>maiorMakespam){
                    maiorMakespam=makespams[j];
                }
            }

            if(melhorMakespam > maiorMakespam){
                //ao final de simular todas as maquinas fazer a troca do processo-maquina e atualizar os parametros

                solucao->jobs[id_processo]=i;

                solucao->makespam=maiorMakespam;
                melhorMakespam=maiorMakespam;

                solucao->custoEnergia=novoCustoEnergetico;
                melhorCustoEnergetico=novoCustoEnergetico;

                melhorMaquina=i;

            }

        }

    }

    //ao final de simular todas as maquinas fazer a troca do processo-maquina e atualizar os parametros
    


    
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
     
    int novomakespam1 = maquina1->min_Atual + processo2Aux->tempos_processamento[maquina1->id] - processo1Aux->tempos_processamento[maquina1->id];
    int novomakespam2 = maquina2->min_Atual + processo1Aux->tempos_processamento[maquina2->id] - processo2Aux->tempos_processamento[maquina2->id];
    // cout<<"novomakespam: "<<novomakespam<<endl;
    // cout<<"makespam: "<<makespam<<endl;
    if (novomakespam1 >= makespam || novomakespam2 >= makespam)
    {
        return false;
    }
    return true;
}

