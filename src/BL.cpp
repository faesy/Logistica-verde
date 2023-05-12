#include <iostream>
#include "BL.h"
#include "Construtivo.h"

using namespace std;


void BL::ChamadaDaBL2(Solucao *solucao, int repeticoes,Instancia* instancia)
{
    for (int i = 0; i < repeticoes; i++)
    {
        //cout << i << endl;
        int id_processo = rand() % instancia->get_n();
        
        BuscaLocal2(solucao, id_processo,instancia);
        
    }

}

void BL::ChamadaDaBL1(Solucao *solucao, int repeticoes,Instancia* instancia)
{

    for (int i = 0; i < repeticoes; i++)
    {
        int id_processo = rand() % instancia->get_n();
        BuscaLocal1(solucao, id_processo,instancia);
    }
}

void BL::BuscaLocal2(Solucao *solucao, int id_processo,Instancia* instancia)
{
    int melhorMakespam=solucao->makespam;
    int melhorCustoEnergetico=solucao->custoEnergia;
    int maquinaAtual=solucao->jobs[id_processo];

    //cout<<"2.1"<<endl;

    //simular trocar o processo sorteado com todos os processos e verificar se em alguma o custo energetico total da solução diminuiu
    for(int i=0;i<instancia->get_n();i++){
        //cout<<"2.2"<<endl;
        //cout<<i<<endl;
        int novoCustoEnergetico = melhorCustoEnergetico -instancia->buscaProcesso(id_processo)->custos_energia[maquinaAtual] + instancia->buscaProcesso(i)->custos_energia[maquinaAtual] + instancia->buscaProcesso(id_processo)->custos_energia[solucao->jobs[i]] - instancia->buscaProcesso(i)->custos_energia[solucao->jobs[i]];
    //                                                      menos o custo do job sorteado na maquina inicial                         mais o custo do job analisado na maquina inicial             mais o custo do job sorteado na maquina do job atual                      menos o custo do job analisado na maquina dele
    //cout<<"2.3"<<endl;
    if(melhorCustoEnergetico > novoCustoEnergetico){
        //cout<<"2.4"<<endl;
        int makespams[20];

            for(int j=0;j<20;j++){
                makespams[j]=0;
            }

            for(int j=0;j<instancia->get_n();j++){

                makespams[solucao->jobs[j]]= makespams[solucao->jobs[j]] + instancia->buscaProcesso(j)->tempos_processamento[solucao->jobs[j]];

            }
            //cout<<"2.5"<<endl;
            makespams[maquinaAtual]=makespams[maquinaAtual] - instancia->buscaProcesso(id_processo)->tempos_processamento[maquinaAtual] + instancia->buscaProcesso(i)->tempos_processamento[maquinaAtual];
            //                          ele mesmo                   menos o tempo de processamento do processo sorteado                                    mais o tempo de processamento do processo analisado

            makespams[solucao->jobs[i]]=makespams[solucao->jobs[i]] + instancia->buscaProcesso(id_processo)->tempos_processamento[solucao->jobs[i]] - instancia->buscaProcesso(i)->tempos_processamento[maquinaAtual];
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

void BL::BuscaLocal1(Solucao *solucao, int id_processo,Instancia* instancia)
{

    int melhorMakespam=solucao->makespam;
    int melhorCustoEnergetico=solucao->custoEnergia;
    int melhorMaquina=solucao->jobs[id_processo];

    //simular colocar o processo sorteado em todas as maquinas e verificar se em alguma o custo energetico total da solução diminuiu
    for(int i=0;i<instancia->get_m();i++){

        int novoCustoEnergetico = melhorCustoEnergetico - instancia->buscaProcesso(id_processo)->custos_energia[melhorMaquina] + instancia->buscaProcesso(id_processo)->custos_energia[i];
                                    /*menos o custo energetico do processo na melhor maquina*/                       /*mais o custo energetico do processo na maquina a ser verificada)*/
        
        
        if(melhorCustoEnergetico > novoCustoEnergetico){

            //se o custo energetico total da solução diminuiu calcular o makespam total da solução e verificar se ele diminuiu

            int makespams[20];

            for(int j=0;j<20;j++){
                makespams[j]=0;
            }

            for(int j=0;j<instancia->get_n();j++){

                makespams[solucao->jobs[j]]= makespams[solucao->jobs[j]] + instancia->buscaProcesso(j)->tempos_processamento[solucao->jobs[j]];

            }


            makespams[melhorMaquina]=makespams[melhorMaquina]-instancia->buscaProcesso(id_processo)->tempos_processamento[melhorMaquina];

            makespams[i]=makespams[i]+instancia->buscaProcesso(id_processo)->tempos_processamento[i];

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

